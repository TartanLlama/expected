#include <catch2/catch.hpp>
#include <tl/expected.hpp>

struct MoveOnly {
  MoveOnly();
  MoveOnly(MoveOnly&&);
  MoveOnly& operator=(MoveOnly&&);
};

TEST_CASE("Unexpected type properties") {
  STATIC_REQUIRE(std::is_constructible<tl::unexpected<int>, int>::value);
  STATIC_REQUIRE(!std::is_convertible<int, tl::unexpected<int>>::value);
  STATIC_REQUIRE(std::is_trivially_copyable<tl::unexpected<int>>::value);
  STATIC_REQUIRE(!std::is_default_constructible<tl::unexpected<int>>::value);
  STATIC_REQUIRE(std::is_copy_constructible<tl::unexpected<int>>::value);

  STATIC_REQUIRE(std::is_constructible<tl::unexpected<MoveOnly>, MoveOnly>::value);
  STATIC_REQUIRE(!std::is_convertible<MoveOnly, tl::unexpected<MoveOnly>>::value);
  STATIC_REQUIRE(!std::is_trivially_copyable<tl::unexpected<MoveOnly>>::value);
  STATIC_REQUIRE(!std::is_default_constructible<tl::unexpected<MoveOnly>>::value);
  STATIC_REQUIRE(!std::is_copy_constructible<tl::unexpected<MoveOnly>>::value);
  STATIC_REQUIRE(std::is_move_constructible<tl::unexpected<MoveOnly>>::value);
}

TEST_CASE("Unexpected assignment") {
  auto u1 = tl::unexpected<int>(1);
  auto u2 = tl::unexpected<int>(2);

  u1 = u2;
  REQUIRE(u1.value() == 2);
  REQUIRE(u2.value() == 2);
}

TEST_CASE("Unexpected swap") {
  auto u1 = tl::unexpected<int>(1);
  auto u2 = tl::unexpected<int>(2);

  using std::swap;
  swap(u1, u2);
  REQUIRE(u1.value() == 2);
  REQUIRE(u2.value() == 1);
}

TEST_CASE("Unexpected comparisons") {
  auto u1 = tl::unexpected<int>(1);
  auto u2 = tl::unexpected<int>(2);

  REQUIRE(u1 < u2);
  REQUIRE(u1 <= u2);
  REQUIRE(!(u1 > u2));
  REQUIRE(!(u1 >= u2));

  REQUIRE(!(u2 < u1));
  REQUIRE(!(u2 <= u1));
  REQUIRE(u2 > u1);
  REQUIRE(u2 >= u1);

  REQUIRE(!(u1 == u2));
  REQUIRE(u1 != u2);
  REQUIRE(u1 == u1);
  REQUIRE(!(u1 != u1));
}

TEST_CASE("Unexpected comparisons against expected") {
  auto u1 = tl::unexpected<int>(1);
  auto u2 = tl::unexpected<int>(2);
  auto ei = tl::expected<int, int>(1);
  auto ev = tl::expected<void, int>();
  auto eu1 = tl::expected<int, int>(tl::make_unexpected(1));
  auto eu2 = tl::expected<void, int>(tl::make_unexpected(2));

  REQUIRE(u1 != ei);
  REQUIRE(u1 != ev);
  REQUIRE(u1 == eu1);
  REQUIRE(u1 != eu2);

  REQUIRE(u2 != ei);
  REQUIRE(u2 != ev);
  REQUIRE(u2 != eu1);
  REQUIRE(u2 == eu2);

  REQUIRE(ei != u1);
  REQUIRE(ev != u1);
  REQUIRE(eu1 == u1);
  REQUIRE(eu2 != u1);

  REQUIRE(ei != u2);
  REQUIRE(ev != u2);
  REQUIRE(eu1 != u2);
  REQUIRE(eu2 == u2);
}
