#include <catch2/catch.hpp>

#include <libsnake/state.h>
#include <libsnake/gamemodes/standard.h>
#include <libsnake/maps/empty.h>

using namespace ls;

static ls::map::Empty emptyMap;

TEST_CASE("State Progression", "[Gamemode Wrapped]") {
	/**
	 * ╔═══════╗	Snake 1:	<11
	 * ║ 2 2 . ║	Snake 2:	<22
	 * ║ v . . ║	Food:		o
	 * ║ . < 1 ║	Empty:		.
	 * ╚═══════╝
	 */
	auto gamemode = ls::gm::StandardGamemode(emptyMap);
	gamemode.setWrappedBoard(true);
	std::vector<Position> snake1 = {{1,0},{2,0}};
	std::vector<Position> snake2 = {{0,1},{0,2},{1,2}};
	auto sdata1 = Snake(std::move(snake1), Move::left, 100, ls::SnakeFlags::Player1);
	auto sdata2 = Snake(std::move(snake2), Move::down, 100, ls::SnakeFlags::Player2);
	auto state1 = State(3,3, {sdata1, sdata2}, {}, {});
	
	// Testcases:
	// - Assert correct initialization
	CHECK(!gamemode.isGameOver(state1));
	CHECK_FALSE(state1.getSnake(0).isDead());
	CHECK_FALSE(state1.getSnake(1).isDead());
	CHECK(gamemode.getWinner(state1) == SnakeFlags::None);
	CHECK(state1.getPossibleActions(0) == (Move::up | Move::left | Move::down));
	CHECK(state1.getPossibleActions(1) == (Move::down | Move::left | Move::right));
	CHECK(gamemode.getUnblockedActions(state1, 0) == (Move::up | Move::left | Move::down));
	CHECK(gamemode.getUnblockedActions(state1, 1) == (Move::left | Move::right | Move::down));

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
	{// - If snake1 and snake2 move left: Game is still on (snake 1 and 2 wrap around)
		auto next = gamemode.stepState(state1, {Move::down, Move::left});
		CHECK_FALSE(gamemode.isGameOver(next));
		CHECK(gamemode.getWinner(next) == SnakeFlags::None);
		CHECK(next.getSnake(0).getHeadPos() == Position(1,2));
		CHECK(next.getSnake(1).getHeadPos() == Position(2,1));
		//CHECK(next.getFieldInfos().__raw() == state1.getFieldInfos().__raw());
	}
}