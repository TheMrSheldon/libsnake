#include <catch2/catch.hpp>

#include "state.h"

TEST_CASE("State progression", "[States]") {
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
    assert(!state1.isGameOver());
    // - If snake1 moves left and snake2 moves up: Gameover
    {
        auto next = state1.afterAction(MoveLeft, MoveUp);
        assert(next != nullptr);
        assert(next->isGameOver());
        delete next;
    }
    // - If snake1 moves down and snake2 moves right: Gameover
    {
        auto next = state1.afterAction(MoveDown, MoveRight);
        assert(next != nullptr);
        assert(next->isGameOver());
        delete next;
    }
}