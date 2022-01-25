#include <catch2/catch.hpp>

#include <libsnake/state.h>
#include <libsnake/gamemodes/squad.h>

#include <iostream>

using namespace ls;

TEST_CASE("Squad (coll) - State progression 1 (no food)", "[Gamemode Squad -- coll]") {
    /**
     * ╔═══════════╗	Snake 1:	<11
     * ║ . 2 2 2 . ║	Snake 2:	<22
     * ║ 2 2 < 2 . ║	Snake 3:	<33
     * ║ 1 > . < 3 ║	Food:		o
     * ╚═══════════╝    Empty:      .
     * Snake 1 and 2 are in the same squad.
     */

    auto& gamemode = ls::gm::Squad;
    gamemode.setAllowBodyCollisions(true);
    gamemode.setSharedElimination(false);
    gamemode.setSharedHealth(false);
    gamemode.setSharedLength(false);
	std::vector<Position> snake1 = {{1,0},{0,0}};
	std::vector<Position> snake2 = {{2,1},{3,1},{3,2},{2,2},{1,2},{1,1},{0,1}};
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
    CHECK((gamemode.getUnblockedActions(state1, 0) == (Move::right | Move::up)));
    CHECK((gamemode.getUnblockedActions(state1, 1) == (Move::down)));
    CHECK((gamemode.getUnblockedActions(state1, 2) == Move::left));
    {//If snake1 and snake3 move up and snake2 moves down: only snake3 should be dead and snake1 and snake2 won
        auto next = gamemode.stepState(state1, {Move::up, Move::down, Move::up});
		CHECK(gamemode.isGameOver(next));
		CHECK_FALSE(next.getSnake(0).isDead());
		CHECK_FALSE(next.getSnake(1).isDead());
		CHECK(next.getSnake(2).isDead());
		CHECK(gamemode.getWinner(next) == SnakeFlags(SnakeFlags::Player1|SnakeFlags::Player2));
    }
    {//If snake1 moves right, snake2 moves down, snake3 moves left: snake1 and 2 win (snake1 and 3 died due to 2)
        auto next = gamemode.stepState(state1, {Move::right, Move::down, Move::left});
		CHECK(gamemode.isGameOver(next));
		CHECK(next.getSnake(0).isDead());
		CHECK_FALSE(next.getSnake(1).isDead());
		CHECK(next.getSnake(2).isDead());
		CHECK(gamemode.getWinner(next) == SnakeFlags(SnakeFlags::Player1|SnakeFlags::Player2));
    }
    {//If snake1 moves down, snake2 moves down, snake3 moves left: tie (snake1 ran into a wall and 3 died due to 2)
        auto next = gamemode.stepState(state1, {Move::down, Move::down, Move::left});
		CHECK(gamemode.isGameOver(next));
		CHECK(next.getSnake(0).isDead());
		CHECK_FALSE(next.getSnake(1).isDead());
		CHECK(next.getSnake(2).isDead());
		CHECK(gamemode.getWinner(next) == SnakeFlags(SnakeFlags::Player1|SnakeFlags::Player2));
    }
    {//If snake1 moves up, snake2 moves up, snake3 moves left: only snake 2 should be dead and game not over
        auto next = gamemode.stepState(state1, {Move::up, Move::up, Move::left});
		CHECK_FALSE(gamemode.isGameOver(next));
		CHECK_FALSE(next.getSnake(0).isDead());
		CHECK(next.getSnake(1).isDead());
		CHECK_FALSE(next.getSnake(2).isDead());
    }
}

