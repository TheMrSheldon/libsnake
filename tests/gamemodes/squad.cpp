#include <catch2/catch.hpp>

#include <libsnake/state.h>
#include <libsnake/gamemodes/squad.h>

#include <iostream>

using namespace ls;

TEST_CASE("Squad - State progression 1 (no food)", "[Gamemode Squad]") {
    /**
     * ╔═══════════╗	Snake 1:	<11
     * ║ . 2 2 2 . ║	Snake 2:	<22
     * ║ . 2 < 2 . ║	Snake 3:	<33
     * ║ 1 > . < 3 ║	Food:		o
     * ╚═══════════╝    Empty:      .
     * Snake 1 and 2 are in the same squad.
     */

    auto& gamemode = ls::gm::Squad;
    gamemode.setAllowBodyCollisions(true);
	std::vector<Position> snake1 = {{1,0},{0,0}};
	std::vector<Position> snake2 = {{2,1},{3,1},{3,2},{2,2},{1,2},{1,1}};
	std::vector<Position> snake3 = {{3,0},{4,0}};
	std::vector<Position> food = {};
    auto sdata1 = Snake(std::move(snake1), 100, ls::SnakeFlags::Player1 | ls::SnakeFlags::Player2);
	auto sdata2 = Snake(std::move(snake2), 100, ls::SnakeFlags::Player1 | ls::SnakeFlags::Player2);
	auto sdata3 = Snake(std::move(snake3), 100, ls::SnakeFlags::Player3);
	auto state1 = State(5,3, {sdata1, sdata2, sdata3}, std::move(food));

	// Testcases:
	// - Assert correct initialization
    CHECK(!gamemode.isGameOver(state1));
	CHECK_FALSE(state1.getSnake(0).isDead());
	CHECK_FALSE(state1.getSnake(1).isDead());
	CHECK_FALSE(state1.getSnake(2).isDead());
	CHECK(gamemode.getWinner(state1) == SnakeFlags::None);
	CHECK((state1.getPossibleActions(0) == (Move::right | Move::up | Move::down)));
	CHECK((state1.getPossibleActions(1) == (Move::down | Move::up | Move::left)));
	CHECK((state1.getPossibleActions(2) == (Move::down | Move::left | Move::up)));
	CHECK(state1.getFood().size() == 0);
    {//If snake1 and snake3 move up and snake2 moves down: only snake3 should be dead and snake1 and snake2 won
        auto next = gamemode.stepState(state1, {Move::up, Move::down, Move::up});
		CHECK(gamemode.isGameOver(next));
		CHECK_FALSE(next.getSnake(0).isDead());
		CHECK_FALSE(next.getSnake(1).isDead());
		CHECK(next.getSnake(2).isDead());
		CHECK(gamemode.getWinner(next) == SnakeFlags(SnakeFlags::Player1|SnakeFlags::Player2));
    }
}