#include <catch2/catch.hpp>

#include "state.h"

TEST_CASE("State progression 1 (no food)", "[States]") {
    /**
     * ╔═══════╗    Snake 1:    <11
     * ║ . < 1 ║    Snake 2:    <22
     * ║ ^ . . ║    Food:       o
     * ║ 2 2 . ║    Empty:      .
     * ╚═══════╝
     */
    std::vector<Position> snake1 = {{1,0},{2,0}};
    std::vector<Position> snake2 = {{0,1},{0,2},{1,2}};
    std::vector<Position> food = {};
    auto sdata1 = SnakeData({snake1.data(), (uint)snake1.size()}, MoveLeft, 100);
    auto sdata2 = SnakeData({snake2.data(), (uint)snake2.size()}, MoveUp, 100);
    auto state1 = State(3,3, sdata1, sdata2, {food.data(), (uint)food.size()});

    // Testcases:
    // - Assert correct initialization
    REQUIRE(!state1.isGameOver());
    REQUIRE(state1.getWinner() == Winner::None);
    REQUIRE(state1.getPossibleActions(0) == (MoveUp | MoveLeft | MoveDown));
    REQUIRE(state1.getPossibleActions(1) == (MoveUp | MoveLeft | MoveRight));
    {// - If snake1 moves left and snake2 moves up: Gameover (head to head collision)
        auto next = state1.afterAction(MoveLeft, MoveUp);
        REQUIRE(next != nullptr);
        REQUIRE(next->isGameOver());
        REQUIRE(next->getWinner() == Winner::Player2);
        delete next;
    }
    {// - If snake1 moves down and snake2 moves right: Gameover (head to head collision)
        auto next = state1.afterAction(MoveDown, MoveRight);
        REQUIRE(next != nullptr);
        REQUIRE(next->isGameOver());
        REQUIRE(next->getWinner() == Winner::Player2);
        delete next;
    }
    {// - If snake1 and snake2 move left: Gameover (snake2 ran into a wall)
        auto next = state1.afterAction(MoveLeft, MoveLeft);
        REQUIRE(next != nullptr);
        REQUIRE(next->isGameOver());
        REQUIRE(next->getWinner() == Winner::Player1);
        delete next;
    }
}