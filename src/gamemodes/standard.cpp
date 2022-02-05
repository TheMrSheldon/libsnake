#include <libsnake/gamemodes/standard.h>
#include <libsnake/state.h>

#include <algorithm>
#include <assert.h>

#include <iostream>

using namespace ls;
using namespace ls::gm;

StandardGamemode ls::gm::Standard;

StandardGamemode::StandardGamemode() noexcept {}
StandardGamemode::~StandardGamemode() noexcept {}

bool StandardGamemode::isGameOver(const State& state) const noexcept {
	return state.getLivingSquads().size() <= 1;
}

SnakeFlags StandardGamemode::getWinner(const State& state) const noexcept {
	const auto& squads = state.getLivingSquads();
	if (squads.empty()) //A tie between all snakes if noone is left alive
		return SnakeFlags::FromTo(0, state.getNumSnakes());
	else if (squads.size() == 1) //Return the squad that is last one standing
		return *squads.begin();
	return SnakeFlags::None; // Two or more squads are left alive thus noone won
}

struct SnakeInfo {
	bool eaten, dead;
	inline constexpr SnakeInfo(SnakeInfo&& other) noexcept : eaten(other.eaten), dead(other.dead) {}
	inline constexpr SnakeInfo(bool eaten, bool dead) noexcept : eaten(eaten), dead(dead) {}
};
static Position calcHeadPos(const StandardGamemode& gm, const State& state, const Snake& snake, const Move& move) {
	const auto afterMove = snake.getHeadPos().after_move(move);
	if (gm.isBoardWrapped())
		return afterMove.mod(state.getWidth(), state.getHeight());
	return afterMove;
}
static std::vector<SnakeInfo> calcSnakeInfo(const StandardGamemode& gm, const State& state, const std::vector<Move>& moves) noexcept {
	std::vector<SnakeInfo> snakeInfos;
	for (size_t i = 0; i < state.getNumSnakes(); ++i) {
		const auto& snake = state.getSnake(i);
		const auto collisionMask = gm.getCollisionMask(state, i);
		const auto newHead = calcHeadPos(gm, state, snake, moves[i]);
		const bool eaten = state.isFoodAt(newHead);
		const bool starved = !eaten && snake.getHealth() <= 1;
		const bool collision = state.isBlocked(newHead, collisionMask, true);
		bool headToHead = false;
		for (size_t j = 0; j < state.getNumSnakes(); ++j) {
			if (i != j) {
				const auto& otherSnake = state.getSnake(j);
				const auto otherHead = calcHeadPos(gm, state, otherSnake, moves[j]);
				if ((otherHead == newHead) && (snake.length() <= otherSnake.length())) {
					headToHead = true;
					break;
				}
			}
		}
		const bool dead = starved || collision || headToHead;
		snakeInfos.emplace_back(SnakeInfo(eaten, dead));
	}
	return std::move(snakeInfos);
}

State StandardGamemode::stepState(const State& state, const std::vector<Move>& moves) const noexcept {
	//TODO: simulate hazard development
	assert(moves.size() == state.getNumSnakes());
	if (isGameOver(state))
		return state;
	std::vector<Snake> snakes;
	bool foodChanged = false;
	const auto snakeInfos = calcSnakeInfo(*this, state, moves);
	for (size_t i = 0; i < state.getNumSnakes(); ++i) {
		const auto& snake = state.getSnake(i);
		const auto& info = snakeInfos[i];
		bool eaten = info.eaten;
		bool dead = info.dead;
		if (sharedHealth || sharedLength) {//FIXME: discriminate between those two
			for (size_t j = 0; j < state.getNumSnakes(); ++j)
				if (state.getSnake(j).getSquad() == snake.getSquad())
					eaten = eaten || snakeInfos[j].eaten;
		}
		if (sharedElimination) {
			for (size_t j = 0; j < state.getNumSnakes(); ++j)
				if (state.getSnake(j).getSquad() == snake.getSquad())
					dead = dead || snakeInfos[j].dead;
		}
		const auto healthDelta = state.getFieldInfos().getHazard(snake.getHeadPos())? -16:-1;
		snakes.emplace_back(snake.afterMove(moves[i], eaten, dead, healthDelta));
		foodChanged = foodChanged || info.eaten;
	}
	if (foodChanged && !isGameOver(state)) {
		auto food = state.getFieldInfos().clone();
		for (size_t i = 0; i < state.getNumSnakes(); ++i) {
			const auto newPos = calcHeadPos(*this, state, state.getSnake(i), moves[i]);
			if (state.isInBounds(newPos))
				food.setFood(newPos, false);
		}
		return State(state.getWidth(), state.getHeight(), std::move(snakes), std::move(food));
	}
	return State(state.getWidth(), state.getHeight(), std::move(snakes), state.getFieldInfos());
}

Move StandardGamemode::getUnblockedActions(const State& state, std::size_t snakeIdx) const noexcept {
	Move ret = Move::none;
	const auto& snake = state.getSnake(snakeIdx);
	const auto collisionMask = getCollisionMask(state, snakeIdx);
	for (const auto& move : state.getPossibleActions(snakeIdx))
		if (!state.isBlocked(snake.getHeadPos().after_move(move), collisionMask, true))
			ret |= move;
	return ret;
}

SnakeFlags StandardGamemode::getCollisionMask(const State& state, std::size_t snakeIdx) const {
	return ~SnakeFlags::None; //All snakes
}