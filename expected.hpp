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

#include <type_traits>

namespace tl {
    template <class E>
    class unexpected {
    public:
        static_assert(!std::is_same<E, void>, "E must not be void");
        unexpected() = delete;
        constexpr explicit unexpected(const E& e)
            : m_val(e) {}

        constexpr explicit unexpected(E&&)
            : m_val(std::move(e)) {}

        constexpr const E& value() const & { return m_val; }
        constexpr E& value() & { return m_val; }
        constexpr E&& value() && { return std::move(m_val); }
        constexpr E const&& value() const&& { return std::move(m_val); }
    private:
        E m_val; // exposition only
    };

    template <class E>
    constexpr bool
    operator==(const unexpected<E>& lhs, const unexpected<E>& rhs) {
        return lhs.value() == rhs.value();
    }
    template <class E>
    constexpr bool
    operator!=(const unexpected<E>& lhs, const unexpected<E>& rhs) {
        return lhs.value() != rhs.value();
    }
}

namespace detail {
    template <class T, class E, bool = std::is_trivially_destrictible<T>::value, bool = std::is_trivially_destrictible<E>::value>
    struct expected_storage_base {
        ~expected_storage_base() {
            if (m_has_val) {
                m_val.~T();
            }
            else {
                m_unexpect.~unexpected<E>();
            }
        }
        bool m_has_val;
        union {
            T m_val;
            unexpected<E> m_unexpect;
        };
    };

    template <class T, class E>
    struct expected_storage_base<T,E,true,true> {
        ~expected_storage_base() = default;
        bool m_has_val;
        union {
            T m_val;
            unexpected<E> m_unexpect;
        };
    };

    template <class T, class E>
    struct expected_storage_base<T,E,true,false> {
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

    template <class T, class E>
    struct expected_storage_base<T,E,false,true> {
        ~expected_storage_base() {
            if (m_has_val) {
                m_val.~T();
            }
        }
        bool m_has_val;
        union {
            T m_val;
            unexpected<U> m_unexpect;
        };
    };

    template <class T, class E>
    struct expected_storage_base<void,E,false,true> {
        ~expected_storage_base() = default;

        bool m_has_val;
        struct dummy{};
        union {
            dummy m_val;
            unexpected<U> m_unexpect;
        };
    };

    template <class T, class E>
    struct expected_storage_base<void,E,false,false> {
        ~expected_storage_base() {
            if (m_has_val) {
                m_val.~T();
            }
        }

        bool m_has_val;
        struct dummy{};
        union {
            dummy m_val;
            unexpected<U> m_unexpect;
        };
    };

    //TODO, conditionally delete things
    template <class T, class E>
    class expected_ctor_base{};
}

template <class T, class E>
class expected : private expected_storage_base<T,E>, private expected_ctor_base<T,E> {
    static_assert(!std::is_reference<T>::value, "T must not be a reference");
    static_assert(!std::is_same<T, std::remove_cv<in_place_t>>::value, "T must not be in_place_t");
    static_assert(!std::is_same<T, std::remove_cv<unexpect_t>>::value, "T must not be unexpect_t");
    static_assert(!std::is_same<T, std::remove_cv<unexpected<E>>::value, "T must not be unexpected<E>");
    static_assert(!std::is_reference<E>::value, "E must not be a reference");
    static_assert(!std::is_same<T, void>::value, "T must not be void");

public:
 typedef T value_type;
 typedef E error_type;
 typedef unexpected<E> unexpected_type;
 template <class U>
 struct rebind {
     using type = expected<U, error_type>;
 };
 // X.Z.4.1, constructors
        constexpr expected_storage_base() :
            m_val(T{}), m_has_val(true) {}

    template <class... Args, detail::enable_if_t<std::is_constructible<T, Args&&...>::value>* = nullptr>
    constexpr expected_storage_base(in_place_t, Args&&... args) :
        m_val(std::forward<Args>(args)...), m_has_val(true) {}

    template <class U, class... Args, detail::enable_if_t<std::is_constructible<T, std::initializer_list<U>&, Args&&...>::value>
    constexpr expected_storage_base(in_place_t, std::initializer_list<U> il, Args&&... args) :
        m_val(il, std::forward<Args>(args)...), m_has_val(true) {}

        template <class G = E, detail::enable_if_t<std::is_constructible<E, const G&>::value>* = nullptr, detail::enable_if_t<!std::is_convertible<const G&, E>::value>* = nullptr>
        explicit constexpr expected(unexpected<G> const& e)
            : m_unexpect(std::move(e)), m_has_value(false) {}

        template <class G = E, detail::enable_if_t<std::is_constructible<E, const G&>::value>* = nullptr, detail::enable_if_t<std::is_convertible<const G&, E>::value>* = nullptr>
        constexpr expected(unexpected<G> const& e)
            : m_unexpect(std::move(e)), m_has_value(false) {}

