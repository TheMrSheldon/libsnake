#include <catch2/catch.hpp>

#include "move.h"

TEST_CASE("General Move Caes", "[Moves]") {
    {
        auto move = MoveUp;
        CHECK(isUp(move));
        CHECK_FALSE(isLeft(move));
        CHECK_FALSE(isRight(move));
        CHECK_FALSE(isDown(move));
        CHECK(opposite(move) == MoveDown);
        CHECK(deltaX(move) == 0);
        CHECK(deltaY(move) == 1);
    }
    {
        auto move = MoveDown;
        CHECK_FALSE(isUp(move));
        CHECK_FALSE(isLeft(move));
        CHECK_FALSE(isRight(move));
        CHECK(isDown(move));
        CHECK(opposite(move) == MoveUp);
        CHECK(deltaX(move) == 0);
        CHECK(deltaY(move) == -1);
    }
    {
        auto move = MoveLeft;
        CHECK_FALSE(isUp(move));
        CHECK(isLeft(move));
        CHECK_FALSE(isRight(move));
        CHECK_FALSE(isDown(move));
        CHECK(opposite(move) == MoveRight);
        CHECK(deltaX(move) == -1);
        CHECK(deltaY(move) == 0);
    }
    {
        auto move = MoveRight;
        CHECK_FALSE(isUp(move));
        CHECK_FALSE(isLeft(move));
        CHECK(isRight(move));
        CHECK_FALSE(isDown(move));
        CHECK(opposite(move) == MoveLeft);
        CHECK(deltaX(move) == 1);
        CHECK(deltaY(move) == 0);
    }
    {
        auto move = MoveUp | MoveRight;
        CHECK(isUp(move));
        CHECK_FALSE(isLeft(move));
        CHECK(isRight(move));
        CHECK_FALSE(isDown(move));
        CHECK(opposite(move) == (MoveDown | MoveLeft));
        CHECK(deltaX(move) == 1);
        CHECK(deltaY(move) == 1);
    }
}