///
// expected - An implementation of std::expected with extensions
// Written in 2017 by Simon Brand (@TartanLlama)
//
// To the extent possible under law, the author(s) have dedicated all
// copyright and related and neighboring rights to this software to the
// public domain worldwide. This software is distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication
// along with this software. If not, see
// <http://creativecommons.org/publicdomain/zero/1.0/>.
///

#ifndef TL_EXPECTED_HPP
#define TL_EXPECTED_HPP

#include <exception>
#include <functional>
#include <type_traits>
#include <utility>
#include <iostream>

#if (defined(_MSC_VER) && _MSC_VER == 1900)
#define TL_EXPECTED_MSVC2015
#endif

#if (defined(__GNUC__) && __GNUC__ == 4 && __GNUC_MINOR__ <= 9)
#define TL_EXPECTED_GCC49
#endif

#if (defined(__GNUC__) && __GNUC__ == 5 && __GNUC_MINOR__ <= 4)
#define TL_EXPECTED_GCC54
#endif

#if (defined(__GNUC__) && __GNUC__ == 4 && __GNUC_MINOR__ <= 9)
#define TL_EXPECTED_NO_CONSTRR
#endif

#if __cplusplus > 201103L
#define TL_EXPECTED_CXX14
#endif

#if (__cplusplus == 201103L || defined(TL_EXPECTED_MSVC2015) ||                \
     defined(TL_EXPECTED_GCC49)) &&                                            \
    !defined(TL_EXPECTED_GCC50)
/// \exclude
#define TL_EXPECTED_11_CONSTEXPR
#else
/// \exclude
#define TL_EXPECTED_11_CONSTEXPR constexpr
#endif

namespace tl {
template <class T, class E> class expected;

namespace detail {
template <bool E, class T = void>
using enable_if_t = typename std::enable_if<E, T>::type;
template <class T> using decay_t = typename std::decay<T>::type;

// Trait for checking if a type is a tl::expected
template <class T> struct is_expected_impl : std::false_type {};
template <class T, class E>
struct is_expected_impl<expected<T, E>> : std::true_type {};
template <class T> using is_expected = is_expected_impl<decay_t<T>>;

// std::invoke from C++17
// https://stackoverflow.com/questions/38288042/c11-14-invoke-workaround
template <typename Fn, typename... Args,
          typename = enable_if_t<std::is_member_pointer<decay_t<Fn>>{}>,
          int = 0>
constexpr auto invoke(Fn &&f, Args &&... args) noexcept(
    noexcept(std::mem_fn(f)(std::forward<Args>(args)...)))
    -> decltype(std::mem_fn(f)(std::forward<Args>(args)...)) {
  return std::mem_fn(f)(std::forward<Args>(args)...);
}

template <typename Fn, typename... Args,
          typename = enable_if_t<!std::is_member_pointer<decay_t<Fn>>{}>>
constexpr auto invoke(Fn &&f, Args &&... args) noexcept(
    noexcept(std::forward<Fn>(f)(std::forward<Args>(args)...)))
    -> decltype(std::forward<Fn>(f)(std::forward<Args>(args)...)) {
  return std::forward<Fn>(f)(std::forward<Args>(args)...);
}

// std::invoke_result from C++17
template <class F, class, class... Us> struct invoke_result_impl;

template <class F, class... Us>
struct invoke_result_impl<
    F, decltype(invoke(std::declval<F>(), std::declval<Us>()...), void()),
    Us...> {
  using type = decltype(invoke(std::declval<F>(), std::declval<Us>()...));
};

template <class F, class... Us>
using invoke_result = invoke_result_impl<F, void, Us...>;

template <class F, class... Us>
using invoke_result_t = typename invoke_result<F, Us...>::type;

} // namespace detail

#ifndef TL_IN_PLACE_MONOSTATE_DEFINED
#define TL_IN_PLACE_MONOSTATE_DEFINED
/// \brief Used to represent an optional with no data; essentially a bool
class monostate {};

/// \brief A tag type to tell optional to construct its value in-place
struct in_place_t {
  explicit in_place_t() = default;
};
/// \brief A tag to tell optional to construct its value in-place
static constexpr in_place_t in_place{};
#endif

template <class E> class unexpected {
public:
  static_assert(!std::is_same<E, void>::value, "E must not be void");
  unexpected() = delete;
  constexpr explicit unexpected(const E &e) : m_val(e) {}

  constexpr explicit unexpected(E &&e) : m_val(std::move(e)) {}

  constexpr const E &value() const & { return m_val; }
  constexpr E &value() & { return m_val; }
  constexpr E &&value() && { return std::move(m_val); }
  constexpr E const &&value() const && { return std::move(m_val); }

private:
  E m_val;
};

template <class E>
constexpr bool operator==(const unexpected<E> &lhs, const unexpected<E> &rhs) {
  return lhs.value() == rhs.value();
}
template <class E>
constexpr bool operator!=(const unexpected<E> &lhs, const unexpected<E> &rhs) {
  return lhs.value() != rhs.value();
}
template <class E>
constexpr bool operator<(const unexpected<E> &lhs, const unexpected<E> &rhs) {
  return lhs.value() < rhs.value();
}
template <class E>
constexpr bool operator<=(const unexpected<E> &lhs, const unexpected<E> &rhs) {
  return lhs.value() <= rhs.value();
}
template <class E>
constexpr bool operator>(const unexpected<E> &lhs, const unexpected<E> &rhs) {
  return lhs.value() > rhs.value();
}
template <class E>
constexpr bool operator>=(const unexpected<E> &lhs, const unexpected<E> &rhs) {
  return lhs.value() >= rhs.value();
}

struct unexpect_t {
  unexpect_t() = default;
};
static constexpr unexpect_t unexpect{};

namespace detail {
template <class T, class E, bool = std::is_trivially_destructible<T>::value,
          bool = std::is_trivially_destructible<E>::value>
struct expected_storage_base {
  constexpr expected_storage_base() : m_val(T{}), m_has_val(true) {}

