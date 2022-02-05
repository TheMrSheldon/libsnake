#include <libsnake/gamemodes/challenge.h>
#include <libsnake/state.h>

#include <algorithm>
#include <assert.h>

using namespace ls;
using namespace ls::gm;

ChallengeGamemode ls::gm::Challenge;

ChallengeGamemode::ChallengeGamemode() noexcept {}
ChallengeGamemode::~ChallengeGamemode() noexcept {}

bool ChallengeGamemode::isGameOver(const State& state) const noexcept {
    //The challenge gamemodes should be played solo. As such the game is over if "any" snake is dead.
    //If there is only one snake this is equivalent to this snake being dead. The implementation with any
    //was only chosen to be safe in cases where there are more or less snakes.
	return std::any_of(state.getSnakes().begin(), state.getSnakes().end(), [](const Snake& snake){return snake.isDead();});
}

SnakeFlags ChallengeGamemode::getWinner(const State& state) const noexcept {
    //The challenge gamemode may not really be won.
    return SnakeFlags::None;
}