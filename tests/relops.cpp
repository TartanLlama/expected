#include <catch2/catch.hpp>
#include <tl/expected.hpp>

TEST_CASE("Relational operators", "[relops]") {
  tl::expected<int, int> o1 = 42;
  tl::expected<int, int> o2{tl::unexpect, 0};
  const tl::expected<int, int> o3 = 42;

  REQUIRE(o1 == o1);
  REQUIRE(o1 != o2);
  REQUIRE(o1 == o3);
  REQUIRE(o3 == o3);

  tl::expected<void, int> o6;

  REQUIRE(o6 == o6);
}

TEST_CASE("Relational operators unexpected", "[relops]") {
  tl::unexpected<int> zero(0);
  tl::unexpected<int> one(1);

  REQUIRE(one == one);
  REQUIRE(one != zero);
  REQUIRE(zero < one);
  REQUIRE(zero <= one);
  REQUIRE(one <= one);
  REQUIRE(one > zero);
  REQUIRE(one >= zero);
  REQUIRE(one >= one);
}

TEST_CASE("Relational operators expected vs unexpected", "[relops]") {
  tl::expected<int, int> ezero(tl::unexpect, 0);
  tl::unexpected<int> uzero(0);
  tl::unexpected<int> uone(1);

  REQUIRE(ezero == uzero);
  REQUIRE(ezero != uone);
  REQUIRE(uzero == ezero);
  REQUIRE(uone != ezero);
}
