#include <libsnake/gamemodes/squad.h>
#include <libsnake/state.h>

#include <algorithm>
#include <assert.h>

#include <set>

using namespace ls;
using namespace ls::gm;

SquadGamemode ls::gm::Squad;

SquadGamemode::SquadGamemode() noexcept {}

bool SquadGamemode::isGameOver(const State& state) const noexcept {
	std::set<SnakeFlags> squads;
	for (const auto& snake : state.getSnakes())
		if (!snake.isDead())
			squads.insert(snake.getSquad());
	return squads.size() <= 1;
}

SnakeFlags SquadGamemode::getWinner(const State& state) const noexcept {
	std::set<SnakeFlags> squads;
	for (const auto& snake : state.getSnakes())
		if (!snake.isDead())
			squads.insert(snake.getSquad());
	if (squads.empty()) //A tie between all snakes if noone is left alive
		return SnakeFlags::FromTo(0, state.getSnakes().size());
	else if (squads.size() == 1) //Return the squad that is last one standing
		return *squads.begin();
	return SnakeFlags::None; // Two or more squads are left alive thus noone won
}

SnakeFlags SquadGamemode::getCollisionMask(const State& state, std::size_t snakeIdx) const noexcept {
	if (allowBodyCollision)
		return ~state.getSnake(snakeIdx).getSquad(); //toggle snakes belonging to my team off
	return ~SnakeFlags::None; //Collide with all snakes
}