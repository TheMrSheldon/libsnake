#include <catch2/catch.hpp>

#include <libsnake/state.h>
#include <libsnake/gamemodes/standard.h>


#include <iostream>

using namespace ls;

TEST_CASE("State progression 1 (no food)", "[Gamemode Standard]") {
	/**
	 * ╔═══════╗	Snake 1:	<11
	 * ║ 2 2 . ║	Snake 2:	<22
	 * ║ v . . ║	Food:		o
	 * ║ . < 1 ║	Empty:		.
	 * ╚═══════╝
	 */
	const auto& gamemode = ls::gm::Standard;
	std::vector<Position> snake1 = {{1,0},{2,0}};
	std::vector<Position> snake2 = {{0,1},{0,2},{1,2}};
	std::vector<Position> food = {};
	auto sdata1 = Snake(std::move(snake1), Move::left, 100, ls::SnakeFlags::ByIndex(0));
	auto sdata2 = Snake(std::move(snake2), Move::down, 100, ls::SnakeFlags::ByIndex(1));
	auto state1 = State(3,3, {sdata1, sdata2}, std::move(food));

	// Testcases:
	// - Assert correct initialization
	CHECK(!gamemode.isGameOver(state1));
	CHECK_FALSE(state1.getSnake(0).isDead());
	CHECK_FALSE(state1.getSnake(1).isDead());
	CHECK(gamemode.getWinner(state1) == SnakeFlags::None);
	CHECK(state1.getPossibleActions(0) == (Move::up | Move::left | Move::down));
	CHECK(state1.getPossibleActions(1) == (Move::down | Move::left | Move::right));
	CHECK(state1.getFood().size() == 0);
	{// - If snake1 moves left and snake2 moves up: Gameover (head to head collision)
		auto next = gamemode.stepState(state1, {Move::left, Move::down});
		CHECK(gamemode.isGameOver(next));
		CHECK(next.getSnake(0).isDead());
		CHECK_FALSE(next.getSnake(1).isDead());
		CHECK(gamemode.getWinner(next) == SnakeFlags::Player2);
		// We don't care about how much food is left on the field since the game is now over
		// and the implementation may optimize this case by ignoring the amount of food left.
	}
	{// - If snake1 moves down and snake2 moves right: Gameover (head to head collision)
		auto next = gamemode.stepState(state1, {Move::up, Move::right});
		CHECK(gamemode.isGameOver(next));
		CHECK(gamemode.getWinner(next) == SnakeFlags::Player2);
		// We don't care about how much food is left on the field since the game is now over
		// and the implementation may optimize this case by ignoring the amount of food left.
	}
	{// - If snake1 and snake2 move left: Gameover (snake2 ran into a wall)
		auto next = gamemode.stepState(state1, {Move::left, Move::left});
		CHECK(gamemode.isGameOver(next));
		CHECK(gamemode.getWinner(next) == SnakeFlags::Player1);
		// We don't care about how much food is left on the field since the game is now over
		// and the implementation may optimize this case by ignoring the amount of food left.
	}
}

TEST_CASE("State progression 2 (food;starving)", "[Gamemode Standard]") {
	/**
	 * ╔═══════╗	Snake 1:	<11
	 * ║ 2 . . ║	Snake 2:	<22
	 * ║ v o < ║	Food:		o
	 * ║ . . o ║	Empty:		.
	 * ╚═══════╝
	 */
	const auto& gamemode = ls::gm::Standard;
	std::vector<Position> snake1 = {{2,1}};
	std::vector<Position> snake2 = {{0,1},{0,2}};
	std::vector<Position> food = {{2,0},{1,1}};
	auto sdata1 = Snake(std::move(snake1), Move::left, 1, ls::SnakeFlags::ByIndex(0));
	auto sdata2 = Snake(std::move(snake2), Move::down, 100, ls::SnakeFlags::ByIndex(1));
	auto state1 = State(3,3, {sdata1, sdata2}, std::move(food));

	// Testcases:
	// - Assert correct initialization
	CHECK(!gamemode.isGameOver(state1));
	CHECK(gamemode.getWinner(state1) == SnakeFlags::None);
	CHECK((state1.getPossibleActions(0) == (Move::up | Move::left | Move::down)));
	CHECK((state1.getPossibleActions(1) == (Move::down | Move::left | Move::right)));
	CHECK(state1.getFood().size() == 2);
	{// - If snake1 moves left and snake2 moves right: Gameover (head to head collision)
		auto next = gamemode.stepState(state1, {Move::left, Move::right});
		CHECK(gamemode.isGameOver(next));
		CHECK(gamemode.getWinner(next) == SnakeFlags::Player2);
		// We don't care about how much food is left on the field since the game is now over
		// and the implementation may optimize this case by ignoring the amount of food left.
	}
	{// - If snake1 moves down and snake2 moves right: Gameover (snake1 starved)
		auto next = gamemode.stepState(state1, {Move::up, Move::right});
		CHECK(gamemode.isGameOver(next));
		CHECK(gamemode.getWinner(next) == SnakeFlags::Player2);
		// We don't care about how much food is left on the field since the game is now over
		// and the implementation may optimize this case by ignoring the amount of food left.
	}
	{// - If snake1 moves up and snake2 moves right: no food remaining and both snakes at 100 HP
	 // and longer by one.
		auto next = gamemode.stepState(state1, {Move::down, Move::right});
		CHECK(!gamemode.isGameOver(next));
		CHECK(gamemode.getWinner(next) == SnakeFlags::None);
		CHECK(next.getFood().size() == 0);
		CHECK(next.getSnake(0).getHealth() == 100);
		CHECK(next.getSnake(1).getHealth() == 100);
		REQUIRE(next.getSnake(0).getBody().size() == 2);
		REQUIRE(next.getSnake(1).getBody().size() == 3);
		CHECK(next.getSnake(0).getBody()[0] == Position(2,0));
		CHECK(next.getSnake(0).getBody()[1] == Position(2,0));
	}
}

