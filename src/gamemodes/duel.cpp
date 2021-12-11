#include <libsnake/gamemodes/duel.h>

#include <libsnake/state.h>

#include <algorithm>

using namespace ls;
using namespace ls::gm;

DuelGamemode ls::gm::Duel;

DuelGamemode::DuelGamemode() noexcept {}

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
    const bool headtohead = newHead1 == newHead2;
    const bool starve1 = !eaten1 && snake1.getHealth() <= 1;
    const bool starve2 = !eaten2 && snake2.getHealth() <= 1;
    const bool headtohead1 = headtohead && snake1.length() <= snake2.length();
    const bool headtohead2 = headtohead && snake2.length() <= snake1.length();
    const bool wall1 = state.isBlocked(newHead1);
    const bool wall2 = state.isBlocked(newHead2);
    const bool dead1 = starve1 || headtohead1 || wall1;
    const bool dead2 = starve2 || headtohead2 || wall2;
    return State(state, moves[0], moves[1], eaten1, eaten2, dead1, dead2);
}

Winner DuelGamemode::getWinner(const State& state) const noexcept {
    auto winflags = (state.getSnake(0).isDead()*Winner::Player2) | (state.getSnake(1).isDead()*Winner::Player1);
    return Winner(winflags);
}