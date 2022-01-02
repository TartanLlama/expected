#include <catch2/catch.hpp>
#include <tl/expected.hpp>

#define TOKENPASTE(x, y) x##y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)
#define STATIC_REQUIRE(e)                                                      \
  constexpr bool TOKENPASTE2(rqure, __LINE__) = e;                             \
  REQUIRE(e);

TEST_CASE("Map extensions", "[extensions.map]") {
  auto mul2 = [](int a) { return a * 2; };
  auto ret_void = [](int a) {};

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
        (std::is_same<decltype(ret), tl::expected<void, int>>::value));
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = e.map(ret_void);
    REQUIRE(ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<void, int>>::value));
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = std::move(e).map(ret_void);
    REQUIRE(ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<void, int>>::value));
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = std::move(e).map(ret_void);
    REQUIRE(ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<void, int>>::value));
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.map(ret_void);
    REQUIRE(!ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<void, int>>::value));
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.map(ret_void);
    REQUIRE(!ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<void, int>>::value));
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).map(ret_void);
    REQUIRE(!ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<void, int>>::value));
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).map(ret_void);
    REQUIRE(!ret);
    STATIC_REQUIRE(
        (std::is_same<decltype(ret), tl::expected<void, int>>::value));
  }


  // mapping functions which return references
  {
    tl::expected<int, int> e(42);
    auto ret = e.map([](int& i) -> int& { return i; });
    REQUIRE(ret);
    REQUIRE(ret == 42);
  }
}

TEST_CASE("Map on expected<void>", "[extensions.map.void]") {
  {
    tl::expected<void, int> a;
    REQUIRE(a.has_value());
    bool called = false;
    tl::expected<void, int> b = a.map([&](){ called = true; });
    REQUIRE(called);
    REQUIRE(b.has_value());
  }
  {
    tl::expected<void, int> a = tl::make_unexpected(42);
    REQUIRE(!a.has_value());
    bool called = false;
    tl::expected<void, int> b = a.map([&](){ called = true; });
    REQUIRE(!called);
    REQUIRE(!b.has_value());
    REQUIRE(b.error() == 42);
  }
  {
    tl::expected<void, int> a;
    REQUIRE(a.has_value());
    bool called = false;
    tl::expected<int, int> b = a.map([&](){ called = true; return 3; });
    REQUIRE(called);
    REQUIRE(b.value() == 3);
  }
  {
    tl::expected<void, int> a = tl::make_unexpected(42);
    REQUIRE(!a.has_value());
    bool called = false;
    tl::expected<int, int> b = a.map([&](){ called = true; return 3; });
    REQUIRE(!called);
    REQUIRE(!b.has_value());
    REQUIRE(b.error() == 42);
  }
}

TEST_CASE("Map error extensions", "[extensions.map_error]") {
  auto mul2 = [](int a) { return a * 2; };
  auto ret_void = [](int a) {};

  {
    tl::expected<int, int> e = 21;
    auto ret = e.map_error(mul2);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = e.map_error(mul2);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = std::move(e).map_error(mul2);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = std::move(e).map_error(mul2);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.map_error(mul2);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 42);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.map_error(mul2);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 42);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).map_error(mul2);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 42);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).map_error(mul2);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 42);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = e.map_error(ret_void);
    REQUIRE(ret);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = e.map_error(ret_void);
    REQUIRE(ret);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = std::move(e).map_error(ret_void);
    REQUIRE(ret);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = std::move(e).map_error(ret_void);
    REQUIRE(ret);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.map_error(ret_void);
    REQUIRE(!ret);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.map_error(ret_void);
    REQUIRE(!ret);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).map_error(ret_void);
    REQUIRE(!ret);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).map_error(ret_void);
    REQUIRE(!ret);
  }

}

template <class Exp, class F>
constexpr auto hasAndThen_impl(int, Exp&& e, F&& f)
  -> decltype(std::forward<Exp>(e).and_then(std::forward<F>(f)), true) {
  return true;
}

template <class Exp, class F>
constexpr bool hasAndThen_impl(long, Exp&&, F&&) { return false; }

template <class Exp, class F>
constexpr bool hasAndThen(Exp&& e, F&& f) {
  return hasAndThen_impl(42, std::forward<Exp>(e), std::forward<F>(f));
}

