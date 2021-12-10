#include <catch2/catch.hpp>

#include "state.h"

TEST_CASE("State progression 1 (no food)", "[States]") {
    /**
     * ╔═══════╗    Snake 1:    <11
     * ║ 2 2 . ║    Snake 2:    <22
     * ║ v . . ║    Food:       o
     * ║ . < 1 ║    Empty:      .
     * ╚═══════╝
     */
    std::vector<Position> snake1 = {{1,0},{2,0}};
    std::vector<Position> snake2 = {{0,1},{0,2},{1,2}};
    std::vector<Position> food = {};
    auto sdata1 = SnakeData(snake1, MoveLeft, 100);
    auto sdata2 = SnakeData(snake2, MoveDown, 100);
    auto state1 = State(3,3, {sdata1, sdata2}, food);

    // Testcases:
    // - Assert correct initialization
    CHECK(!state1.isGameOver());
    CHECK(state1.getWinner() == Winner::None);
    CHECK(state1.getPossibleActions(0) == (MoveUp | MoveLeft | MoveDown));
    CHECK(state1.getPossibleActions(1) == (MoveDown | MoveLeft | MoveRight));
    CHECK(state1.getFood().size() == 0);
    {// - If snake1 moves left and snake2 moves up: Gameover (head to head collision)
        auto next = state1.afterAction(MoveLeft, MoveDown);
        REQUIRE(next != nullptr);
        CHECK(next->isGameOver());
        CHECK(next->getWinner() == Winner::Player2);
        // We don't care about how much food is left on the field since the game is now over
        // and the implementation may optimize this case by ignoring the amount of food left.
        delete next;
    }
    {// - If snake1 moves down and snake2 moves right: Gameover (head to head collision)
        auto next = state1.afterAction(MoveUp, MoveRight);
        REQUIRE(next != nullptr);
        CHECK(next->isGameOver());
        CHECK(next->getWinner() == Winner::Player2);
        // We don't care about how much food is left on the field since the game is now over
        // and the implementation may optimize this case by ignoring the amount of food left.
        delete next;
    }
    {// - If snake1 and snake2 move left: Gameover (snake2 ran into a wall)
        auto next = state1.afterAction(MoveLeft, MoveLeft);
        REQUIRE(next != nullptr);
        CHECK(next->isGameOver());
        CHECK(next->getWinner() == Winner::Player1);
        // We don't care about how much food is left on the field since the game is now over
        // and the implementation may optimize this case by ignoring the amount of food left.
        delete next;
    }
}

TEST_CASE("State progression 2 (food;starving)", "[States]") {
    /**
     * ╔═══════╗    Snake 1:    <11
     * ║ 2 . . ║    Snake 2:    <22
     * ║ v o < ║    Food:       o
     * ║ . . o ║    Empty:      .
     * ╚═══════╝
     */
    std::vector<Position> snake1 = {{2,1}};
    std::vector<Position> snake2 = {{0,1},{0,2}};
    std::vector<Position> food = {{2,0},{1,1}};
    auto sdata1 = SnakeData(snake1, MoveLeft, 1);
    auto sdata2 = SnakeData(snake2, MoveDown, 100);
    auto state1 = State(3,3, {sdata1, sdata2}, food);

    // Testcases:
    // - Assert correct initialization
    CHECK(!state1.isGameOver());
    CHECK(state1.getWinner() == Winner::None);
    CHECK(state1.getPossibleActions(0) == (MoveUp | MoveLeft | MoveDown));
    CHECK(state1.getPossibleActions(1) == (MoveDown | MoveLeft | MoveRight));
    CHECK(state1.getFood().size() == 2);
    {// - If snake1 moves left and snake2 moves right: Gameover (head to head collision)
        auto next = state1.afterAction(MoveLeft, MoveRight);
        REQUIRE(next != nullptr);
        CHECK(next->isGameOver());
        CHECK(next->getWinner() == Winner::Player2);
        // We don't care about how much food is left on the field since the game is now over
        // and the implementation may optimize this case by ignoring the amount of food left.
        delete next;
    }
    {// - If snake1 moves down and snake2 moves right: Gameover (snake1 starved)
        auto next = state1.afterAction(MoveUp, MoveRight);
        REQUIRE(next != nullptr);
        CHECK(next->isGameOver());
        CHECK(next->getWinner() == Winner::Player2);
        // We don't care about how much food is left on the field since the game is now over
        // and the implementation may optimize this case by ignoring the amount of food left.
        delete next;
    }
    {// - If snake1 moves up and snake2 moves right: no food remaining and both snakes at 100 HP
     // and longer by one.
        auto next = state1.afterAction(MoveDown, MoveRight);
        REQUIRE(next != nullptr);
        CHECK(!next->isGameOver());
        CHECK(next->getWinner() == Winner::None);
        CHECK(next->getFood().size() == 0);
        CHECK(next->getSnake(0).getHealth() == 100);
        CHECK(next->getSnake(1).getHealth() == 100);
        CHECK(next->getSnake(0).getBody().size() == 2);
        CHECK(next->getSnake(1).getBody().size() == 3);
        delete next;
    }
}

