#include <catch2/catch.hpp>

#include "move.h"

TEST_CASE("General Move Caes", "[Moves]") {
    {
        auto move = MoveUp;
        REQUIRE(isUp(move));
        REQUIRE_FALSE(isLeft(move));
        REQUIRE_FALSE(isRight(move));
        REQUIRE_FALSE(isDown(move));
        REQUIRE(opposite(move) == MoveDown);
    }
    {
        auto move = MoveDown;
        REQUIRE_FALSE(isUp(move));
        REQUIRE_FALSE(isLeft(move));
        REQUIRE_FALSE(isRight(move));
        REQUIRE(isDown(move));
        REQUIRE(opposite(move) == MoveUp);
    }
    {
        auto move = MoveLeft;
        REQUIRE_FALSE(isUp(move));
        REQUIRE(isLeft(move));
        REQUIRE_FALSE(isRight(move));
        REQUIRE_FALSE(isDown(move));
        REQUIRE(opposite(move) == MoveRight);
    }
    {
        auto move = MoveRight;
        REQUIRE_FALSE(isUp(move));
        REQUIRE_FALSE(isLeft(move));
        REQUIRE(isRight(move));
        REQUIRE_FALSE(isDown(move));
        REQUIRE(opposite(move) == MoveLeft);
    }
    {
        auto move = MoveUp | MoveRight;
        REQUIRE(isUp(move));
        REQUIRE_FALSE(isLeft(move));
        REQUIRE(isRight(move));
        REQUIRE_FALSE(isDown(move));
        REQUIRE(opposite(move) == (MoveDown | MoveLeft));
    }
}