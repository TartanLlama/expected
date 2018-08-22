#include "catch.hpp"
#include "expected.hpp"

#include <string>

using std::string;

tl::expected<int, string> getInt3(int val) { return val; }

tl::expected<int, string> getInt2(int val) { return val; }

tl::expected<int, string> getInt1() { return getInt2(5).and_then(getInt3); }

TEST_CASE("Issue 1", "[issues.1]") { getInt1(); }

tl::expected<int, int> operation1() { return 42; }

tl::expected<std::string, int> operation2(int const val) { return "Bananas"; }

TEST_CASE("Issue 17", "[issues.17]") {
  auto const intermediate_result = operation1();

  intermediate_result.and_then(operation2);
}

struct a {};
struct b : a {};

TEST_CASE("Issue 26", "[issues.26]") {
  tl::expected<a, int> exp = tl::expected<b, int>(tl::unexpect, 0);
  REQUIRE(!exp.has_value());
}

struct foo {
  foo() = default;
  foo(foo &) = delete;
  foo(foo &&){};
};

TEST_CASE("Issue 29", "[issues.29]") {
  std::vector<foo> v;
  v.emplace_back();
  tl::expected<std::vector<foo>, int> ov = std::move(v);
  REQUIRE(ov->size() == 1);
}

tl::expected<int, std::string> error() {
  return tl::make_unexpected(std::string("error1 "));
}
std::string maperror(std::string s) { return s + "maperror "; }

TEST_CASE("Issue 30", "[issues.30]") {
  error().map_error(maperror);
}
