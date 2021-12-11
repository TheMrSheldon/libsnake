#pragma once

#include "move.h"
#include "snake.h"
#include "definitions.h"
#include "winner.h"

#include <memory>
#include <ostream>
#include <string>
#include <vector>

namespace ls {
	class State final {
	private:
		const unsigned width;
		const unsigned height;
		const std::vector<Snake> snakes;
		const std::shared_ptr<const std::vector<Position>> foodPositions;
		
	public:
		/**
		 * @brief Construct a new State object by "stepping" the provided state using the given information.
		 * The created state will have the two snakes moved using the provided action. If either snake has
		 * eaten (eaten1 or eaten2 respectively are set) the respective snake gets elongated. If either snake
		 * was killed (kill1 or kill2 respectively) the according snake is set to 0 health.
		 * 
		 * @param other The previous state from which data is copied.
		 * @param move1 The direction in which the first snake is moved for the new (this) state.
		 * @param move2 The direction in which the second snake is moved for the new (this) state.
		 * @param eaten1 True if the first snake has eaten after enacting move1 in transition to this state.
		 * @param eaten2 True if the second snake has eaten after enacting move2 in transition to this state.
		 * @param kill1 True if the first snake has died after enacting move1 in transition to this state.
		 * @param kill2 True if the second snake has died after enacting move2 in transition to this state.
		 * @see Snake::after_move()
		 */
		State(const State& other, Move move1, Move move2, bool eaten1, bool eaten2, bool kill1, bool kill2) noexcept;
	public:
		DLLEXPORT State(State&& other) : width(other.width), height(other.height), snakes(std::move(other.snakes)), foodPositions(std::move(other.foodPositions)) {}
		DLLEXPORT State(const State& other) : width(other.width), height(other.height), snakes(other.snakes), foodPositions(other.foodPositions) {}
		DLLEXPORT State(unsigned width, unsigned height, std::vector<Snake>& snakes, std::vector<Position>& food) noexcept;
		DLLEXPORT State(unsigned width, unsigned height, std::vector<SnakeData> snakes, PosArray food) noexcept;

		DLLEXPORT Move getPossibleActions(unsigned snake) const noexcept;

		inline const std::vector<Snake>& getSnakes() const noexcept { return snakes; }
		inline const Snake& getSnake(std::size_t index) const noexcept { return snakes[index]; }
		inline const std::vector<Position>& getFood() const noexcept { return *foodPositions; }
		inline unsigned getWidth() const noexcept { return width; }
		inline unsigned getHeight() const noexcept { return height; }
		DLLEXPORT bool isInBounds(const Position& pos) const noexcept;
		DLLEXPORT bool isBlocked(const Position& pos) const noexcept;
		DLLEXPORT std::size_t getSnakeIndexAt(const Position& pos) const noexcept;
		DLLEXPORT bool isFoodAt(const Position& pos) const noexcept;

		DLLEXPORT void print(std::ostream& out) const noexcept;
	};
}