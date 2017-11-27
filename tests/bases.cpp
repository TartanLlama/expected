#include "catch.hpp"
#include "expected.hpp"

TEST_CASE("Triviality", "[bases.triviality]") {
    REQUIRE(std::is_trivially_copy_constructible<tl::expected<int,int>>::value);
    REQUIRE(std::is_trivially_copy_assignable<tl::expected<int,int>>::value);
    REQUIRE(std::is_trivially_move_constructible<tl::expected<int,int>>::value);
    REQUIRE(std::is_trivially_move_assignable<tl::expected<int,int>>::value);
    REQUIRE(std::is_trivially_destructible<tl::expected<int,int>>::value);

    {
        struct T {
            T(const T&) = default;
            T(T&&) = default;
            T& operator=(const T&) = default;
            T& operator=(T&&) = default;
            ~T() = default;
        };
        REQUIRE(std::is_trivially_copy_constructible<tl::expected<T,int>>::value);
        REQUIRE(std::is_trivially_copy_assignable<tl::expected<T,int>>::value);
        REQUIRE(std::is_trivially_move_constructible<tl::expected<T,int>>::value);
        REQUIRE(std::is_trivially_move_assignable<tl::expected<T,int>>::value);
        REQUIRE(std::is_trivially_destructible<tl::expected<T,int>>::value);
    }

    {
        struct T {
            T(const T&){}
            T(T&&) {};
            T& operator=(const T&) {}
            T& operator=(T&&) {};
            ~T(){}
        };
        REQUIRE(!std::is_trivially_copy_constructible<tl::expected<T,int>>::value);
        REQUIRE(!std::is_trivially_copy_assignable<tl::expected<T,int>>::value);
        REQUIRE(!std::is_trivially_move_constructible<tl::expected<T,int>>::value);
        REQUIRE(!std::is_trivially_move_assignable<tl::expected<T,int>>::value);
        REQUIRE(!std::is_trivially_destructible<tl::expected<T,int>>::value);
    }

}

TEST_CASE("Deletion", "[bases.deletion]") {
    REQUIRE(std::is_copy_constructible<tl::expected<int,int>>::value);
    REQUIRE(std::is_copy_assignable<tl::expected<int,int>>::value);
    REQUIRE(std::is_move_constructible<tl::expected<int,int>>::value);
    REQUIRE(std::is_move_assignable<tl::expected<int,int>>::value);
    REQUIRE(std::is_destructible<tl::expected<int,int>>::value);

    {
        struct T {
            T()=default;
        };
        REQUIRE(std::is_default_constructible<tl::expected<T,int>>::value);
    }

    {
        struct T {
            T(int);
        };
        REQUIRE(!std::is_default_constructible<tl::expected<T,int>>::value);
    }

    {
        struct T {
            T(const T&) = default;
            T(T&&) = default;
            T& operator=(const T&) = default;
            T& operator=(T&&) = default;
            ~T() = default;
        };
        REQUIRE(std::is_copy_constructible<tl::expected<T,int>>::value);
        REQUIRE(std::is_copy_assignable<tl::expected<T,int>>::value);
        REQUIRE(std::is_move_constructible<tl::expected<T,int>>::value);
        REQUIRE(std::is_move_assignable<tl::expected<T,int>>::value);
        REQUIRE(std::is_destructible<tl::expected<T,int>>::value);
    }

    {
        struct T {
            T(const T&)=delete;
            T(T&&)=delete;
            T& operator=(const T&)=delete;
            T& operator=(T&&)=delete;
        };
        REQUIRE(!std::is_copy_constructible<tl::expected<T,int>>::value);
        REQUIRE(!std::is_copy_assignable<tl::expected<T,int>>::value);
        REQUIRE(!std::is_move_constructible<tl::expected<T,int>>::value);
        REQUIRE(!std::is_move_assignable<tl::expected<T,int>>::value);
    }

    {
        struct T {
            T(const T&)=delete;
            T(T&&)=default;
            T& operator=(const T&)=delete;
            T& operator=(T&&)=default;
        };
        REQUIRE(!std::is_copy_constructible<tl::expected<T,int>>::value);
        REQUIRE(!std::is_copy_assignable<tl::expected<T,int>>::value);
        REQUIRE(std::is_move_constructible<tl::expected<T,int>>::value);
        REQUIRE(std::is_move_assignable<tl::expected<T,int>>::value);
    }

    {
        struct T {
            T(const T&)=default;
            T(T&&)=delete;
            T& operator=(const T&)=default;
            T& operator=(T&&)=delete;
        };
        REQUIRE(std::is_copy_constructible<tl::expected<T,int>>::value);
        REQUIRE(std::is_copy_assignable<tl::expected<T,int>>::value);
        //TODO see why this fails
        //REQUIRE(!std::is_move_constructible<tl::expected<T,int>>::value);
        //REQUIRE(!std::is_move_assignable<tl::expected<T,int>>::value);
    }


}
