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
