#include <libsnake/gamemodes/arena.h>
#include <libsnake/state.h>

#include <algorithm>
#include <assert.h>

#include <iostream>

using namespace ls;
using namespace ls::gm;

ArenaGamemode ls::gm::Arena;

ArenaGamemode::ArenaGamemode() noexcept {}

bool ArenaGamemode::isGameOver(const State& state) const noexcept {
	return std::count_if(state.getSnakes().begin(), state.getSnakes().end(), [](const Snake& snake){return !snake.isDead();}) <= 1;
}

Winner ArenaGamemode::getWinner(const State& state) const noexcept {
	Winner winner = Winner::FromTo(0, state.getSnakes().size());
	for (size_t i = 0; i < state.getSnakes().size(); ++i) {
		const auto& snake = state.getSnake(i);
		if (!snake.isDead())
			winner &= Winner::ByIndex(i);
	}
	return winner;
}

State ArenaGamemode::stepState(const State& state, const std::vector<Move>& moves) const noexcept {
	assert(moves.size() == state.getSnakes().size());
	if (isGameOver(state))
		return state;
	std::vector<Snake> snakes;
	bool foodChanged = false;
	for (size_t i = 0; i < state.getSnakes().size(); ++i) {
		const auto& snake = state.getSnake(i);
		const auto newHead = snake.getHeadPos().after_move(moves[i]);
		const bool eaten = state.isFoodAt(newHead);
		const bool starved = !eaten && snake.getHealth() <= 1;
		const bool collision = state.isBlocked(newHead);
		bool headToHead = false;
		for (size_t j = 0; j < state.getSnakes().size(); ++j) {
			if (i != j) {
				const auto& otherSnake = state.getSnake(j);
				const auto otherHead = otherSnake.getHeadPos().after_move(moves[j]);
				if ((otherHead == newHead) && (snake.length() <= otherSnake.length())) {
					headToHead = true;
					break;
				}
			}
		}
		const bool dead = starved || collision || headToHead;
		snakes.emplace_back(snake.afterMove(moves[i], eaten, dead));
		foodChanged |= eaten;
	}
	if (foodChanged && !isGameOver(state)) {
		Foods food = state.getFood().clone();
		for (size_t i = 0; i < state.getSnakes().size(); ++i)
			food.set(state.getSnake(i).getHeadPos().after_move(moves[i]), false);
		return State(state.getWidth(), state.getHeight(), std::move(snakes), std::move(food));
	}
	return State(state.getWidth(), state.getHeight(), std::move(snakes), state.getFood());
}

Move ArenaGamemode::getUnblockedActions(const State& state, std::size_t snakeIdx) const noexcept {
	//FIXME: The tip of a tail of a snake should not be considered blocked
	Move ret = Move::none;
	const auto& snake = state.getSnake(snakeIdx);
	for (const auto& move : state.getPossibleActions(snakeIdx))
		if (!state.isBlocked(snake.getHeadPos().after_move(move)))
			ret |= move;
	return ret;
}