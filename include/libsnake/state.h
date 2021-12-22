#pragma once

#include "move.h"
#include "snake.h"
#include "definitions.h"
#include "snake_flags.h"

#include <memory>
#include <ostream>
#include <string>
#include <tuple>
#include <vector>

namespace ls {

	class Foods final {
	private:
		const unsigned width;
		const unsigned height;
		std::shared_ptr<std::vector<uint8_t>> positions;

	public:
		DLLEXPORT Foods(unsigned width, unsigned height) noexcept;
		DLLEXPORT Foods(unsigned width, unsigned height, std::vector<Position> pos) noexcept;
		DLLEXPORT void set(const Position& p, bool value) noexcept;
		DLLEXPORT void set(unsigned x, unsigned y, bool value) noexcept;
		DLLEXPORT const bool get(unsigned x, unsigned y) const noexcept;
		//DLLEXPORT bool& operator[](const Position& pos) noexcept;
		DLLEXPORT const bool operator[](const Position& pos) const noexcept;
		DLLEXPORT const size_t size() const noexcept;
		DLLEXPORT Foods clone() const noexcept;

		inline const std::vector<uint8_t>* __raw() const noexcept { return positions.get(); }
	};

	class State final {
	private:
		const unsigned width;
		const unsigned height;
		const std::vector<Snake> snakes;
		const Foods food;
		
	public:
		DLLEXPORT State(State&& other) noexcept : width(other.width), height(other.height), snakes(std::move(other.snakes)), food(std::move(other.food)) {}
		DLLEXPORT State(const State& other) noexcept : width(other.width), height(other.height), snakes(other.snakes), food(other.food) {}
		DLLEXPORT State(unsigned width, unsigned height, std::vector<Snake>&& snakes, const std::vector<Position>& food) noexcept;
		DLLEXPORT State(unsigned width, unsigned height, std::vector<Snake>&& snakes, const Foods& food) noexcept;
		DLLEXPORT State(unsigned width, unsigned height, std::vector<Snake>&& snakes, Foods&& food) noexcept;

		DLLEXPORT Move getPossibleActions(size_t snake) const noexcept;

		inline const std::vector<Snake>& getSnakes() const noexcept { return snakes; }
		inline const Snake& getSnake(std::size_t index) const noexcept { return snakes[index]; }
		inline const Foods& getFood() const noexcept { return food; }
		inline unsigned getWidth() const noexcept { return width; }
		inline unsigned getHeight() const noexcept { return height; }
		DLLEXPORT bool isInBounds(const Position& pos) const noexcept;
		DLLEXPORT bool isBlocked(const Position& pos) const noexcept;
		DLLEXPORT std::size_t getSnakeIndexAt(const Position& pos) const noexcept;
		DLLEXPORT bool isFoodAt(const Position& pos) const noexcept;

		DLLEXPORT friend std::ostream& operator<<(std::ostream& os, const State& state) noexcept;

		template<typename F>
		static void drawBoard(std::ostream& out, unsigned width, unsigned height, F callback, unsigned cellWidth=1) {
			constexpr char box_hor = '\xC4';
			constexpr char box_vert = '\xB3';
			constexpr char box_tl = '\xDA';
			constexpr char box_tr = '\xBF';
			constexpr char box_bl = '\xC0';
			constexpr char box_br = '\xD9';
			out << box_tl << std::string((width*(1+cellWidth))+1, box_hor) << box_tr << std::endl;
			for (unsigned y = 0; y < height; y++) {
				out << box_vert << ' ';
				for (unsigned x = 0; x < width; x++)
					out << callback(ls::Position(x,height-1-y)) << ' ';
				out << box_vert << '\n';
			}
			out << box_bl << std::string((width*(1+cellWidth))+1, box_hor) << box_br << std::endl;
		}
	};
}