TEST_CASE("and_then is SFINAE-friendly", "[extensions.and_then.sfinae]") {
  auto succeed = [](int) { return tl::expected<int, int>(21 * 2); };

  {
    tl::expected<int, int> e = 21;
    STATIC_REQUIRE(hasAndThen(e, succeed));
    STATIC_REQUIRE(hasAndThen(std::move(e), succeed));
    STATIC_REQUIRE(hasAndThen(e, std::move(succeed)));
    STATIC_REQUIRE(hasAndThen(std::move(e), std::move(succeed)));
  }
  {
    const tl::expected<int, int> ce = 21;
    STATIC_REQUIRE(hasAndThen(ce, succeed));
    STATIC_REQUIRE(hasAndThen(std::move(ce), succeed));
    STATIC_REQUIRE(hasAndThen(ce, std::move(succeed)));
    STATIC_REQUIRE(hasAndThen(std::move(ce), std::move(succeed)));
  }
  {
    tl::expected<int, int> e = 21;
    STATIC_REQUIRE(!hasAndThen(e, 42));

    auto wrongParamType = [](char *) { return tl::expected<int, int>(); };
    STATIC_REQUIRE(!hasAndThen(e, wrongParamType));

    auto wrongParamType2 = []() { return tl::expected<int, int>(); };
    STATIC_REQUIRE(!hasAndThen(e, wrongParamType2));

    auto wrongReturnType = [](int) { return 21; };
    STATIC_REQUIRE(!hasAndThen(e, wrongReturnType));

    auto wrongReturnType2 = [](int) { return tl::expected<char*, char*>(); };
    STATIC_REQUIRE(!hasAndThen(e, wrongReturnType2));

    auto voidReturnType = [](int) {};
    STATIC_REQUIRE(!hasAndThen(e, voidReturnType));

    auto voidReturnWrongParam = [](char *) {};
    STATIC_REQUIRE(!hasAndThen(e, voidReturnWrongParam));
  }
  {
    tl::expected<int, int> e = 21;
    const tl::expected<int, int> ce = 21;

    auto lvalueParam = [](int&) { return tl::expected<int, int>(); };
    STATIC_REQUIRE(hasAndThen(e, lvalueParam));
    STATIC_REQUIRE(!hasAndThen(std::move(e), lvalueParam));
    STATIC_REQUIRE(!hasAndThen(ce, lvalueParam));
    STATIC_REQUIRE(!hasAndThen(std::move(ce), lvalueParam));

    auto rvalueParam = [](int&&) { return tl::expected<int, int>(); };
    STATIC_REQUIRE(!hasAndThen(e, rvalueParam));
    STATIC_REQUIRE(hasAndThen(std::move(e), rvalueParam));
    STATIC_REQUIRE(!hasAndThen(ce, rvalueParam));
    STATIC_REQUIRE(!hasAndThen(std::move(ce), rvalueParam));
  }
}

TEST_CASE("And then extensions", "[extensions.and_then]") {
  auto succeed = [](int a) { return tl::expected<int, int>(21 * 2); };
  auto fail = [](int a) { return tl::expected<int, int>(tl::unexpect, 17); };

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
    REQUIRE(ret.error() == 17);
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

TEST_CASE("or_else", "[extensions.or_else]") {
  using eptr = std::unique_ptr<int>;
  auto succeed = [](int a) { return tl::expected<int, int>(21 * 2); };
  auto succeedptr = [](eptr e) { return tl::expected<int,eptr>(21*2);};
  auto fail =    [](int a) { return tl::expected<int,int>(tl::unexpect, 17);};
  auto efail =   [](eptr e) { *e = 17;return tl::expected<int,eptr>(tl::unexpect, std::move(e));};
  auto failptr = [](eptr e) { return tl::expected<int,eptr>(tl::unexpect, std::move(e));};
  auto failvoid = [](int) {};
  auto failvoidptr = [](const eptr&) { /* don't consume */};
  auto consumeptr = [](eptr) {};
  auto make_u_int = [](int n) { return std::unique_ptr<int>(new int(n));};

  {
    tl::expected<int, int> e = 21;
    auto ret = e.or_else(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = e.or_else(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = std::move(e).or_else(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    tl::expected<int, eptr> e = 21;
    auto ret = std::move(e).or_else(succeedptr);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = std::move(e).or_else(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = e.or_else(fail);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = e.or_else(fail);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    tl::expected<int, int> e = 21;
    auto ret = std::move(e).or_else(fail);
    REQUIRE(ret);
    REQUIRE(ret == 21);
  }


  {
    tl::expected<int, eptr> e = 21;
    auto ret = std::move(e).or_else(efail);
    REQUIRE(ret);
    REQUIRE(ret == 21);
  }

  {
    const tl::expected<int, int> e = 21;
    auto ret = std::move(e).or_else(fail);
    REQUIRE(ret);
    REQUIRE(*ret == 21);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.or_else(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.or_else(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).or_else(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    tl::expected<int, eptr> e(tl::unexpect, make_u_int(21));
    auto ret = std::move(e).or_else(succeedptr);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).or_else(succeed);
    REQUIRE(ret);
    REQUIRE(*ret == 42);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.or_else(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.or_else(failvoid);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.or_else(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = e.or_else(failvoid);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).or_else(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).or_else(failvoid);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

  {
    tl::expected<int, eptr> e(tl::unexpect, make_u_int(21));
    auto ret = std::move(e).or_else(failvoidptr);
    REQUIRE(!ret);
    REQUIRE(*ret.error() == 21);
  }

  {
    tl::expected<int, eptr> e(tl::unexpect, make_u_int(21));
    auto ret = std::move(e).or_else(consumeptr);
    REQUIRE(!ret);
    REQUIRE(ret.error() == nullptr);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).or_else(fail);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 17);
  }

  {
    const tl::expected<int, int> e(tl::unexpect, 21);
    auto ret = std::move(e).or_else(failvoid);
    REQUIRE(!ret);
    REQUIRE(ret.error() == 21);
  }

}
struct S {
    int x;
};

struct F {
    int x;
};

TEST_CASE("14", "[issue.14]") {
    auto res = tl::expected<S,F>{tl::unexpect, F{}};

    res.map_error([](F f) {

    });
}

TEST_CASE("32", "[issue.32]") {
    int i = 0;
    tl::expected<void, int> a;
    a.map([&i]{i = 42;});
    REQUIRE(i == 42);

    auto x = a.map([]{return 42;});
    REQUIRE(*x == 42);
}
