#include <libsnake/state.h>

#include <libsnake/util.h>

#include <libsnake/definitions.h>

#include <algorithm>
#include <stdio.h>

using namespace ls;

Foods::Foods(unsigned width, unsigned height) noexcept : width(width), height(height),
	positions(std::make_shared<std::vector<uint8_t>>(width*height, false)) {}
Foods::Foods(unsigned width, unsigned height, std::vector<Position> pos) noexcept : Foods(width, height) {
	for (const auto& p : pos)
		set(p.x, p.y, true);
}
void Foods::set(const Position& p, bool value) noexcept {
	ASSERT(p.x < width, "The accessed x-coordinate may not exceed the width of the board.");
	ASSERT(p.y < height, "The accessed y-coordinate may not exceed the height of the board.");
	set(p.x, p.y, value);
}
void Foods::set(unsigned x, unsigned y, bool value) noexcept {
	ASSERT(x < width, "The accessed x-coordinate may not exceed the width of the board.");
	ASSERT(y < height, "The accessed y-coordinate may not exceed the height of the board.");
	positions->at(y*width+x) = value;
}
const bool Foods::get(unsigned x, unsigned y) const noexcept {
	ASSERT(x < width, "The accessed x-coordinate may not exceed the width of the board.");
	ASSERT(y < height, "The accessed y-coordinate may not exceed the height of the board.");
	return (*positions)[y*width + x];
}
/*bool& Foods::operator[](const Position& pos) noexcept {
	return get(pos.x, pos.y);
}*/
const bool Foods::operator[](const Position& pos) const noexcept {
	ASSERT(pos.x < width, "The accessed x-coordinate may not exceed the width of the board.");
	ASSERT(pos.y < height, "The accessed y-coordinate may not exceed the height of the board.");
	return get(pos.x, pos.y);
}
const size_t Foods::size() const noexcept {
	return std::count_if(positions->begin(), positions->end(), [](const bool& b){return b;});
}
Foods Foods::clone() const noexcept {
	Foods copy(width, height);
	for (unsigned x = 0; x < width; ++x)
		for (unsigned y = 0; y < height; ++y)
			if (get(x,y))
				copy.set(x, y, true);
	return std::move(copy);
}

State::State(unsigned width, unsigned height, std::vector<Snake>&& snakes, const Foods& food) noexcept
	: width(width), height(height), snakes(std::move(snakes)), food(food) {}
State::State(unsigned width, unsigned height, std::vector<Snake>&& snakes, Foods&& food) noexcept
	: width(width), height(height), snakes(std::move(snakes)), food(std::move(food)) {}
State::State(unsigned width, unsigned height, std::vector<Snake>&& snakes, const std::vector<Position>& food) noexcept
	: width(width), height(height), snakes(std::move(snakes)), food(width, height, food) {}

Move State::getPossibleActions(size_t snake) const noexcept {
	auto& dir = snakes[snake].getDirection();
	return ~dir.opposite();
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
	return isInBounds(pos) && food[pos];
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