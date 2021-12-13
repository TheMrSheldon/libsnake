#include <catch2/catch.hpp>

#include <libsnake/move.h>

TEST_CASE("General Move Case", "[Moves]") {
    {
        ls::Move move = ls::Move::up;
        CHECK(move.isUp());
        CHECK_FALSE(move.isLeft());
        CHECK_FALSE(move.isRight());
        CHECK_FALSE(move.isDown());
        CHECK(move.opposite() == ls::Move::down);
        CHECK(move.deltaX() == 0);
        CHECK(move.deltaY() == 1);
    }
    {
        ls::Move move = ls::Move::down;
        CHECK_FALSE(move.isUp());
        CHECK_FALSE(move.isLeft());
        CHECK_FALSE(move.isRight());
        CHECK(move.isDown());
        CHECK(move.opposite() == ls::Move::up);
        CHECK(move.deltaX() == 0);
        CHECK(move.deltaY() == -1);
    }
    {
        ls::Move move = ls::Move::left;
        CHECK_FALSE(move.isUp());
        CHECK(move.isLeft());
        CHECK_FALSE(move.isRight());
        CHECK_FALSE(move.isDown());
        CHECK(move.opposite() == ls::Move::right);
        CHECK(move.deltaX() == -1);
        CHECK(move.deltaY() == 0);
    }
    {
        ls::Move move = ls::Move::right;
        CHECK_FALSE(move.isUp());
        CHECK_FALSE(move.isLeft());
        CHECK(move.isRight());
        CHECK_FALSE(move.isDown());
        CHECK(move.opposite() == ls::Move::left);
        CHECK(move.deltaX() == 1);
        CHECK(move.deltaY() == 0);
    }
    {
        ls::Move move = ls::Move::up | ls::Move::right;
        CHECK(move.isUp());
        CHECK_FALSE(move.isLeft());
        CHECK(move.isRight());
        CHECK_FALSE(move.isDown());
        CHECK(move.opposite() == (ls::Move::down | ls::Move::left));
        CHECK(move.deltaX() == 1);
        CHECK(move.deltaY() == 1);
    }
}

TEST_CASE("Iterating moves", "[Moves]") {
    {
        ls::Move moves = ls::Move::up | ls::Move::down;
        std::vector<ls::Move> iterated;
        for (const auto& move : moves)
            iterated.push_back(move);
        REQUIRE(iterated.size() == 2);
        CHECK(iterated[0] == ls::Move::up);
        CHECK(iterated[1] == ls::Move::down);
    }
}