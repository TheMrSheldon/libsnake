#include <libsnake/state.h>

#include <libsnake/util.h>

#include <libsnake/definitions.h>

#include <algorithm>
#include <stdio.h>

using namespace ls;

FieldFlags::FieldFlags(unsigned width, unsigned height) noexcept : width(width), height(height),
	positions(std::vector<Field>(width*height, Field{.food=false, .hazard=false})) {}
FieldFlags::FieldFlags(unsigned width, unsigned height, const std::vector<Position>& pos, const std::vector<Position>& hazards) noexcept : FieldFlags(width, height) {
	for (const auto& p : pos)
		setFood(p.x, p.y, true);
	for (const auto& p : hazards)
		setHazard(p.x, p.y, true);
}

FieldFlags::Field& FieldFlags::get(unsigned x, unsigned y) noexcept {
	ASSERT(x < width, "The accessed x-coordinate may not exceed the width of the board.");
	ASSERT(y < height, "The accessed y-coordinate may not exceed the height of the board.");
	return positions.at(y*width+x);
}
FieldFlags::Field FieldFlags::get(unsigned x, unsigned y) const noexcept {
	ASSERT(x < width, "The accessed x-coordinate may not exceed the width of the board.");
	ASSERT(y < height, "The accessed y-coordinate may not exceed the height of the board.");
	return positions.at(y*width+x);
}

void FieldFlags::setFood(const Position& p, bool value) noexcept {
	setFood(p.x, p.y, value);
}
void FieldFlags::setFood(unsigned x, unsigned y, bool value) noexcept {
	get(x,y).food = value;
}
const bool FieldFlags::getFood(const Position& p) const noexcept {
	return get(p.x, p.y).food;
}
void FieldFlags::setHazard(const Position& p, bool value) noexcept {
	setHazard(p.x, p.y, value);
}
void FieldFlags::setHazard(unsigned x, unsigned y, bool value) noexcept {
	get(x,y).hazard = value;
}
const bool FieldFlags::getHazard(const Position& p) const noexcept {
	return get(p.x, p.y).hazard;
}
const size_t FieldFlags::numFood() const noexcept {
	return std::count_if(positions.begin(), positions.end(), [](const FieldFlags::Field& f){return f.food;});
}

State::State(unsigned width, unsigned height, std::vector<Snake>&& snakes, const FieldFlags& fields) noexcept
	: width(width), height(height), snakes(std::move(snakes)), fields(fields) {
		for (const auto& snake : getSnakes())
			if (!snake.isDead())
				livingSquads.insert(snake.getSquad());
	}
State::State(unsigned width, unsigned height, std::vector<Snake>&& snakes, FieldFlags&& fields) noexcept
	: width(width), height(height), snakes(std::move(snakes)), fields(std::move(fields)) {
		for (const auto& snake : getSnakes())
			if (!snake.isDead())
				livingSquads.insert(snake.getSquad());
	}
State::State(unsigned width, unsigned height, std::vector<Snake>&& snakes, const std::vector<Position>& food, const std::vector<Position>& hazards) noexcept
	: State(width, height, std::move(snakes), std::move(FieldFlags(width, height, food, hazards))) {};

Move State::getPossibleActions(size_t snake) const noexcept {
	auto& dir = snakes[snake].getDirection();
	return ~dir.opposite();
}

bool State::isInBounds(const Position& pos) const noexcept {
	return pos.x >= 0 && pos.y >= 0 && pos.x < getWidth() && pos.y < getHeight();
}

bool State::isBlocked(const Position& pos, const SnakeFlags& mask, bool ignoreTailtips) const noexcept {
	if (!isInBounds(pos))
		return true;
	const auto idx = getSnakeIndexAt(pos, ignoreTailtips);
	const bool blockedBySnake = idx < snakes.size() && mask.containsAny(SnakeFlags::ByIndex(idx));
	return blockedBySnake;
}

std::size_t State::getSnakeIndexAt(const Position& pos, bool ignoreTailtips) const noexcept {
	std::size_t index = 0;
	for (; index < snakes.size(); ++index) {
		const auto& body = snakes[index].getBody();
		const auto endIt = (ignoreTailtips && body.begin() != body.end())? std::prev(body.end()) : body.end();
		if (utl::contains(body.begin(), endIt, pos))
			return index;
	}
	return index;
}

bool State::isFoodAt(const Position& pos) const noexcept {
	return isInBounds(pos) && fields.getFood(pos);
}
bool State::isHazardAt(const Position& pos) const noexcept {
	return isInBounds(pos) && fields.getHazard(pos);
}
void State::setHazardAt(const Position& pos, bool hazard) noexcept {
	if (isInBounds(pos))
		fields.setHazard(pos, hazard);
}

namespace ls {
	std::ostream& operator<<(std::ostream& os, const State& state) noexcept {
		State::drawBoard(os, state.getWidth(), state.getHeight(), [state](const Position& pos) {
			if (state.isFoodAt(pos))
				return 'o';
			auto snake = state.getSnakeIndexAt(pos);
			if (snake < state.getNumSnakes())
				return std::to_string(snake+1)[0];
			return '.';
		});
		return os;
	}
}