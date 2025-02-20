#include <catch2/catch.hpp>
#include <tl/expected.hpp>

#include <type_traits>
#include <vector>
#include <array>
#include <string>

struct takes_init_and_variadic {
    std::vector<int> v;
    std::tuple<int, int> t;
    template <class... Args>
    takes_init_and_variadic(std::initializer_list<int> l, Args &&... args)
        : v(l), t(std::forward<Args>(args)...) {}
};

struct trivial_type {
    int x;
    int y;
    trivial_type(int _x, int _y) : x{_x}, y{_y} {}
    trivial_type(std::initializer_list<int> list) {
      auto it = list.begin();
      x = *it;
      ++it;
      y = *it;
    }
};

struct takes_init_and_variadic_trivial {
    trivial_type p;
    std::tuple<int, int> t;
    template <class... Args>
    takes_init_and_variadic_trivial(std::initializer_list<int> l,
                                         Args &&...args)
      : p(l), t(std::forward<Args>(args)...) {}
};

TEST_CASE("Constructors", "[constructors]") {
    {
        tl::expected<int,int> e;
        REQUIRE(e);
        REQUIRE(e == 0);
    }

    {
        tl::expected<int,int> e = tl::make_unexpected(0);
        REQUIRE(!e);
        REQUIRE(e.error() == 0);
    }

    {
        tl::expected<int,int> e (tl::unexpect, 0);
        REQUIRE(!e);
        REQUIRE(e.error() == 0);
    }

    {
        tl::expected<int,int> e (tl::in_place, 42);
        REQUIRE(e);
        REQUIRE(e == 42);
    }

    {
        tl::expected<int, int> e(tl::in_place);
        REQUIRE(e);
        REQUIRE(e == 0);
    }

    {
        tl::expected<std::vector<int>,int> e (tl::in_place, {0,1});
        REQUIRE(e);
        REQUIRE((*e)[0] == 0);
        REQUIRE((*e)[1] == 1);
    }

    {
        tl::expected<std::tuple<int,int>,int> e (tl::in_place, 0, 1);
        REQUIRE(e);
        REQUIRE(std::get<0>(*e) == 0);
        REQUIRE(std::get<1>(*e) == 1);
    }

    {
        tl::expected<int, std::tuple<int, int>> e(tl::unexpect, 0, 1);
        REQUIRE(!e);
        REQUIRE(std::get<0>(e.error()) == 0);
        REQUIRE(std::get<1>(e.error()) == 1);
    }

    {
        tl::expected<void, std::tuple<int, int>> e(tl::unexpect, 0, 1);
        REQUIRE(!e);
        REQUIRE(std::get<0>(e.error()) == 0);
        REQUIRE(std::get<1>(e.error()) == 1);
    }
    {
        tl::expected<void, std::vector<int>> e(tl::unexpect, 2, 1);
        REQUIRE(!e);
        REQUIRE(e.error()[0] == 1);
        REQUIRE(e.error()[1] == 1);
    }
    {
        tl::expected<std::vector<int>, std::vector<int>> e(tl::unexpect, 2, 1);
        REQUIRE(!e);
        REQUIRE(e.error()[0] == 1);
        REQUIRE(e.error()[1] == 1);
    }
    {
        tl::expected<std::vector<int>, takes_init_and_variadic> e(tl::unexpect,
                                                                  {0, 1}, 2, 3);
        REQUIRE(!e);
        REQUIRE(e.error().v[0] == 0);
        REQUIRE(e.error().v[1] == 1);
        REQUIRE(std::get<0>(e.error().t) == 2);
        REQUIRE(std::get<1>(e.error().t) == 3);
    }
    {
        tl::expected<takes_init_and_variadic,int> e (tl::in_place, {0,1}, 2, 3);
        REQUIRE(e);
        REQUIRE(e->v[0] == 0);
        REQUIRE(e->v[1] == 1);
        REQUIRE(std::get<0>(e->t) == 2);
        REQUIRE(std::get<1>(e->t) == 3);
    }
    {
        tl::expected<int, takes_init_and_variadic> e(tl::unexpect, {0, 1}, 2, 3);
        REQUIRE(!e);
        REQUIRE(e.error().v[0] == 0);
        REQUIRE(e.error().v[1] == 1);
        REQUIRE(std::get<0>(e.error().t) == 2);
        REQUIRE(std::get<1>(e.error().t) == 3);
    }
    {
        tl::expected<int, takes_init_and_variadic_trivial> e(tl::unexpect, {0, 1}, 2, 3);
        REQUIRE(!e);
        REQUIRE(e.error().p.x == 0);
        REQUIRE(e.error().p.y == 1);
        REQUIRE(std::get<0>(e.error().t) == 2);
        REQUIRE(std::get<1>(e.error().t) == 3);
    }
    {
        tl::expected<void, takes_init_and_variadic_trivial> e(tl::unexpect,
                                                                   {0, 1}, 2, 3);
        REQUIRE(!e);
        REQUIRE(e.error().p.x == 0);
        REQUIRE(e.error().p.y == 1);
        REQUIRE(std::get<0>(e.error().t) == 2);
        REQUIRE(std::get<1>(e.error().t) == 3);
    }
    {
        tl::expected<int, std::vector<int>> e(tl::unexpect, 2, 1);
        REQUIRE(!e);
        REQUIRE(e.error()[0] == 1);
        REQUIRE(e.error()[1] == 1);
    }
    {
        tl::expected<std::vector<int>, trivial_type> e(tl::unexpect, 1, 2);
        REQUIRE(!e);
        REQUIRE(e.error().x == 1);
        REQUIRE(e.error().y == 2);
    }
    {
        tl::expected<std::vector<int>, takes_init_and_variadic_trivial> e(tl::unexpect, {1, 2}, 3, 4);
        REQUIRE(!e);
        REQUIRE(e.error().p.x == 1);
        REQUIRE(e.error().p.y == 2);
        REQUIRE(std::get<0>(e.error().t) == 3);
        REQUIRE(std::get<1>(e.error().t) == 4);
    }
    {
        tl::expected<void, takes_init_and_variadic> e(tl::unexpect, {0, 1}, 2, 3);
        REQUIRE(!e);
        REQUIRE(e.error().v[0] == 0);
        REQUIRE(e.error().v[1] == 1);
        REQUIRE(std::get<0>(e.error().t) == 2);
        REQUIRE(std::get<1>(e.error().t) == 3);
    }

	{
		tl::expected<int, int> e;
		REQUIRE(std::is_default_constructible<decltype(e)>::value);
		REQUIRE(std::is_copy_constructible<decltype(e)>::value);
		REQUIRE(std::is_move_constructible<decltype(e)>::value);
		REQUIRE(std::is_copy_assignable<decltype(e)>::value);
		REQUIRE(std::is_move_assignable<decltype(e)>::value);
		REQUIRE(TL_EXPECTED_IS_TRIVIALLY_COPY_CONSTRUCTIBLE(decltype(e))::value);
		REQUIRE(TL_EXPECTED_IS_TRIVIALLY_COPY_ASSIGNABLE(decltype(e))::value);
#	if !defined(TL_EXPECTED_GCC49)
		REQUIRE(std::is_trivially_move_constructible<decltype(e)>::value);
		REQUIRE(std::is_trivially_move_assignable<decltype(e)>::value);
#	endif
	}

	{
		tl::expected<int, std::string> e;
		REQUIRE(std::is_default_constructible<decltype(e)>::value);
		REQUIRE(std::is_copy_constructible<decltype(e)>::value);
		REQUIRE(std::is_move_constructible<decltype(e)>::value);
		REQUIRE(std::is_copy_assignable<decltype(e)>::value);
		REQUIRE(std::is_move_assignable<decltype(e)>::value);
		REQUIRE(!TL_EXPECTED_IS_TRIVIALLY_COPY_CONSTRUCTIBLE(decltype(e))::value);
		REQUIRE(!TL_EXPECTED_IS_TRIVIALLY_COPY_ASSIGNABLE(decltype(e))::value);
#	if !defined(TL_EXPECTED_GCC49)
		REQUIRE(!std::is_trivially_move_constructible<decltype(e)>::value);
		REQUIRE(!std::is_trivially_move_assignable<decltype(e)>::value);
#	endif
	}

	{
		tl::expected<std::string, int> e;
		REQUIRE(std::is_default_constructible<decltype(e)>::value);
		REQUIRE(std::is_copy_constructible<decltype(e)>::value);
		REQUIRE(std::is_move_constructible<decltype(e)>::value);
		REQUIRE(std::is_copy_assignable<decltype(e)>::value);
		REQUIRE(std::is_move_assignable<decltype(e)>::value);
		REQUIRE(!TL_EXPECTED_IS_TRIVIALLY_COPY_CONSTRUCTIBLE(decltype(e))::value);
		REQUIRE(!TL_EXPECTED_IS_TRIVIALLY_COPY_ASSIGNABLE(decltype(e))::value);
#	if !defined(TL_EXPECTED_GCC49)
		REQUIRE(!std::is_trivially_move_constructible<decltype(e)>::value);
		REQUIRE(!std::is_trivially_move_assignable<decltype(e)>::value);
#	endif
	}

	{
		tl::expected<std::string, std::string> e;
		REQUIRE(std::is_default_constructible<decltype(e)>::value);
		REQUIRE(std::is_copy_constructible<decltype(e)>::value);
		REQUIRE(std::is_move_constructible<decltype(e)>::value);
		REQUIRE(std::is_copy_assignable<decltype(e)>::value);
		REQUIRE(std::is_move_assignable<decltype(e)>::value);
		REQUIRE(!TL_EXPECTED_IS_TRIVIALLY_COPY_CONSTRUCTIBLE(decltype(e))::value);
		REQUIRE(!TL_EXPECTED_IS_TRIVIALLY_COPY_ASSIGNABLE(decltype(e))::value);
#	if !defined(TL_EXPECTED_GCC49)
		REQUIRE(!std::is_trivially_move_constructible<decltype(e)>::value);
		REQUIRE(!std::is_trivially_move_assignable<decltype(e)>::value);
#	endif
	}

    {
        tl::expected<void,int> e;
        REQUIRE(e);
    }

    {
        tl::expected<void,int> e (tl::unexpect, 42);
        REQUIRE(!e);
        REQUIRE(e.error() == 42);
    }

    {
        constexpr tl::unexpected<char> u('s');
        tl::expected<int, int> e(u);
        REQUIRE(e.error() == 's');
    }

    {
        struct value {
            constexpr explicit value(char v) : val(v) {}
            char val;
        };

        constexpr tl::unexpected<char> u('s');
        tl::expected<int, value> e1(u);
        REQUIRE(e1.error().val == 's');

        tl::expected<int, value> e2(tl::unexpected<char>('s'));
        REQUIRE(e2.error().val == 's');
    }
}

TEST_CASE("Unexpected constructors", "[constructors]") {
    REQUIRE(tl::unexpected<int>(1).error() == 1);
    REQUIRE(tl::unexpected<int>(tl::in_place).error() == 0);
    REQUIRE(tl::unexpected<int>(tl::in_place, 1).error() == 1);
    REQUIRE(tl::unexpected<std::vector<int>>(tl::in_place, {1, 2, 3}).error() ==
            std::vector<int>{1, 2, 3});
}