  template <class... Args,
            detail::enable_if_t<std::is_constructible<T, Args &&...>::value> * =
                nullptr>
  constexpr expected_storage_base(in_place_t, Args &&... args)
      : m_val(std::forward<Args>(args)...), m_has_val(true) {}

  template <class U, class... Args,
            detail::enable_if_t<std::is_constructible<
                T, std::initializer_list<U> &, Args &&...>::value> * = nullptr>
  constexpr expected_storage_base(in_place_t, std::initializer_list<U> il,
                                  Args &&... args)
      : m_val(il, std::forward<Args>(args)...), m_has_val(true) {}
  template <class... Args,
            detail::enable_if_t<std::is_constructible<E, Args &&...>::value> * =
                nullptr>
  constexpr explicit expected_storage_base(unexpect_t, Args &&... args)
      : m_unexpect(std::forward<Args>(args)...), m_has_val(false) {}

  template <class U, class... Args,
            detail::enable_if_t<std::is_constructible<
                E, std::initializer_list<U> &, Args &&...>::value> * = nullptr>
  constexpr explicit expected_storage_base(unexpect_t,
                                           std::initializer_list<U> il,
                                           Args &&... args)
      : m_unexpect(il, std::forward<Args>(args)...), m_has_val(false) {}

  ~expected_storage_base() {
    if (m_has_val) {
      m_val.~T();
    } else {
      m_unexpect.~unexpected<E>();
    }
  }
  bool m_has_val;
  union {
    T m_val;
    unexpected<E> m_unexpect;
  };
};

template <class T, class E> struct expected_storage_base<T, E, true, true> {
  constexpr expected_storage_base() : m_val(T{}), m_has_val(true) {}

  template <class... Args,
            detail::enable_if_t<std::is_constructible<T, Args &&...>::value> * =
                nullptr>
  constexpr expected_storage_base(in_place_t, Args &&... args)
      : m_val(std::forward<Args>(args)...), m_has_val(true) {}

  template <class U, class... Args,
            detail::enable_if_t<std::is_constructible<
                T, std::initializer_list<U> &, Args &&...>::value> * = nullptr>
  constexpr expected_storage_base(in_place_t, std::initializer_list<U> il,
                                  Args &&... args)
      : m_val(il, std::forward<Args>(args)...), m_has_val(true) {}
  template <class... Args,
            detail::enable_if_t<std::is_constructible<E, Args &&...>::value> * =
                nullptr>
  constexpr explicit expected_storage_base(unexpect_t, Args &&... args)
      : m_unexpect(std::forward<Args>(args)...), m_has_val(false) {}

  template <class U, class... Args,
            detail::enable_if_t<std::is_constructible<
                E, std::initializer_list<U> &, Args &&...>::value> * = nullptr>
  constexpr explicit expected_storage_base(unexpect_t,
                                           std::initializer_list<U> il,
                                           Args &&... args)
      : m_unexpect(il, std::forward<Args>(args)...), m_has_val(false) {}

  ~expected_storage_base() = default;
  bool m_has_val;
  union {
    T m_val;
    unexpected<E> m_unexpect;
  };
};

template <class T, class E> struct expected_storage_base<T, E, true, false> {
  constexpr expected_storage_base() : m_val(T{}), m_has_val(true) {}

  template <class... Args,
            detail::enable_if_t<std::is_constructible<T, Args &&...>::value> * =
                nullptr>
  constexpr expected_storage_base(in_place_t, Args &&... args)
      : m_val(std::forward<Args>(args)...), m_has_val(true) {}

  template <class U, class... Args,
            detail::enable_if_t<std::is_constructible<
                T, std::initializer_list<U> &, Args &&...>::value> * = nullptr>
  constexpr expected_storage_base(in_place_t, std::initializer_list<U> il,
                                  Args &&... args)
      : m_val(il, std::forward<Args>(args)...), m_has_val(true) {}
  template <class... Args,
            detail::enable_if_t<std::is_constructible<E, Args &&...>::value> * =
                nullptr>
  constexpr explicit expected_storage_base(unexpect_t, Args &&... args)
      : m_unexpect(std::forward<Args>(args)...), m_has_val(false) {}

  template <class U, class... Args,
            detail::enable_if_t<std::is_constructible<
                E, std::initializer_list<U> &, Args &&...>::value> * = nullptr>
  constexpr explicit expected_storage_base(unexpect_t,
                                           std::initializer_list<U> il,
                                           Args &&... args)
      : m_unexpect(il, std::forward<Args>(args)...), m_has_val(false) {}

  ~expected_storage_base() {
    if (!m_has_val) {
      m_unexpect.~unexpected<E>();
    }
  }

  bool m_has_val;
  union {
    T m_val;
    unexpected<E> m_unexpect;
  };
};

template <class T, class E> struct expected_storage_base<T, E, false, true> {
  constexpr expected_storage_base() : m_val(T{}), m_has_val(true) {}

  template <class... Args,
            detail::enable_if_t<std::is_constructible<T, Args &&...>::value> * =
                nullptr>
  constexpr expected_storage_base(in_place_t, Args &&... args)
      : m_val(std::forward<Args>(args)...), m_has_val(true) {}

  template <class U, class... Args,
            detail::enable_if_t<std::is_constructible<
                T, std::initializer_list<U> &, Args &&...>::value> * = nullptr>
  constexpr expected_storage_base(in_place_t, std::initializer_list<U> il,
                                  Args &&... args)
      : m_val(il, std::forward<Args>(args)...), m_has_val(true) {}
  template <class... Args,
            detail::enable_if_t<std::is_constructible<E, Args &&...>::value> * =
                nullptr>
  constexpr explicit expected_storage_base(unexpect_t, Args &&... args)
      : m_unexpect(std::forward<Args>(args)...), m_has_val(false) {}

  template <class U, class... Args,
            detail::enable_if_t<std::is_constructible<
                E, std::initializer_list<U> &, Args &&...>::value> * = nullptr>
  constexpr explicit expected_storage_base(unexpect_t,
                                           std::initializer_list<U> il,
                                           Args &&... args)
      : m_unexpect(il, std::forward<Args>(args)...), m_has_val(false) {}

  ~expected_storage_base() {
    if (m_has_val) {
      m_val.~T();
    }
  }
  bool m_has_val;
  union {
    T m_val;
    unexpected<E> m_unexpect;
  };
};

template <class E> struct expected_storage_base<void, E, false, true> {
  constexpr expected_storage_base() : m_val(), m_has_val(true) {}

  template <class... Args,
            detail::enable_if_t<std::is_constructible<E, Args &&...>::value> * =
                nullptr>
  constexpr explicit expected_storage_base(unexpect_t, Args &&... args)
      : m_unexpect(std::forward<Args>(args)...), m_has_val(false) {}

  template <class U, class... Args,
            detail::enable_if_t<std::is_constructible<
                E, std::initializer_list<U> &, Args &&...>::value> * = nullptr>
  constexpr explicit expected_storage_base(unexpect_t,
                                           std::initializer_list<U> il,
                                           Args &&... args)
      : m_unexpect(il, std::forward<Args>(args)...), m_has_val(false) {}

  ~expected_storage_base() = default;

  bool m_has_val;
  struct dummy {};
  union {
    dummy m_val;
    unexpected<E> m_unexpect;
  };
};

template <class E> struct expected_storage_base<void, E, false, false> {
  constexpr expected_storage_base() : m_val(), m_has_val(true) {}

  template <class... Args,
            detail::enable_if_t<std::is_constructible<E, Args &&...>::value> * =
                nullptr>
  constexpr explicit expected_storage_base(unexpect_t, Args &&... args)
      : m_unexpect(std::forward<Args>(args)...), m_has_val(false) {}

  template <class U, class... Args,
            detail::enable_if_t<std::is_constructible<
                E, std::initializer_list<U> &, Args &&...>::value> * = nullptr>
  constexpr explicit expected_storage_base(unexpect_t,
                                           std::initializer_list<U> il,
                                           Args &&... args)
      : m_unexpect(il, std::forward<Args>(args)...), m_has_val(false) {}

  ~expected_storage_base() {
    if (m_has_val) {
      m_val.~T();
    }
  }

  bool m_has_val;
  struct dummy {};
  union {
    dummy m_val;
    unexpected<E> m_unexpect;
  };
};

// TODO, conditionally delete things
template <class T, class E> class expected_ctor_base {};
} // namespace detail

template <class E> class bad_expected_access : public std::exception {
public:
  explicit bad_expected_access(E e) : m_val(std::move(e)) {}

  virtual const char *what() const noexcept override {
    return "Bad expected access";
  }

  const E &error() const & { return m_val; }
  E &error() & { return m_val; }
  const E &&error() const && { return std::move(m_val); }
  E &&error() && { return std::move(m_val); }

private:
  E m_val;
};

template <class T, class E>
class expected : private detail::expected_storage_base<T, E>,
                 private detail::expected_ctor_base<T, E> {
  static_assert(!std::is_reference<T>::value, "T must not be a reference");
  static_assert(!std::is_same<T, std::remove_cv<in_place_t>>::value,
                "T must not be in_place_t");
  static_assert(!std::is_same<T, std::remove_cv<unexpect_t>>::value,
                "T must not be unexpect_t");
  static_assert(!std::is_same<T, std::remove_cv<unexpected<E>>>::value,
                "T must not be unexpected<E>");
  static_assert(!std::is_reference<E>::value, "E must not be a reference");
  static_assert(!std::is_same<T, void>::value, "T must not be void");

  T *valptr() { return std::addressof(this->m_val); }
  unexpected<E> *errptr() { return std::addressof(this->m_unexpect); }
  T &val() { return this->m_val; }
  unexpected<E> &err() { return this->m_unexpect; }
  const T &val() const { return this->m_val; }
  const unexpected<E> &err() const { return this->m_unexpect; }

  using storage_base = detail::expected_storage_base<T, E>;

public:
  typedef T value_type;
  typedef E error_type;
  typedef unexpected<E> unexpected_type;

#if defined(TL_EXPECTED_CXX14) && !defined(TL_EXPECTED_GCC49) && !defined(TL_EXPECTED_GCC54)
  /// \group and_then
  /// Carries out some operation which returns an optional on the stored object
  /// if there is one. \requires `std::invoke(std::forward<F>(f), value())`
  /// returns a `std::optional<U>` for some `U`. \returns Let `U` be the result
  /// of `std::invoke(std::forward<F>(f), value())`. Returns a
  /// `std::optional<U>`. The return value is empty if `*this` is empty,
  /// otherwise the return value of `std::invoke(std::forward<F>(f), value())`
  /// is returned. \group and_then \synopsis template <class F>\nconstexpr auto
  /// and_then(F &&f) &;
  template <class F> TL_EXPECTED_11_CONSTEXPR auto and_then(F &&f) & {
    using result = detail::invoke_result_t<F, T &>;
    static_assert(detail::is_expected<result>::value,
                  "F must return an expected");

    return has_value() ? detail::invoke(std::forward<F>(f), **this)
                       : result(unexpect, this->error());
  }

  /// \group and_then
  /// \synopsis template <class F>\nconstexpr auto and_then(F &&f) &&;
  template <class F> TL_EXPECTED_11_CONSTEXPR auto and_then(F &&f) && {
    using result = detail::invoke_result_t<F, T &&>;
    static_assert(detail::is_expected<result>::value,
                  "F must return an expected");

    return has_value() ? detail::invoke(std::forward<F>(f), std::move(**this))
                       : result(unexpect, std::move(this->error()));
  }

  /// \group and_then
  /// \synopsis template <class F>\nconstexpr auto and_then(F &&f) const &;
  template <class F> constexpr auto and_then(F &&f) const & {
    using result = detail::invoke_result_t<F, const T &>;
    static_assert(detail::is_expected<result>::value,
                  "F must return an expected");

    return has_value() ? detail::invoke(std::forward<F>(f), **this)
                       : result(unexpect, this->error());
  }

#ifndef TL_EXPECTED_NO_CONSTRR
  /// \group and_then
  /// \synopsis template <class F>\nconstexpr auto and_then(F &&f) const &&;
  template <class F> constexpr auto and_then(F &&f) const && {
    using result = detail::invoke_result_t<F, const T &&>;
    static_assert(detail::is_expected<result>::value,
                  "F must return an expected");

    return has_value() ? detail::invoke(std::forward<F>(f), std::move(**this))
                       : result(unexpect, std::
                                    : move(this->error()));
  }
#endif

#else
  /// \group and_then
  /// Carries out some operation which returns an optional on the stored object
  /// if there is one. \requires `std::invoke(std::forward<F>(f), value())`
  /// returns a `std::optional<U>` for some `U`. \returns Let `U` be the result
  /// of `std::invoke(std::forward<F>(f), value())`. Returns a
  /// `std::optional<U>`. The return value is empty if `*this` is empty,
  /// otherwise the return value of `std::invoke(std::forward<F>(f), value())`
  /// is returned. \group and_then \synopsis template <class F>\nconstexpr auto
  /// and_then(F &&f) &;
  template <class F>
  TL_EXPECTED_11_CONSTEXPR detail::invoke_result_t<F, T &> and_then(F &&f) & {
    using result = detail::invoke_result_t<F, T &>;
    static_assert(detail::is_expected<result>::value,
                  "F must return an expected");

    return has_value() ? detail::invoke(std::forward<F>(f), **this)
                       : result(unexpect, this->error());
  }

  /// \group and_then
  /// \synopsis template <class F>\nconstexpr auto and_then(F &&f) &&;
  template <class F>
  TL_EXPECTED_11_CONSTEXPR detail::invoke_result_t<F, T &&> and_then(F &&f) && {
    using result = detail::invoke_result_t<F, T &&>;
    static_assert(detail::is_expected<result>::value,
                  "F must return an expected");

    return has_value() ? detail::invoke(std::forward<F>(f), **this)
                       : result(unexpect, std::move(this->error()));
  }

  /// \group and_then
  /// \synopsis template <class F>\nconstexpr auto and_then(F &&f) const &;
  template <class F>
  constexpr detail::invoke_result_t<F, const T &> and_then(F &&f) const & {
    using result = detail::invoke_result_t<F, const T &>;
    static_assert(detail::is_expected<result>::value,
                  "F must return an expected");

    return has_value() ? detail::invoke(std::forward<F>(f), **this)
                       : result(unexpect, this->error());
  }

#ifndef TL_EXPECTED_NO_CONSTRR
  /// \group and_then
  /// \synopsis template <class F>\nconstexpr auto and_then(F &&f) const &&;
  template <class F>
  constexpr detail::invoke_result_t<F, const T &&> and_then(F &&f) const && {
    using result = detail::invoke_result_t<F, const T &&>;
    static_assert(detail::is_expected<result>::value,
                  "F must return an expected");

    return has_value() ? detail::invoke(std::forward<F>(f), **this)
                       : result(unexpect, std::move(this->error()));
  }
#endif
#endif

#if defined(TL_EXPECTED_CXX14) && !defined(TL_EXPECTED_GCC49) && !defined(TL_EXPECTED_GCC54)
  /// \brief Carries out some operation on the stored object if there is one.
  /// \returns Let `U` be the result of `std::invoke(std::forward<F>(f),
  /// value())`. Returns a `std::expected<U>`. The return value is empty if
  /// `*this` is empty, otherwise an `expected<U>` is constructed from the
  /// return value of `std::invoke(std::forward<F>(f), value())` and is
  /// returned. \group map \synopsis template <class F> auto map(F &&f) &;
  template <class F> TL_EXPECTED_11_CONSTEXPR auto map(F &&f) & {
    return map_impl(*this, std::forward<F>(f));
  }

  template <class F> TL_EXPECTED_11_CONSTEXPR auto map(F &&f) && {
    return map_impl(std::move(*this), std::forward<F>(f));
  }

  template <class F> constexpr auto map(F &&f) const & {
    return map_impl(*this, std::forward<F>(f));
  }

  template <class F> constexpr auto map(F &&f) const && {
    return map_impl(std::move(*this), std::forward<F>(f));
  }
#else
  /// \brief Carries out some operation on the stored object if there is one.
  /// \returns Let `U` be the result of `std::invoke(std::forward<F>(f),
  /// value())`. Returns a `std::expected<U>`. The return value is empty if
  /// `*this` is empty, otherwise an `expected<U>` is constructed from the
  /// return value of `std::invoke(std::forward<F>(f), value())` and is
  /// returned. \group map \synopsis template <class F> auto map(F &&f) &;
  template <class F>
  TL_EXPECTED_11_CONSTEXPR decltype(map_impl(std::declval<expected &>(),
                                             std::declval<F &&>()))
  map(F &&f) & {
    return map_impl(*this, std::forward<F>(f));
  }

  template <class F>
  TL_EXPECTED_11_CONSTEXPR decltype(map_impl(std::declval<expected &&>(),
                                             std::declval<F &&>()))
  map(F &&f) && {
    return map_impl(std::move(*this), std::forward<F>(f));
  }

  template <class F>
  constexpr decltype(map_impl(std::declval<const expected &>(),
                              std::declval<F &&>()))
  map(F &&f) const & {
    return map_impl(*this, std::forward<F>(f));
  }

#ifndef TL_EXPECTED_NO_CONSTRR
  template <class F>
  constexpr decltype(map_impl(std::declval<const expected &&>(),
                              std::declval<F &&>()))
  map(F &&f) const && {
    return map_impl(std::move(*this), std::forward<F>(f));
  }
#endif
#endif

#if defined(TL_EXPECTED_CXX14) && !defined(TL_EXPECTED_GCC49) && !defined(TL_EXPECTED_GCC54)
  /// \brief Carries out some operation on the stored object if there is one.
  /// \returns Let `U` be the result of `std::invoke(std::forward<F>(f),
  /// value())`. Returns a `std::expected<U>`. The return value is empty if
  /// `*this` is empty, otherwise an `expected<U>` is constructed from the
  /// return value of `std::invoke(std::forward<F>(f), value())` and is
  /// returned. \group map_error \synopsis template <class F> auto map_error(F
  /// &&f) &;
  template <class F> TL_EXPECTED_11_CONSTEXPR auto map_error(F &&f) & {
    return map_error_impl(*this, std::forward<F>(f));
  }

  template <class F> TL_EXPECTED_11_CONSTEXPR auto map_error(F &&f) && {
    return map_error_impl(std::move(*this), std::forward<F>(f));
  }

  template <class F> constexpr auto map_error(F &&f) const & {
    return map_error_impl(*this, std::forward<F>(f));
  }

  template <class F> constexpr auto map_error(F &&f) const && {
    return map_error_impl(std::move(*this), std::forward<F>(f));
  }
#else
  /// \brief Carries out some operation on the stored object if there is one.
  /// \returns Let `U` be the result of `std::invoke(std::forward<F>(f),
  /// value())`. Returns a `std::expected<U>`. The return value is empty if
  /// `*this` is empty, otherwise an `expected<U>` is constructed from the
  /// return value of `std::invoke(std::forward<F>(f), value())` and is
  /// returned. \group map_error \synopsis template <class F> auto map_error(F
  /// &&f) &;
  template <class F>
  TL_EXPECTED_11_CONSTEXPR decltype(map_error_impl(std::declval<expected &>(),
                                                   std::declval<F &&>()))
  map_error(F &&f) & {
    return map_error_impl(*this, std::forward<F>(f));
  }

  template <class F>
  TL_EXPECTED_11_CONSTEXPR decltype(map_error_impl(std::declval<expected &&>(),
                                                   std::declval<F &&>()))
  map_error(F &&f) && {
    return map_error_impl(std::move(*this), std::forward<F>(f));
  }

  template <class F>
  constexpr decltype(map_error_impl(std::declval<const expected &>(),
                                    std::declval<F &&>()))
  map_error(F &&f) const & {
    return map_error_impl(*this, std::forward<F>(f));
  }

#ifndef TL_EXPECTED_NO_CONSTRR
  template <class F>
  constexpr decltype(map_error_impl(std::declval<const expected &&>(),
                                    std::declval<F &&>()))
  map_error(F &&f) const && {
    return map_error_impl(std::move(*this), std::forward<F>(f));
  }
#endif
#endif

  constexpr expected() = default;

  template <class... Args,
            detail::enable_if_t<std::is_constructible<T, Args &&...>::value> * =
                nullptr>
  constexpr expected(in_place_t, Args &&... args)
      : storage_base(in_place, std::forward<Args>(args)...) {}

  template <class U, class... Args,
            detail::enable_if_t<std::is_constructible<
                T, std::initializer_list<U> &, Args &&...>::value> * = nullptr>
  constexpr expected(in_place_t, std::initializer_list<U> il, Args &&... args)
      : storage_base(in_place, il, std::forward<Args>(args)...) {}

  template <class G = E,
            detail::enable_if_t<std::is_constructible<E, const G &>::value> * =
                nullptr,
            detail::enable_if_t<!std::is_convertible<const G &, E>::value> * =
                nullptr>
  explicit constexpr expected(unexpected<G> const &e)
      : storage_base(unexpect, e) {}

  template <
      class G = E,
      detail::enable_if_t<std::is_constructible<E, const G &>::value> * =
          nullptr,
      detail::enable_if_t<std::is_convertible<const G &, E>::value> * = nullptr>
  constexpr expected(unexpected<G> const &e) : storage_base(unexpect, e) {}

  template <
      class G = E,
      detail::enable_if_t<std::is_constructible<E, G &&>::value> * = nullptr,
      detail::enable_if_t<!std::is_convertible<G &&, E>::value> * = nullptr>
  explicit constexpr expected(unexpected<G> &&e) noexcept(
      std::is_nothrow_constructible<E, G &&>::value)
      : storage_base(unexpect, std::move(e)) {}

  template <
      class G = E,
      detail::enable_if_t<std::is_constructible<E, G &&>::value> * = nullptr,
      detail::enable_if_t<std::is_convertible<G &&, E>::value> * = nullptr>
  constexpr expected(unexpected<G> &&e) noexcept(
      std::is_nothrow_constructible<E, G &&>::value)
      : storage_base(unexpect, std::move(e)) {}

  template <class... Args,
            detail::enable_if_t<std::is_constructible<E, Args &&...>::value> * =
                nullptr>
  constexpr explicit expected(unexpect_t, Args &&... args)
      : storage_base(unexpect, std::forward<Args>(args)...) {}

  template <class U, class... Args,
            detail::enable_if_t<std::is_constructible<
                E, std::initializer_list<U> &, Args &&...>::value> * = nullptr>
  constexpr explicit expected(unexpect_t, std::initializer_list<U> il,
                              Args &&... args)
      : storage_base(unexpect, il, std::forward<Args>(args)...) {}

  constexpr expected(const expected &rhs) {
    if (rhs.has_value()) {
      ::new (valptr()) T(*rhs);
    } else {
      ::new (errptr()) unexpected_type(unexpected<E>(rhs.error()));
    }
  }

  // TODO SFINAE
  constexpr expected(expected &&rhs) noexcept(
      std::is_nothrow_move_constructible<T>::value
          &&std::is_nothrow_move_constructible<E>::value) {
    if (rhs.has_value()) {
      ::new (valptr()) T(std::move(*rhs));
    } else {
      ::new (errptr()) unexpected_type(unexpected<E>(std::move(rhs.error())));
    }
  }

  // TODO SFINAE
  template <class U, class G,
            detail::enable_if_t<(!std::is_convertible<U const &, T>::value ||
                                 !std::is_convertible<G const &, E>::value)> * =
                nullptr>
  explicit constexpr expected(const expected<U, G> &rhs) {
    if (rhs.has_value()) {
      ::new (valptr()) T(*rhs);
    } else {
      ::new (errptr()) unexpected_type(unexpected<E>(rhs.error()));
    }
  }

  // TODO SFINAE
  template <
      class U, class G,
      detail::enable_if_t<(!std::is_convertible<U &&, T>::value ||
                           !std::is_convertible<G &&, E>::value)> * = nullptr>
  explicit constexpr expected(const expected<U, G> &rhs) {
    if (rhs.has_value()) {
      ::new (valptr()) T(*rhs);
    } else {
      ::new (errptr()) unexpected_type(unexpected<E>(rhs.error()));
    }
  }

  // TODO SFINAE
  template <
      class U, class G,
      detail::enable_if_t<(std::is_convertible<U &&, T>::value ||
                           std::is_convertible<G &&, E>::value)> * = nullptr>
  constexpr expected(expected<U, G> &&rhs) {
    if (rhs.has_value()) {
      ::new (valptr()) T(std::move(*rhs));
    } else {
      ::new (errptr()) unexpected_type(unexpected<E>(std::move(rhs.error())));
    }
  }

  // TODO SFINAE
  template <class U = T, detail::enable_if_t<
                             !std::is_convertible<U &&, T>::value> * = nullptr>
  explicit constexpr expected(U &&v) : expected(in_place, std::forward<U>(v)) {}

  // TODO SFINAE
  template <class U = T, detail::enable_if_t<
                             std::is_convertible<U &&, T>::value> * = nullptr>
  constexpr expected(U &&v) : expected(in_place, std::forward<U>(v)) {}

  // TODO
  expected &operator=(const expected &);
  expected &operator=(expected &&) noexcept;
  template <class U = T> expected &operator=(U &&);
  template <class G = E> expected &operator=(const unexpected<G> &);
  template <class G = E> expected &operator=(unexpected<G> &&) noexcept;
  template <class... Args> void emplace(Args &&...);
  template <class U, class... Args>
  void emplace(std::initializer_list<U>, Args &&...);

  // TODO SFINAE
  void swap(expected &rhs) noexcept(
      std::is_nothrow_move_constructible<T>::value &&noexcept(
          swap(std::declval<T &>(), std::declval<T &>())) &&
      std::is_nothrow_move_constructible<E>::value &&
      noexcept(swap(std::declval<E &>(), std::declval<E &>()))) {
    if (has_value() && rhs.has_value()) {
      using std::swap;
      swap(val(), rhs.val());
    } else if (!has_value() && rhs.has_value()) {
      using std::swap;
      swap(err(), rhs.err());
    } else if (has_value()) {
      auto temp = std::move(rhs.err());
      ::new (rhs.valptr()) T(val());
      ::new (errptr()) unexpected_type(std::move(temp));
      std::swap(this->m_has_val, rhs.m_has_val);
    } else {
      auto temp = std::move(this->err());
      ::new (valptr()) T(rhs.val());
      ::new (errptr()) unexpected_type(std::move(temp));
      std::swap(this->m_has_val, rhs.m_has_val);
    }
  }

  constexpr const T *operator->() const { return valptr(); }
  constexpr T *operator->() { return valptr(); }
  constexpr const T &operator*() const & { return val(); }
  constexpr T &operator*() & { return val(); }
  constexpr const T &&operator*() const && { return std::move(val()); }
  constexpr T &&operator*() && { return std::move(val()); }
  constexpr explicit operator bool() const noexcept { return this->m_has_val; }
  constexpr bool has_value() const noexcept { return this->m_has_val; }
  constexpr const T &value() const & {
    if (!has_value())
      throw bad_expected_access<E>(err());
    return val();
  }
  constexpr T &value() & {
    if (!has_value())
      throw bad_expected_access<E>(err());
    return val();
  }
  constexpr const T &&value() const && {
    if (!has_value())
      throw bad_expected_access<E>(err());
    return std::move(val());
  }
  constexpr T &&value() && {
    if (!has_value())
      throw bad_expected_access<E>(err());
    return std::move(val());
  }
  constexpr const E &error() const & { return err().value(); }
  constexpr E &error() & { return err().value(); }
  constexpr const E &&error() const && { return std::move(err().value()); }
  constexpr E &&error() && { return std::move(err().value()); }
  template <class U> constexpr T value_or(U &&v) const & {
    static_assert(std::is_copy_constructible<T>::value &&
                      std::is_convertible<U &&, T>::value,
                  "T must be copy-constructible and convertible to from U&&");
    return bool(*this) ? **this : static_cast<T>(std::forward<U>(v));
  }
  template <class U> T value_or(U &&v) && {
    static_assert(std::is_move_constructible<T>::value &&
                      std::is_convertible<U &&, T>::value,
                  "T must be move-constructible and convertible to from U&&");
    return bool(*this) ? std::move(**this) : static_cast<T>(std::forward<U>(v));
  }
};

