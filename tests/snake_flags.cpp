#include <catch2/catch.hpp>

#include <libsnake/snake_flags.h>

TEST_CASE("General Snake Flags Case", "[Snake Flags]") {
	{
        auto flags = ls::SnakeFlags();
        CHECK(flags == ls::SnakeFlags::None);
        CHECK_FALSE(flags.containsAny(ls::SnakeFlags::Player1));
        CHECK_FALSE(flags.containsAny(ls::SnakeFlags::Player2));
        CHECK_FALSE(flags.containsAny(ls::SnakeFlags::Player3));
        CHECK_FALSE(flags.containsAny(ls::SnakeFlags::Player4));
        CHECK_FALSE(flags.containsAny(ls::SnakeFlags::Player5));
        CHECK_FALSE(flags.containsAny(ls::SnakeFlags::Player6));
        CHECK_FALSE(flags.containsAny(ls::SnakeFlags::Player7));
        CHECK_FALSE(flags.containsAny(ls::SnakeFlags::Player8));
        CHECK_FALSE(flags.containsAll(ls::SnakeFlags::Player1));
        CHECK_FALSE(flags.containsAll(ls::SnakeFlags::Player2));
        CHECK_FALSE(flags.containsAll(ls::SnakeFlags::Player3));
        CHECK_FALSE(flags.containsAll(ls::SnakeFlags::Player4));
        CHECK_FALSE(flags.containsAll(ls::SnakeFlags::Player5));
        CHECK_FALSE(flags.containsAll(ls::SnakeFlags::Player6));
        CHECK_FALSE(flags.containsAll(ls::SnakeFlags::Player7));
        CHECK_FALSE(flags.containsAll(ls::SnakeFlags::Player8));
        CHECK(flags.size() == 0);
        CHECK((flags | (ls::SnakeFlags)ls::SnakeFlags::Player3) == ls::SnakeFlags::Player3);
        CHECK((flags | (ls::SnakeFlags)ls::SnakeFlags::Player3).containsAny(ls::SnakeFlags::Player3));
        CHECK_FALSE((~(flags | (ls::SnakeFlags)ls::SnakeFlags::Player3)).containsAny(ls::SnakeFlags::Player3));
    }
    {
        auto flags = ls::SnakeFlags(ls::SnakeFlags::Player5);
        CHECK(flags == ls::SnakeFlags::Player5);
        CHECK_FALSE(flags.containsAny(ls::SnakeFlags::Player1));
        CHECK_FALSE(flags.containsAny(ls::SnakeFlags::Player2));
        CHECK_FALSE(flags.containsAny(ls::SnakeFlags::Player3));
        CHECK_FALSE(flags.containsAny(ls::SnakeFlags::Player4));
        CHECK(flags.containsAny(ls::SnakeFlags::Player5));
        CHECK_FALSE(flags.containsAny(ls::SnakeFlags::Player6));
        CHECK_FALSE(flags.containsAny(ls::SnakeFlags::Player7));
        CHECK_FALSE(flags.containsAny(ls::SnakeFlags::Player8));
        CHECK_FALSE(flags.containsAll(ls::SnakeFlags::Player1));
        CHECK_FALSE(flags.containsAll(ls::SnakeFlags::Player2));
        CHECK_FALSE(flags.containsAll(ls::SnakeFlags::Player3));
        CHECK_FALSE(flags.containsAll(ls::SnakeFlags::Player4));
        CHECK(flags.containsAll(ls::SnakeFlags::Player5));
        CHECK_FALSE(flags.containsAll(ls::SnakeFlags::Player6));
        CHECK_FALSE(flags.containsAll(ls::SnakeFlags::Player7));
        CHECK_FALSE(flags.containsAll(ls::SnakeFlags::Player8));
        
        CHECK(flags.size() == 1);
        CHECK(flags.getIndex() == 4);//Player 5 has index 4
        CHECK(flags.containsAny(ls::SnakeFlags::Player5 | ls::SnakeFlags::Player3));
        CHECK_FALSE(flags.containsAll(ls::SnakeFlags::Player5 | ls::SnakeFlags::Player3));
        CHECK((flags & (ls::SnakeFlags)ls::SnakeFlags::Player3) == (ls::SnakeFlags::None));
        CHECK((flags | (ls::SnakeFlags)ls::SnakeFlags::Player3).containsAny(ls::SnakeFlags::Player3));
        CHECK_FALSE((~(flags | (ls::SnakeFlags)ls::SnakeFlags::Player3)).containsAny(ls::SnakeFlags::Player3 | ls::SnakeFlags::Player5));
        CHECK((~(flags | (ls::SnakeFlags)ls::SnakeFlags::Player3)).containsAny(ls::SnakeFlags::Player3 | ls::SnakeFlags::Player2));
    }
    {
        auto flags = ls::SnakeFlags::FromTo(1, 4);
        CHECK_FALSE(flags.containsAny(ls::SnakeFlags::Player1));
        CHECK(flags.containsAny(ls::SnakeFlags::Player2));
        CHECK(flags.containsAny(ls::SnakeFlags::Player3));
        CHECK(flags.containsAny(ls::SnakeFlags::Player4));
        CHECK_FALSE(flags.containsAny(ls::SnakeFlags::Player5));
        CHECK_FALSE(flags.containsAny(ls::SnakeFlags::Player6));
        CHECK_FALSE(flags.containsAny(ls::SnakeFlags::Player7));
        CHECK_FALSE(flags.containsAny(ls::SnakeFlags::Player8));
        CHECK_FALSE(flags.containsAll(ls::SnakeFlags::Player1));
        CHECK(flags.containsAll(ls::SnakeFlags::Player2));
        CHECK(flags.containsAll(ls::SnakeFlags::Player3));
        CHECK(flags.containsAll(ls::SnakeFlags::Player4));
        CHECK_FALSE(flags.containsAll(ls::SnakeFlags::Player5));
        CHECK_FALSE(flags.containsAll(ls::SnakeFlags::Player6));
        CHECK_FALSE(flags.containsAll(ls::SnakeFlags::Player7));
        CHECK_FALSE(flags.containsAll(ls::SnakeFlags::Player8));
        CHECK(flags.containsAll(ls::SnakeFlags::Player2 | ls::SnakeFlags::Player3 | ls::SnakeFlags::Player4));
    }
}