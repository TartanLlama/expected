#include "catch.hpp"
#include "expected.hpp"

#include <string>

using std::string;

tl::expected<int, string> getInt3(int val)
{
    return val;
}

tl::expected<int, string> getInt2(int val)
{
    return val;
}

tl::expected<int, string> getInt1()
{
    return getInt2(5).and_then(getInt3);
}


TEST_CASE("Issue 1", "[issues.1]") {
    getInt1();
}