TEST_CASE("State progression 3 (death by wall)", "[States]") {
    /**
     * ╔═══════╗    Snake 1:    <11
     * ║ ^ . . ║    Snake 2:    <22
     * ║ 2 . 1 ║    Food:       o
     * ║ . . v ║    Empty:      .
     * ╚═══════╝
     */
    std::vector<Position> snake1 = {{2,0},{2,1}};
    std::vector<Position> snake2 = {{0,2},{0,1}};
    std::vector<Position> food = {};
    auto sdata1 = SnakeData(snake1, MoveDown, 100);
    auto sdata2 = SnakeData(snake2, MoveUp, 100);
    auto state1 = State(3,3, {sdata1, sdata2}, food);

    // Testcases:
    // - Assert correct initialization
    CHECK(!state1.isGameOver());
    CHECK(state1.getWinner() == Winner::None);
    CHECK(state1.getPossibleActions(0) == (MoveDown | MoveLeft | MoveRight));
    CHECK(state1.getPossibleActions(1) == (MoveUp | MoveLeft | MoveRight));
    CHECK(state1.getFood().size() == 0);
    {// - If snake1 moves right and snake2 moves right: Gameover (snake1 ran into a wall)
        auto next = state1.afterAction(MoveRight, MoveRight);
        REQUIRE(next != nullptr);
        CHECK(next->isGameOver());
        CHECK(next->getWinner() == Winner::Player2);
        // We don't care about how much food is left on the field since the game is now over
        // and the implementation may optimize this case by ignoring the amount of food left.
        delete next;
    }
    {// - If snake1 moves up and snake2 moves right: Gameover (snake1 ran into a wall)
        auto next = state1.afterAction(MoveDown, MoveRight);
        REQUIRE(next != nullptr);
        CHECK(next->isGameOver());
        CHECK(next->getWinner() == Winner::Player2);
        // We don't care about how much food is left on the field since the game is now over
        // and the implementation may optimize this case by ignoring the amount of food left.
        delete next;
    }
    {// - If snake1 and snake2 move left: Gameover (snake2 ran into a wall)
        auto next = state1.afterAction(MoveLeft, MoveLeft);
        REQUIRE(next != nullptr);
        CHECK(next->isGameOver());
        CHECK(next->getWinner() == Winner::Player1);
        // We don't care about how much food is left on the field since the game is now over
        // and the implementation may optimize this case by ignoring the amount of food left.
        delete next;
    }
    {// - If snake1 moves left and snake2 moves down: Gameover (snake2 ran into a wall)
        auto next = state1.afterAction(MoveLeft, MoveUp);
        REQUIRE(next != nullptr);
        CHECK(next->isGameOver());
        CHECK(next->getWinner() == Winner::Player1);
        // We don't care about how much food is left on the field since the game is now over
        // and the implementation may optimize this case by ignoring the amount of food left.
        delete next;
    }
}

TEST_CASE("State COW 1 (food)", "[States]") {
    /**
     * ╔═══════╗    Snake 1:    <11
     * ║ 2 . . ║    Snake 2:    <22
     * ║ v o < ║    Food:       o
     * ║ . . o ║    Empty:      .
     * ╚═══════╝
     */
    std::vector<Position> snake1 = {{2,1}};
    std::vector<Position> snake2 = {{0,1},{0,2}};
    std::vector<Position> food = {{2,0},{1,1}};
    auto sdata1 = SnakeData(snake1, MoveLeft, 100);
    auto sdata2 = SnakeData(snake2, MoveDown, 100);
    auto state1 = State(3,3, {sdata1, sdata2}, food);

    // Testcases:
    // - Assert correct initialization
    CHECK(!state1.isGameOver());
    CHECK(state1.getWinner() == Winner::None);
    CHECK(state1.getPossibleActions(0) == (MoveUp | MoveLeft | MoveDown));
    CHECK(state1.getPossibleActions(1) == (MoveDown | MoveLeft | MoveRight));
    CHECK(state1.getFood().size() == 2);
    {// - If snake1 moves down and snake2 moves up: cow should not create a new food-list
        auto next = state1.afterAction(MoveUp, MoveUp);
        REQUIRE(next != nullptr);
        CHECK(!next->isGameOver());
        CHECK(next->getWinner() == Winner::None);
        CHECK(&next->getFood() == &state1.getFood());
        delete next;
    }
    {// - If snake1 moves left and snake2 moves up: cow should have created a modified copy of food-list
        auto next = state1.afterAction(MoveLeft, MoveDown);
        REQUIRE(next != nullptr);
        CHECK(!next->isGameOver());
        CHECK(next->getWinner() == Winner::None);
        CHECK(next->getFood().size() == 1);
        CHECK(state1.getFood().size() == 2); //Should be unaffected
        CHECK(&next->getFood() != &state1.getFood());
        delete next;
    }
}