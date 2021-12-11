#include <libsnake/state.h>

#include <libsnake/util.h>
#include <libsnake/gamemodes/duel.h>

#include <algorithm>
#include <stdio.h>

using namespace ls;

inline static std::shared_ptr<const std::vector<Position>> CopyIfUnchanged(const std::shared_ptr<const std::vector<Position>>& food, bool gameover, bool eaten1, bool eaten2, const Snake& snake1, const Snake& snake2) {
    if ((eaten1 || eaten2) && !gameover) {
        const auto& head1 = snake1.getHeadPos();
        const auto& head2 = snake2.getHeadPos();
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
	
State::State(unsigned width, unsigned height, std::vector<Snake>& snakes, std::vector<Position>& food) noexcept
    : width(width), height(height), snakes(std::move(snakes)),
    foodPositions(std::make_shared<const std::vector<Position>>(std::move(food))) {}

State::State(const State& prev, Move move1, Move move2, bool eaten1, bool eaten2, bool kill1, bool kill2) noexcept
    : width(prev.width), height(prev.height),
    snakes({prev.snakes[0].afterMove(move1, eaten1, kill1), prev.snakes[1].afterMove(move2, eaten2, kill2)}),
    foodPositions(CopyIfUnchanged(prev.foodPositions, ls::gm::Duel.isGameOver(*this), eaten1, eaten2, getSnake(0), getSnake(1))) {}

Move State::getPossibleActions(unsigned snake) const noexcept {
    auto& dir = snakes[snake].getDirection();
    return (~opposite(dir)) & MoveMask;
}

bool State::isInBounds(const Position& pos) const noexcept {
    return pos.x >= 0 && pos.y >= 0 && pos.x < getWidth() && pos.y < getHeight();
}

bool State::isBlocked(const Position& pos) const noexcept {
    return !isInBounds(pos) || getSnakeIndexAt(pos) < snakes.size();
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