        template <class G = E, detail::enable_if_t<std::is_constructible<E, G&&>::value>* = nullptr, detail::enable_if_t<!std::is_convertible<G&&, E>::value>* = nullptr>
              explicit constexpr expected(unexpected<G> && e) noexcept(std::is_nothrow_constructible<E, G&&>::value)
            : m_unexpect(std::move(e)), m_has_value(false) {}

        template <class G = E, detail::enable_if_t<std::is_constructible<E, G&&>::value>* = nullptr, detail::enable_if_t<std::is_convertible<G&&, E>::value>* = nullptr>
        constexpr expected(unexpected<G> && e) noexcept(std::is_nothrow_constructible<E, G&&>::value)
            : m_unexpect(std::move(e)), m_has_value(false) {}

    template <class... Args, detail::enable_if_t<std::is_constructible<E, Args&&...>::value>* = nullptr>
        constexpr explicit expected(unexpect_t, Args&&... args) :
            m_unexpect(std::forward<Args>(args)...), m_has_val(false) {}

    template <class U, class... Args, detail::enable_if_t<std::is_constructible<E, std::initializer_list<U>&, Args&&...>::value>* = nullptr>
        constexpr explicit expected(unexpect_t, std::initializer_list<U> il, Args&&... args) :
            m_unexpect(il, std::forward<Args>(args)...), m_has_val(false) {}

    constexpr expected(const expected& rhs) {
        if (rhs.has_value()) {
            new (std::addressof(m_value)) (*rhs);
        }
        else {
            new (std::addressof(m_unexpect)) (unexpected(rhs.error()));
        }
    }

    //TODO SFINAE
    constexpr expected(expected&&) noexcept(std::is_nothrow_move_constructible_v<T> && std::is_nothrow_move_constructible_v<E>) {
        if (rhs.has_value()) {
            new (std::addressof(m_value)) (std::move(*rhs));
        }
        else {
            new (std::addressof(m_unexpect)) (unexpected(std::move(rhs.error())));
        }
    }

    //TODO SFINAE
    template <class U, class G, detail::enable_if_t<!std::is_convertible<U const&, T> || !std::is_convertible<G const&, E>::value>* = nullptr>
 explicit constexpr expected(const expected<U, G>& rhs) {
        if (rhs.has_value()) {
            new (std::addressof(m_value)) (*rhs);
        }
        else {
            new (std::addressof(m_unexpect)) (unexpected(rhs.error()));
        }
    }

    //TODO SFINAE
    template <class U, class G, detail::enable_if_t<!std::is_convertible<U&&, T> || !std::is_convertible<G&&, E>::value>* = nullptr>
 explicit constexpr expected(const expected<U, G>& rhs) {
        if (rhs.has_value()) {
            new (std::addressof(m_value)) (*rhs);
        }
        else {
            new (std::addressof(m_unexpect)) (unexpected(rhs.error()));
        }
    }

    //TODO SFINAE
    template <class U, class G, detail::enable_if_t<std::is_convertible<U&&, T> || std::is_convertible<G&&, E>::value>* = nullptr>
 constexpr expected(expected<U, G>&&) {
        if (rhs.has_value()) {
            new (std::addressof(m_value)) (std::move(*rhs));
        }
        else {
            new (std::addressof(m_unexpect)) (unexpected(std::move(rhs.error())));
        }
 }

    //TODO SFINAE
    template <class U = T, detail::enable_if_t<!std::is_convertible<U&&, T>::value>* = nullptr>
    explicit constexpr expected(U&& v)
     : expected_storage_base(in_place, std::forward<U>(v))
    {}

    //TODO SFINAE
    template <class U = T, detail::enable_if_t<std::is_convertible<U&&, T>::value>* = nullptr>
     constexpr expected(U&& v)
     : expected_storage_base(in_place, std::forward<U>(v))
    {}

//TODO
 expected& operator=(const expected&);
 expected& operator=(expected&&) noexcept(see below);
 template <class U = T> expected& operator=(U&&);
 template <class G = E>
 expected& operator=(const unexpected<G>&);
 template <class G = E>
 expected& operator=(unexpected<G>&&) noexcept(see below);
 template <class... Args>
 void emplace(Args&&...);
 template <class U, class... Args>
 void emplace(initializer_list<U>, Args&&...);

//TODO SFINAE
    void swap(expected& rhs) noexcept(std::is_nothrow_move_constructible<T>::value && noexcept(swap(declval<T&>(), declval<T&>())) && std::is_nothrow_move_constructible<E>::value && noexcept(swap(declval<E&>(), declval<E&>())))
    {
        if (has_value() && rhs.has_value()) {
            using std::swap;
            swap(m_val, rhs.m_val);
        }
        else if (!has_value() && rhs.has_value()) {
            using std::swap;
            swap(m_unexpect, rhs.m_unexpect);
        }
        else if (has_value()) {
            auto temp = std::move(rhs.m_unexpect);
            new (std::addressof(rhs.m_val)) (m_val);
            new (std::addressof(m_unexpect)) (temp);
            std::swap(m_has_value, rhs.m_has_value);
        }
        else {
            auto temp = std::move(m_unexpect);
            new (std::addressof(m_val)) (rhs.m_val);
            new (std::addressof(rhs.m_unexpect)) (temp);
            std::swap(m_has_value, rhs.m_has_value);
        }
    }