TEST_CASE("State progression 3 (death by wall)", "[Gamemode Standard]") {
	/**
	 * ╔═══════╗	Snake 1:	<11
	 * ║ ^ . . ║	Snake 2:	<22
	 * ║ 2 . 1 ║	Food:		o
	 * ║ . . v ║	Empty:		.
	 * ╚═══════╝
	 */
	const auto& gamemode = ls::gm::Standard;
	std::vector<Position> snake1 = {{2,0},{2,1}};
	std::vector<Position> snake2 = {{0,2},{0,1}};
	std::vector<Position> food = {};
	auto sdata1 = Snake(std::move(snake1), Move::down, 100, ls::SnakeFlags::ByIndex(0));
	auto sdata2 = Snake(std::move(snake2), Move::up, 100, ls::SnakeFlags::ByIndex(1));
	auto state1 = State(3,3, {sdata1, sdata2}, std::move(food));

	// Testcases:
	// - Assert correct initialization
	CHECK(!gamemode.isGameOver(state1));
	CHECK(gamemode.getWinner(state1) == SnakeFlags::None);
	CHECK(state1.getPossibleActions(0) == (Move::down | Move::left | Move::right));
	CHECK(state1.getPossibleActions(1) == (Move::up | Move::left | Move::right));
	CHECK(state1.getFood().size() == 0);
	{// - If snake1 moves right and snake2 moves right: Gameover (snake1 ran into a wall)
		auto next = gamemode.stepState(state1, {Move::right, Move::right});
		CHECK(gamemode.isGameOver(next));
		CHECK(gamemode.getWinner(next) == SnakeFlags::Player2);
		// We don't care about how much food is left on the field since the game is now over
		// and the implementation may optimize this case by ignoring the amount of food left.
	}
	{// - If snake1 moves up and snake2 moves right: Gameover (snake1 ran into a wall)
		auto next = gamemode.stepState(state1, {Move::down, Move::right});
		CHECK(gamemode.isGameOver(next));
		CHECK(gamemode.getWinner(next) == SnakeFlags::Player2);
		// We don't care about how much food is left on the field since the game is now over
		// and the implementation may optimize this case by ignoring the amount of food left.
	}
	{// - If snake1 and snake2 move left: Gameover (snake2 ran into a wall)
		auto next = gamemode.stepState(state1, {Move::left, Move::left});
		CHECK(gamemode.isGameOver(next));
		CHECK(gamemode.getWinner(next) == SnakeFlags::Player1);
		// We don't care about how much food is left on the field since the game is now over
		// and the implementation may optimize this case by ignoring the amount of food left.
	}
	{// - If snake1 moves left and snake2 moves down: Gameover (snake2 ran into a wall)
		auto next = gamemode.stepState(state1, {Move::left, Move::up});
		CHECK(gamemode.isGameOver(next));
		CHECK(gamemode.getWinner(next) == SnakeFlags::Player1);
		// We don't care about how much food is left on the field since the game is now over
		// and the implementation may optimize this case by ignoring the amount of food left.
	}
}

TEST_CASE("State COW 1 (food)", "[Gamemode Standard]") {
	/**
	 * ╔═══════╗	Snake 1:	<11
	 * ║ 2 . . ║	Snake 2:	<22
	 * ║ v o < ║	Food:		o
	 * ║ . . o ║	Empty:		.
	 * ╚═══════╝
	 */
	const auto& gamemode = ls::gm::Standard;
	std::vector<Position> snake1 = {{2,1}};
	std::vector<Position> snake2 = {{0,1},{0,2}};
	std::vector<Position> food = {{2,0},{1,1}};
	auto sdata1 = Snake(std::move(snake1), Move::left, 100, ls::SnakeFlags::ByIndex(0));
	auto sdata2 = Snake(std::move(snake2), Move::down, 100, ls::SnakeFlags::ByIndex(1));
	auto state1 = State(3,3, {sdata1, sdata2}, std::move(food));

	// Testcases:
	// - Assert correct initialization
	CHECK(!gamemode.isGameOver(state1));
	CHECK(gamemode.getWinner(state1) == SnakeFlags::None);
	CHECK((state1.getPossibleActions(0) == (Move::up | Move::left | Move::down)));
	CHECK((state1.getPossibleActions(1) == (Move::down | Move::left | Move::right)));
	CHECK(state1.getFood().size() == 2);
	{// - If snake1 moves up and snake2 moves down: cow should not create a new food-list
		auto next = gamemode.stepState(state1, {Move::up, Move::down});
		CHECK(!gamemode.isGameOver(next));
		CHECK(gamemode.getWinner(next) == SnakeFlags::None);
		CHECK(next.getFood().__raw() == state1.getFood().__raw());
	}
	{// - If snake1 moves left and snake2 moves up: cow should have created a modified copy of food-list
		auto next = gamemode.stepState(state1, {Move::left, Move::down});
		CHECK(!gamemode.isGameOver(next));
		CHECK(gamemode.getWinner(next) == SnakeFlags::None);
		CHECK(next.getFood().size() == 1);
		CHECK(state1.getFood().size() == 2); //Should be unaffected
		CHECK(next.getFood().__raw() != state1.getFood().__raw());
	}
}