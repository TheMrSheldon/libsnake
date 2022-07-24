#include <catch2/catch.hpp>

#include <libsnake/gamemodes/standard.h>
#include <libsnake/maps/empty.h>
#include <libsnake/state.h>

using namespace ls;

static ls::map::Empty emptyMap;

TEST_CASE("Standard Gamemode Benchmark") {
	/**
	 * ╔═══════════════════════════════╗	Snake 1:	<11
	 * ║ . . . . . . . . . . . . . . . ║	Snake 2:	<22
	 * ║ . . o . . . . . o . . o . . . ║	Food:		o
	 * ║ . . . . . . . . . . . . . . . ║	Empty:		.
	 * ║ . . . . . o . . o < 2 2 . 2 2 ║
	 * ║ . . . . . . o . . . . 2 . 2 2 ║
	 * ║ . . o . . . ^ . . . . 2 2 2 2 ║
	 * ║ . . . . . . 1 . . . . . . . 2 ║
	 * ║ . . . . . . 1 . 1 1 1 1 1 1 2 ║
	 * ║ . . o . o . 1 1 1 . . . . 1 2 ║
	 * ║ . . . . . . . . . . . . 1 1 2 ║
	 * ╚═══════════════════════════════╝
	 */

	const auto gamemode = ls::gm::StandardGamemode(emptyMap);
	std::vector<Position> snake1 = {{6, 4},	 {6, 3},	{6, 2},	 {6, 1},	{7, 1},	 {8, 1},	{8, 2}, {9, 2},
																	{10, 2}, {11, 2}, {12, 2}, {13, 2}, {13, 1}, {13, 0}, {12, 0}};
	std::vector<Position> snake2 = {{9, 6},	 {10, 6}, {11, 6}, {11, 5}, {11, 4}, {12, 4}, {13, 4}, {13, 5},
																	{13, 6}, {14, 6}, {14, 5}, {14, 4}, {14, 3}, {14, 2}, {14, 1}, {14, 0}};
	std::vector<Position> food = {{2, 1}, {4, 1}, {2, 4}, {6, 5}, {5, 6}, {8, 6}, {2, 8}, {8, 8}, {11, 8}};
	auto sdata1 = Snake(std::move(snake1), Move::up, 100, ls::SnakeFlags::ByIndex(0));
	auto sdata2 = Snake(std::move(snake2), Move::left, 100, ls::SnakeFlags::ByIndex(1));
	auto state = State(15, 10, {sdata1, sdata2}, std::move(food), {});

	BENCHMARK("Progression"){
		auto state1 = std::move(gamemode.stepState(state, {Move::up, Move::left}));
		auto state2 = std::move(gamemode.stepState(state1, {Move::left, Move::left}));
		auto state3 = std::move(gamemode.stepState(state2, {Move::up, Move::left}));
		return state3;
	};
}