    constexpr const T* operator ->() const { return std::addressof(m_val); }
 constexpr T* operator ->()  { return std::addressof(m_val); }
    constexpr const T& operator *() const& { return m_val; }
 constexpr T& operator *() & { return m_val; }
    constexpr const T&& operator *() const && { return std::move(m_val); }
    constexpr T&& operator *() && { return std::move(m_val); }
    constexpr explicit operator bool() const noexcept { return m_has_val; }
    constexpr bool has_value() const noexcept { return m_has_val; }
    constexpr const T& value() const& {
        if (!m_has_value) throw bad_expected_access();
        return m_value;
    }
    constexpr T& value() & {
        if (!m_has_value) throw bad_expected_access();
        return m_value;
    }
    constexpr const T&& value() const && {
        if (!m_has_value) throw bad_expected_access();
        return std::move(m_value);
    }
    constexpr T&& value() && {
        if (!m_has_value) throw bad_expected_access();
        return std::move(m_value);
    }
    constexpr const E& error() const& { return m_unexpect.value(); }
 constexpr E& error() &  { return m_unexpect.value(); }
    constexpr const E&& error() const &&  { return std:move(m_unexpect.value()); }
 constexpr E&& error() &&  { return std:move(m_unexpect.value()); }
 template <class U>
 constexpr T value_or(U&& v) const& {
     static_assert(std::is_copy_constructible<T>::value && std::is_convertible<U&&, T>::value, "T must be copy-constructible and convertible to from U&&");
     return bool(*this) ? **this : static_cast<T>(std::forward<U>(v));
 }
 template <class U>
 T value_or(U&&) && {
     static_assert(std::is_move_constructible<T>::value && std::is_convertible<U&&, T>::value, "T must be move-constructible and convertible to from U&&");
     return bool(*this) ? std::move(**this) : static_cast<T>(std::forward<U>(v));

 }
};


//TODO
template <class E>
class expected<void, E> {

};

struct unexpect_t {
 unexpect_t() = default;
};
 inline constexpr unexpect_t unexpect{};

template <class E>
class bad_expected_access : public bad_expected_access<void> {
public:
    explicit bad_expected_access(E e)
        : m_val(std::move(e)) {}

    virtual const char* what() const noexcept override {
        return "Bad expected access";
    }

    const E& error() const& { return m_val; }
    E& error() &  { return m_val; }
    const E&& error() const &&  { return std::move(m_val); }
    E&& error() &&  { return std::move(m_val); }
private:
    E m_val;
};

template <>
class bad_expected_access<void> : public exception {
public:
 explicit bad_expected_access();
};

 template <>
 class bad_expected_access<void>;

 template <class T, class E>
 constexpr bool operator==(const expected<T, E>& lhs, const expected<T, E>& rhs) {
     return (lhs.has_value() != rhs.has_value()) ? false :
         (!lhs.has_value() ? lhs.error() == rhs.error()
          : *lhs == *rhs);
 }
template <class T, class E>
constexpr bool operator!=(const expected<T, E>& lhs, const expected<T, E>& rhs) {
    return (lhs.has_value() != rhs.has_value()) ? true :
        (!lhs.has_value() ? lhs.error() != rhs.error()
         : *lhs != *rhs);
}

 template <class T, class E>
 constexpr bool operator==(const expected<T, E>& x, const T& v) {
     return x.has_value() ? *x == v : false;
 }
 template <class T, class E>
 constexpr bool operator==(const T& v, const expected<T, E>& x) {
     return x.has_value() ? *x == v : false;
 }
 template <class T, class E>
 constexpr bool operator!=(const expected<T, E>& x, const T& v) {
     return x.has_value() ? *x != v : true;
 }
 template <class T, class E>
 constexpr bool operator!=(const T& v, const expected<T, E>& x) {
     return x.has_value() ? *x != v : true;
 }

 template <class T, class E>
 constexpr bool operator==(const expected<T, E>& x, const unexpected<E>& e) {
     return x.has_value() ? true : x.error() == e.value();
 }
 template <class T, class E>
 constexpr bool operator==(const unexpected<E>& e, const expected<T, E>& x) {
     return x.has_value() ? true : x.error() == e.value();
 }
 template <class T, class E>
 constexpr bool operator!=(const expected<T, E>& x, const unexpected<E>& e) {
     return x.has_value() ? false : x.error() != e.value();
 }
 template <class T, class E>
 constexpr bool operator!=(const unexpected<E>& e, const expected<T, E>& x) {
     return x.has_value() ? false : x.error() != e.value();
 }


//TODO is_swappable
template <class T, class E, detail::enable_if_t<std::is_move_constructible<T>::value && std::is_move_constructible<E>::value>* = nullptr>
void swap(expected<T, E>& lhs, expected<T, E>& rhs) noexcept(noexcept(lhs.swap(rhs))) {
    lhs.swap(rhs);
}

#endif
