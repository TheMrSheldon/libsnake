#include "gamemodes/duel.h"

#include "state.h"

#include <algorithm>

using namespace ls;
using namespace ls::gm;

DuelGamemode ls::gm::Duel;

bool DuelGamemode::isGameOver(const State& state) const noexcept {
    return std::count_if(state.getSnakes().begin(), state.getSnakes().end(), [](const Snake& snake){return !snake.isDead();}) <= 1;
}

State DuelGamemode::stepState(const State& state, const std::array<Move, 2>& moves) const noexcept {
    if (isGameOver(state))
        return state;
    const auto& snake1 = state.getSnake(0);
    const auto& snake2 = state.getSnake(1);
    const auto newHead1 = snake1.getHeadPos().after_move(moves[0]);
    const auto newHead2 = snake2.getHeadPos().after_move(moves[1]);
    const bool eaten1 = state.isFoodAt(newHead1);
    const bool eaten2 = state.isFoodAt(newHead2);
    const bool collision = newHead1 == newHead2;
    const bool starve1 = !eaten1 && snake1.getHealth() <= 1;
    const bool starve2 = !eaten2 && snake2.getHealth() <= 1;
    const bool collision1 = collision && snake1.length() <= snake2.length();
    const bool collision2 = collision && snake2.length() <= snake1.length();
    const bool wall1 = !state.isInBounds(newHead1);
    const bool wall2 = !state.isInBounds(newHead2);
    const bool dead1 = starve1 || collision1 || wall1;
    const bool dead2 = starve2 || collision2 || wall2;
    return State(state, moves[0], moves[1], eaten1, eaten2, dead1, dead2);
}

Winner DuelGamemode::getWinner(const State& state) const noexcept {
    auto& p1Health = state.getSnake(0).getHealth();
    auto& p2Health = state.getSnake(1).getHealth();
    auto winflags = ((p1Health <= 0)*Winner::Player2) | ((p2Health <= 0)*Winner::Player1);
    return Winner(winflags);
}