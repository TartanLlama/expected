#include "catch.hpp"
#include "expected.hpp"

#define TOKENPASTE(x, y) x##y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)
#define STATIC_REQUIRE(e)                                                      \
  constexpr bool TOKENPASTE2(rqure, __LINE__) = e;                             \
  REQUIRE(e);

TEST_CASE("Map extensions", "[extensions.map]") {
  auto mul2 = [](auto a) { return a * 2; };
  auto ret_void = [](auto a) {};

  {
    tl::expected<int, int> e = 21;
    auto ret = e.map(mul2);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = e.map(mul2);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = std::move(e).map(mul2);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = std::move(e).map(mul2);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.map(mul2);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.map(mul2);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).map(mul2);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).map(mul2);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = e.map(ret_void);
    REQUIRE(ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<tl::monostate, int>>::value));
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = e.map(ret_void);
    REQUIRE(ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<tl::monostate, int>>::value));
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = std::move(e).map(ret_void);
    REQUIRE(ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<tl::monostate, int>>::value));
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = std::move(e).map(ret_void);
    REQUIRE(ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<tl::monostate, int>>::value));
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.map(ret_void);
    REQUIRE(!ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<tl::monostate, int>>::value));
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.map(ret_void);
    REQUIRE(!ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<tl::monostate, int>>::value));
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).map(ret_void);
    REQUIRE(!ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<tl::monostate, int>>::value));
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).map(ret_void);
    REQUIRE(!ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<tl::monostate, int>>::value));
  }
}

TEST_CASE("And then extensions", "[extensions.and_then]") {
  auto succeed = [](auto a) { return tl::expected<int, int>(21 * 2); };
  auto fail = [](auto a) { return tl::expected<int, int>(tl::unexpect, 17); };

  {
    tl::expected<int, int> e = 21;
    auto ret = e.and_then(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = e.and_then(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = std::move(e).and_then(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = std::move(e).and_then(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = e.and_then(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error()  == 17);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = e.and_then(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = std::move(e).and_then(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = std::move(e).and_then(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.and_then(succeed);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.and_then(succeed);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).and_then(succeed);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).and_then(succeed);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.and_then(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.and_then(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).and_then(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).and_then(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }
}