TEST_CASE("Squad (coll;elim;health;length) - State progression 1 (no food)", "[Gamemode Squad -- coll;elim;health;length]") {
    /**
     * ╔═══════════╗	Snake 1:	<11
     * ║ . 2 2 2 . ║	Snake 2:	<22
     * ║ 2 2 < 2 . ║	Snake 3:	<33
     * ║ 1 > . < 3 ║	Food:		o
     * ╚═══════════╝    Empty:      .
     * Snake 1 and 2 are in the same squad.
     */

    auto& gamemode = ls::gm::Squad;
    gamemode.setAllowBodyCollisions(true);
    gamemode.setSharedElimination(true);
    gamemode.setSharedHealth(true);
    gamemode.setSharedLength(true);
	std::vector<Position> snake1 = {{1,0},{0,0}};
	std::vector<Position> snake2 = {{2,1},{3,1},{3,2},{2,2},{1,2},{1,1},{0,1}};
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
    CHECK((gamemode.getUnblockedActions(state1, 0) == (Move::right | Move::up)));
    CHECK((gamemode.getUnblockedActions(state1, 1) == (Move::down)));
    CHECK((gamemode.getUnblockedActions(state1, 2) == Move::left));
    {//If snake1 and snake3 move up and snake2 moves down: only snake3 should be dead and snake1 and snake2 won
        auto next = gamemode.stepState(state1, {Move::up, Move::down, Move::up});
		CHECK(gamemode.isGameOver(next));
		CHECK_FALSE(next.getSnake(0).isDead());
		CHECK_FALSE(next.getSnake(1).isDead());
		CHECK(next.getSnake(2).isDead());
		CHECK(gamemode.getWinner(next) == SnakeFlags(SnakeFlags::Player1|SnakeFlags::Player2));
    }
    {//If snake1 moves right, snake2 moves down, snake3 moves left: tie (snake1 and 3 died due to 2; 2 dies because 1 died)
        auto next = gamemode.stepState(state1, {Move::right, Move::down, Move::left});
		CHECK(gamemode.isGameOver(next));
		CHECK(next.getSnake(0).isDead());
		CHECK(next.getSnake(1).isDead());
		CHECK(next.getSnake(2).isDead());
		CHECK(gamemode.getWinner(next) == SnakeFlags(SnakeFlags::Player1|SnakeFlags::Player2|SnakeFlags::Player3));
    }
    {//If snake1 moves down, snake2 moves down, snake3 moves left: tie (snake1 ran into a wall and 3 died due to 2; 2 dies because 1 died)
        auto next = gamemode.stepState(state1, {Move::down, Move::down, Move::left});
		CHECK(gamemode.isGameOver(next));
		CHECK(next.getSnake(0).isDead());
		CHECK(next.getSnake(1).isDead());
		CHECK(next.getSnake(2).isDead());
		CHECK(gamemode.getWinner(next) == SnakeFlags(SnakeFlags::Player1|SnakeFlags::Player2|SnakeFlags::Player3));
    }
}

TEST_CASE("Shared Length", "[Gamemode Squad -- length]") {
	/**
     * ╔═══════════╗	Snake 1:	<11
     * ║ 1 > o . . ║	Snake 2:	<22
     * ║ 2 > . . . ║	Snake 3:	<33
     * ║ 3 > . . . ║	Food:		o
     * ╚═══════════╝    Empty:      .
     * Snake 1 and 2 are in the same squad.
     */
	auto gamemode = ls::gm::SquadGamemode();
    gamemode.setAllowBodyCollisions(true);
    gamemode.setSharedElimination(true);
    gamemode.setSharedHealth(true);
    gamemode.setSharedLength(true);
	std::vector<Position> snake1 = {{1,2},{0,2}};
	std::vector<Position> snake2 = {{1,1},{0,1}};
	std::vector<Position> snake3 = {{1,0},{0,0}};
	std::vector<Position> food = {{2,2}};
    auto sdata1 = Snake(std::move(snake1), 100, ls::SnakeFlags::Player1 | ls::SnakeFlags::Player2);
	auto sdata2 = Snake(std::move(snake2), 100, ls::SnakeFlags::Player1 | ls::SnakeFlags::Player2);
	auto sdata3 = Snake(std::move(snake3), 100, ls::SnakeFlags::Player3);
	auto state1 = State(5,3, {sdata1, sdata2, sdata3}, std::move(food));

	{//If all snakes move right, snake 1 and 2 should have grown
		auto next = gamemode.stepState(state1, {Move::right, Move::right, Move::right});
		REQUIRE(next.getSnake(0).length() == 3);
		REQUIRE(next.getSnake(1).length() == 3);
		REQUIRE(next.getSnake(2).length() == 2);
		CHECK(next.getSnake(0).getBody()[0] == Position(2,2));
		CHECK(next.getSnake(0).getBody()[1] == Position(1,2));
		CHECK(next.getSnake(0).getBody()[2] == Position(1,2));
		CHECK(next.getSnake(1).getBody()[0] == Position(2,1));
		CHECK(next.getSnake(1).getBody()[1] == Position(1,1));
		CHECK(next.getSnake(1).getBody()[2] == Position(1,1));
	}
}