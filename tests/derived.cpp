#include <catch2/catch.hpp>
#include <tl/expected.hpp>

namespace tl {
    template <typename T, typename E>
    class derived : public tl::expected<T,E>
    {
    public:
        derived() : tl::expected<T,E>() {}
        template <typename G>
        derived(unexpected<G> const &e) : tl::expected<T,E>(e) {}
        derived(const derived& d) : tl::expected<T,E>(d) {}
        derived(derived&& d) : tl::expected<T,E>(std::move(d)) {}
        // TODO: Add overloads for other constructors
    };
}

TEST_CASE("Derived constructors", "[constructors.derived]") {
    {
        tl::derived<int,int> e;
        REQUIRE(e);
        REQUIRE(e == 0);
    }

    // Construct from unexpected
    {
        tl::derived<int,int> e = tl::make_unexpected(0);
        REQUIRE(!e);
        REQUIRE(e.error() == 0);
    }

    // Copy construct
    {
        tl::derived<bool, int> e;
        REQUIRE(e);
        REQUIRE(!e.value());

        tl::derived<bool, int> e_copy(e);
        REQUIRE(e_copy);
        REQUIRE(e_copy.value() == e.value());
    }

    // Move construct
    {
        tl::derived<bool, int> e;
        REQUIRE(e);
        REQUIRE(e == false);

        tl::derived<bool, int> e_move(std::move(e));
        REQUIRE(e_move);
        REQUIRE(!e_move.value());
    }
}