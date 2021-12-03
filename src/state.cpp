#include "state.h"

#include <stdio.h>

State::State(unsigned width, unsigned height, SnakeData snake1, SnakeData snake2, PosArray food) noexcept
    : width(width), height(height), snakes({snake1, snake2}),
    foodPositions(std::make_shared<const std::vector<Position>>(food.data, food.data+food.length)) {}

State::State(const State& prev, Move move1, Move move2, bool eaten1, bool eaten2, bool kill1, bool kill2) noexcept
    : width(prev.width), height(prev.height),
    snakes({prev.snakes[0].afterMove(move1, eaten1, kill1), prev.snakes[1].afterMove(move2, eaten2, kill2)}) {}

bool State::isGameOver() const noexcept { return snakes[0].getHealth() <= 0 || snakes[1].getHealth() <= 0; }

Move State::getPossibleActions(unsigned snake) const noexcept {
    auto& dir = snakes[snake].getDirection();
    return ~dir;
}

State* State::afterAction(Move snake1Action, Move snake2Action) const noexcept {
    if (isGameOver())
        return nullptr;
    const auto& snake1 = snakes[0];
    const auto& snake2 = snakes[1];
    const auto newHead1 = snake1.getHeadPos().after_move(snake1Action);
    const auto newHead2 = snake2.getHeadPos().after_move(snake2Action);
    const bool eaten1 = isFoodAt(newHead1);
    const bool eaten2 = isFoodAt(newHead2);
    const bool collision = newHead1 == newHead2;
    const bool dead1 = (!eaten1 && snake1.getHealth() <= 1) || (collision && snake1.length() <= snake2.length());
    const bool dead2 = (!eaten2 && snake2.getHealth() <= 1) || (collision && snake2.length() <= snake1.length());
    return new State(*this, snake1Action, snake2Action, eaten1, eaten2, dead1, dead2);
}

bool State::isFoodAt(const Position& pos) const noexcept {
    for (const auto& food : *foodPositions)
        if (pos == food)
            return true;
    return false;
}