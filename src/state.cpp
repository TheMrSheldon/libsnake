#include "state.h"

#include "util.h"

#include <algorithm>
#include <stdio.h>

inline static std::shared_ptr<const std::vector<Position>> CopyIfUnchanged(const std::shared_ptr<const std::vector<Position>>& food, bool gameover, bool eaten1, bool eaten2, const Position& head1, const Position& head2) {
    if ((eaten1 || eaten2) && !gameover) {
        auto copy = std::vector<Position>();
        copy.reserve(food->size()-1);
        for (const auto& pos : *food) {
            if (pos != head1 && pos != head2)
                copy.emplace_back(pos);
        }
        return std::make_shared<const std::vector<Position>>(std::move(copy));
    }
    return food;
}

inline static std::vector<Snake> FromSnakeData(const std::vector<SnakeData>& data) noexcept {
    std::vector<Snake> snakes;
    snakes.reserve(data.size());
    for (const auto& sd : data)
        snakes.emplace_back(Snake(sd));
    return snakes;
}

State::State(unsigned width, unsigned height, std::vector<SnakeData> snakes, PosArray food) noexcept
    : width(width), height(height), snakes(FromSnakeData(snakes)),
    foodPositions(std::make_shared<const std::vector<Position>>(food.data, food.data+food.length)) {}

State::State(const State& prev, Move move1, Move move2, bool eaten1, bool eaten2, bool kill1, bool kill2) noexcept
    : width(prev.width), height(prev.height),
    snakes({prev.snakes[0].afterMove(move1, eaten1, kill1), prev.snakes[1].afterMove(move2, eaten2, kill2)}),
    foodPositions(CopyIfUnchanged(prev.foodPositions, isGameOver(), eaten1, eaten2, snakes[0].getHeadPos(), snakes[1].getHeadPos())) {}

bool State::isGameOver() const noexcept { return snakes[0].getHealth() <= 0 || snakes[1].getHealth() <= 0; }

Winner State::getWinner() const noexcept {
    auto& p1Health = snakes[0].getHealth();
    auto& p2Health = snakes[1].getHealth();
    auto winflags = ((p1Health <= 0)*static_cast<unsigned char>(Winner::Player2)) |
        ((p2Health <= 0)*static_cast<unsigned char>(Winner::Player1));
    return static_cast<Winner>(winflags);
}

Move State::getPossibleActions(unsigned snake) const noexcept {
    auto& dir = snakes[snake].getDirection();
    return (~opposite(dir)) & MoveMask;
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
    const bool starve1 = !eaten1 && snake1.getHealth() <= 1;
    const bool starve2 = !eaten2 && snake2.getHealth() <= 1;
    const bool collision1 = collision && snake1.length() <= snake2.length();
    const bool collision2 = collision && snake2.length() <= snake1.length();
    const bool wall1 = !isInBounds(newHead1);
    const bool wall2 = !isInBounds(newHead2);
    const bool dead1 = starve1 || collision1 || wall1;
    const bool dead2 = starve2 || collision2 || wall2;
    return new State(*this, snake1Action, snake2Action, eaten1, eaten2, dead1, dead2);
}

bool State::isInBounds(const Position& pos) const noexcept {
    return pos.x >= 0 && pos.y >= 0 && pos.x < getWidth() && pos.y < getHeight();
}

std::size_t State::getSnakeIndexAt(const Position& pos) const noexcept {
    std::size_t index = 0;
    for (; index < snakes.size(); ++index) {
        if (utl::contains(snakes[index].getBody(), pos))
            return index;
    }
    return index;
}

bool State::isFoodAt(const Position& pos) const noexcept {
    return utl::contains(*foodPositions, pos);
}

void State::print(std::ostream& out) const noexcept {
    out << std::string(2*getWidth()+3, '#') << std::endl;
    for (unsigned y = 1; y <= getHeight(); ++y) {
        out << "# ";
        for (unsigned x = 0; x < getWidth(); ++x) {
            char c = '.';
            if (isFoodAt({x, getHeight()-y}))
                c = 'o';
            else {
                auto snake = getSnakeIndexAt({x,getHeight()-y});
                if (snake >= snakes.size())
                    c = '.';
                else
                    c = std::to_string(snake+1)[0];
            }
            out << c << ' ';
        }
        out << "#" << std::endl;
    }
    out << std::string(2*getWidth()+3, '#') << std::endl;
}