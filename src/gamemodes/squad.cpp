#include <libsnake/gamemodes/squad.h>
#include <libsnake/state.h>

#include <algorithm>
#include <assert.h>

#include <set>

using namespace ls;
using namespace ls::gm;

SquadGamemode::SquadGamemode(const ls::map::Map &map) noexcept : StandardGamemode(map) {}
SquadGamemode::~SquadGamemode() noexcept {}

SnakeFlags SquadGamemode::getCollisionMask(const State &state, std::size_t snakeIdx) const noexcept {
	if (getAllowBodyCollisions())
		return ~state.getSnake(snakeIdx).getSquad() |
					 SnakeFlags::ByIndex(snakeIdx); // toggle snakes belonging to my team off (but I still collide with myself)
	return ~SnakeFlags::None;								// Collide with all snakes
}