    namespace detail {
  template <class Exp> using err_t = typename detail::decay_t<Exp>::error_type;
  template <class Exp, class Ret> using ret_t = expected<Ret, err_t<Exp>>;

#ifdef TL_EXPECTED_CXX14
  template <class Exp, class F,
            class Ret = decltype(detail::invoke(std::declval<F>(),
                                                *std::declval<Exp>())),
            detail::enable_if_t<!std::is_void<Ret>::value> * = nullptr>
   constexpr auto map_impl(Exp &&exp, F &&f) {
    using result = ret_t<Exp, Ret>;
    return exp.has_value() ? result(detail::invoke(std::forward<F>(f),
                                                   *std::forward<Exp>(exp)))
                           : result(unexpect, std::forward<Exp>(exp).error());
  }

  template <class Exp, class F,
            class Ret = decltype(detail::invoke(std::declval<F>(),
                                                *std::declval<Exp>())),
            detail::enable_if_t<std::is_void<Ret>::value> * = nullptr>
   auto map_impl(Exp &&exp, F &&f) {
    using result = expected<monostate, err_t<Exp>>;
    if (exp.has_value()) {
      detail::invoke(std::forward<F>(f), *std::forward<Exp>(exp));
      return result(monostate{});
    }

    return result(unexpect, std::forward<Exp>(exp).error());
  }
#else
  template <class Exp, class F,
            class Ret = decltype(detail::invoke(std::declval<F>(),
                                                *std::declval<Exp>())),
            detail::enable_if_t<!std::is_void<Ret>::value> * = nullptr>

