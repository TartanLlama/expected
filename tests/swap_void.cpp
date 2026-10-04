#include <catch2/catch.hpp>
#include <tl/expected.hpp>

#include <initializer_list>
#include <type_traits>
#include <utility>

namespace {
int error_swap_calls = 0;

template <bool MoveNoexcept, bool SwapNoexcept> struct swap_error {
  explicit swap_error(int value) : value(value) {}
  swap_error(const swap_error &) = delete;
  swap_error &operator=(const swap_error &) = delete;
  swap_error(swap_error &&other) noexcept(MoveNoexcept) : value(other.value) {}
  swap_error &operator=(swap_error &&) = delete;

  friend void swap(swap_error &lhs, swap_error &rhs) noexcept(SwapNoexcept) {
    ++error_swap_calls;
    using std::swap;
    swap(lhs.value, rhs.value);
  }

  int value;
};

struct immovable_error {
  immovable_error() = default;
  immovable_error(const immovable_error &) = delete;
  immovable_error(immovable_error &&) = delete;
  friend void swap(immovable_error &, immovable_error &) noexcept {}
};

struct unswappable_error {
  unswappable_error() = default;
  unswappable_error(unswappable_error &&) = default;
  unswappable_error &operator=(unswappable_error &&) = delete;
};

template <class T, class = void> struct has_member_swap : std::false_type {};
template <class T>
struct has_member_swap<T,
                       decltype(std::declval<T &>().swap(std::declval<T &>()))>
    : std::true_type {};

template <class T, class = void> struct has_free_swap : std::false_type {};
template <class T>
struct has_free_swap<T, decltype(tl::swap(std::declval<T &>(),
                                          std::declval<T &>()))>
    : std::true_type {};

template <class E> void void_swap_test() {
  typedef tl::expected<void, E> result;
  for (bool member : {false, true}) {
    result success1;
    result success2;
    result error1(tl::unexpect, 1);
    result error2(tl::unexpect, 2);

    if (member)
      success1.swap(success2);
    else
      tl::swap(success1, success2);
    REQUIRE(success1.has_value());
    REQUIRE(success2.has_value());

    if (member)
      success1.swap(error1);
    else
      tl::swap(success1, error1);
    REQUIRE_FALSE(success1.has_value());
    REQUIRE(success1.error().value == 1);
    REQUIRE(error1.has_value());

    if (member)
      success1.swap(error1);
    else
      tl::swap(success1, error1);
    REQUIRE(success1.has_value());
    REQUIRE_FALSE(error1.has_value());
    REQUIRE(error1.error().value == 1);

    if (member)
      error1.swap(error2);
    else
      tl::swap(error1, error2);
    REQUIRE_FALSE(error1.has_value());
    REQUIRE_FALSE(error2.has_value());
    REQUIRE(error1.error().value == 2);
    REQUIRE(error2.error().value == 1);
  }
}
} // namespace

TEST_CASE("swap void", "[swap.void]") {
  typedef tl::expected<void, swap_error<true, true>> nothrow_result;
  typedef tl::expected<void, swap_error<false, true>> throwing_move_result;
  static_assert(noexcept(std::declval<nothrow_result &>().swap(
                    std::declval<nothrow_result &>())),
                "");
  static_assert(noexcept(tl::swap(std::declval<nothrow_result &>(),
                                  std::declval<nothrow_result &>())),
                "");
  static_assert(!noexcept(std::declval<throwing_move_result &>().swap(
                    std::declval<throwing_move_result &>())),
                "");
  static_assert(!noexcept(tl::swap(std::declval<throwing_move_result &>(),
                                   std::declval<throwing_move_result &>())),
                "");
#if !defined(_MSC_VER) || _MSC_VER > 1900
  // MSVC 2015 uses a permissive fallback for the swappability traits.
  typedef tl::expected<void, swap_error<true, false>> throwing_swap_result;
  static_assert(!noexcept(std::declval<throwing_swap_result &>().swap(
                    std::declval<throwing_swap_result &>())),
                "");
  static_assert(!noexcept(tl::swap(std::declval<throwing_swap_result &>(),
                                   std::declval<throwing_swap_result &>())),
                "");
  static_assert(!has_member_swap<tl::expected<void, unswappable_error>>::value,
                "");
  static_assert(!has_free_swap<tl::expected<void, unswappable_error>>::value,
                "");
#endif
  static_assert(!has_member_swap<tl::expected<void, immovable_error>>::value,
                "");
  static_assert(!has_free_swap<tl::expected<void, immovable_error>>::value, "");

  void_swap_test<swap_error<true, true>>();
  void_swap_test<swap_error<false, true>>();
  void_swap_test<swap_error<true, false>>();
}

TEST_CASE("swap uses error ADL swap", "[swap.error]") {
  tl::expected<int, swap_error<true, true>> lhs(tl::unexpect, 1);
  tl::expected<int, swap_error<true, true>> rhs(tl::unexpect, 2);
  error_swap_calls = 0;
  lhs.swap(rhs);
  REQUIRE(error_swap_calls == 1);
  REQUIRE(lhs.error().value == 2);
  REQUIRE(rhs.error().value == 1);
  tl::swap(lhs, rhs);
  REQUIRE(error_swap_calls == 2);
  REQUIRE(lhs.error().value == 1);
  REQUIRE(rhs.error().value == 2);
}

#ifdef TL_EXPECTED_EXCEPTIONS_ENABLED
namespace {
struct throwing_error {
  explicit throwing_error(int value) : value(value) {}
  throwing_error(throwing_error &&other) { throw other.value; }
  friend void swap(throwing_error &lhs, throwing_error &rhs) noexcept {
    using std::swap;
    swap(lhs.value, rhs.value);
  }
  int value;
};
} // namespace

TEST_CASE("swap void propagates a throwing error move", "[swap.void]") {
  tl::expected<void, throwing_error> success;
  tl::expected<void, throwing_error> error(tl::unexpect, 42);
  REQUIRE_THROWS_AS(success.swap(error), int);
  REQUIRE(success.has_value());
  REQUIRE_FALSE(error.has_value());
  REQUIRE(error.error().value == 42);
  REQUIRE_THROWS_AS(tl::swap(error, success), int);
  REQUIRE(success.has_value());
  REQUIRE_FALSE(error.has_value());
  REQUIRE(error.error().value == 42);
}
#endif