   constexpr auto map_impl(Exp &&exp, F &&f) -> ret_t<Exp, Ret> {
    using result = ret_t<Exp, Ret>;

    return exp.has_value() ? result(detail::invoke(std::forward<F>(f),
                                                   *std::forward<Exp>(exp)))
                           : result(unexpect, std::forward<Exp>(exp).error());
  }

  template <class Exp, class F,
            class Ret = decltype(detail::invoke(std::declval<F>(),
                                                *std::declval<Exp>())),
            detail::enable_if_t<std::is_void<Ret>::value> * = nullptr>

   auto map_impl(Exp &&exp, F &&f) -> expected<monostate, err_t<Exp>> {
    if (exp.has_value()) {
      detail::invoke(std::forward<F>(f), *std::forward<Exp>(exp));
      return tl::monostate{};
    }

    return unexpected<err_t<Exp>>(std::forward<Exp>(exp).error());
  }
#endif

#if defined(TL_EXPECTED_CXX14) && !defined(TL_EXPECTED_GCC49) && !defined(TL_EXPECTED_GCC54)
  template <class Exp, class F,
            class Ret = decltype(detail::invoke(std::declval<F>(),
                                                *std::declval<Exp>()))>
   constexpr auto map_error_impl(Exp &&exp, F &&f) {
    using result = ret_t<Exp, Ret>;
    return exp.has_value()
               ? result(*std::forward<Exp>(exp))
               : result(unexpect,
                        detail::invoke(std::forward<F>(f),
                                       std::forward<Exp>(exp).error()));
  }
#else
  template <class Exp, class F,
            class Ret = decltype(detail::invoke(std::declval<F>(),
                                                *std::declval<Exp>()))>
   constexpr auto map_error_impl(Exp &&exp, F &&f) -> ret_t<Exp, Ret> {
    using result = ret_t<Exp, Ret>;

    return exp.has_value()
               ? result(*std::forward<Exp>(exp))
               : result(unexpect,
                        detail::invoke(std::forward<F>(f),
                                       std::forward<Exp>(exp).error()));
  }
#endif
    }

// TODO
template <class E> class expected<void, E> {};

template <class T, class E>
constexpr bool operator==(const expected<T, E> &lhs,
                          const expected<T, E> &rhs) {
  return (lhs.has_value() != rhs.has_value())
             ? false
             : (!lhs.has_value() ? lhs.error() == rhs.error() : *lhs == *rhs);
}
template <class T, class E>
constexpr bool operator!=(const expected<T, E> &lhs,
                          const expected<T, E> &rhs) {
  return (lhs.has_value() != rhs.has_value())
             ? true
             : (!lhs.has_value() ? lhs.error() != rhs.error() : *lhs != *rhs);
}

template <class T, class E>
constexpr bool operator==(const expected<T, E> &x, const T &v) {
  return x.has_value() ? *x == v : false;
}
template <class T, class E>
constexpr bool operator==(const T &v, const expected<T, E> &x) {
  return x.has_value() ? *x == v : false;
}
template <class T, class E>
constexpr bool operator!=(const expected<T, E> &x, const T &v) {
  return x.has_value() ? *x != v : true;
}
template <class T, class E>
constexpr bool operator!=(const T &v, const expected<T, E> &x) {
  return x.has_value() ? *x != v : true;
}

template <class T, class E>
constexpr bool operator==(const expected<T, E> &x, const unexpected<E> &e) {
  return x.has_value() ? true : x.error() == e.value();
}
template <class T, class E>
constexpr bool operator==(const unexpected<E> &e, const expected<T, E> &x) {
  return x.has_value() ? true : x.error() == e.value();
}
template <class T, class E>
constexpr bool operator!=(const expected<T, E> &x, const unexpected<E> &e) {
  return x.has_value() ? false : x.error() != e.value();
}
template <class T, class E>
constexpr bool operator!=(const unexpected<E> &e, const expected<T, E> &x) {
  return x.has_value() ? false : x.error() != e.value();
}

// TODO is_swappable
template <class T, class E,
          detail::enable_if_t<std::is_move_constructible<T>::value &&
                              std::is_move_constructible<E>::value> * = nullptr>
void swap(expected<T, E> &lhs,
          expected<T, E> &rhs) noexcept(noexcept(lhs.swap(rhs))) {
  lhs.swap(rhs);
}
} // namespace tl

#endif
