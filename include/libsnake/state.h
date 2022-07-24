#pragma once

#include "move.h"
#include "snake.h"
#include "definitions.h"
#include "snake_flags.h"

#include <memory>
#include <ostream>
#include <set>
#include <string>
#include <tuple>
#include <vector>

namespace ls {

	/**
	 * @brief A datastructure that stores the food-positions.
	 */
	class FieldFlags final {
	private:
		struct Field {
			bool food : 1;
			bool hazard : 1;
		};

		/**
		 * @brief The width of the playarea.
		 */
		const unsigned width;
		/**
		 * @brief The height of the playarea.
		 */
		const unsigned height;
		/**
		 * @brief Stores a boolean for each position that is set to true iff food is at that position.
		 * @details The vector is indexed in row-major order. Thus the index for the coordinates (x,y)
		 * is y*width + x. The vector is additionally stored in an std::shared_ptr to allow for copy-
		 * on-write.
		 */
		std::vector<Field> positions;

		DLLEXPORT Field& get(unsigned x, unsigned y) noexcept;
		DLLEXPORT Field get(unsigned x, unsigned y) const noexcept;
	public:
		/**
		 * @brief Creates a new Foods object that stores the food-locations for a field of the specified
		 * width and height. Initially no food is stored anywhere on the field.
		 * 
		 * @param width the width of the playarea.
		 * @param height the height of the playarea.
		 */
		DLLEXPORT FieldFlags(unsigned width, unsigned height) noexcept;
		DLLEXPORT FieldFlags(unsigned width, unsigned height, const std::vector<Position>& pos, const std::vector<Position>& hazards) noexcept;
		DLLEXPORT void setFood(const Position& p, bool value) noexcept;
		DLLEXPORT void setFood(unsigned x, unsigned y, bool value) noexcept;
		DLLEXPORT const bool getFood(const Position& p) const noexcept;
		
		DLLEXPORT void setHazard(const Position& p, bool value) noexcept;
		DLLEXPORT void setHazard(unsigned x, unsigned y, bool value) noexcept;
		DLLEXPORT const bool getHazard(const Position& p) const noexcept;
		
		DLLEXPORT const size_t numFood() const noexcept;
	};

	/**
	 * @brief Represents the gamestate of snake.
	 */
	class State final {
	private:
		/**
		 * @brief The width of the playarea.
		 */
		const unsigned width;
		/**
		 * @brief The height of the playarea.
		 */
		const unsigned height;
		const std::vector<Snake> snakes;
		/**
		 * @brief Stores information about fields and hazards.
		 */
		FieldFlags fields;
		std::set<ls::SnakeFlags> livingSquads;
		const std::vector<bool> hazards;
		
	public:
		DLLEXPORT State(State&& other) noexcept : width(other.width), height(other.height), snakes(std::move(other.snakes)),
													fields(std::move(other.fields)), livingSquads(std::move(other.livingSquads)) {}
		DLLEXPORT State(const State& other) noexcept : width(other.width), height(other.height), snakes(other.snakes), fields(other.fields),
													livingSquads(other.livingSquads) {}
		DLLEXPORT State(unsigned width, unsigned height, std::vector<Snake>&& snakes, const std::vector<Position>& food, const std::vector<Position>& hazards) noexcept;
		DLLEXPORT State(unsigned width, unsigned height, std::vector<Snake>&& snakes, const FieldFlags& fields) noexcept;
		DLLEXPORT State(unsigned width, unsigned height, std::vector<Snake>&& snakes, FieldFlags&& fields) noexcept;

		DLLEXPORT Move getPossibleActions(size_t snake) const noexcept;
		
		/**
		 * @brief Returns the snake-data of this gamestate.
		 * 
		 * @return The snake-data of this gamestate.
		 */
		inline const std::vector<Snake>& getSnakes() const noexcept { return snakes; }
		/**
		 * @brief Returns the number of total snakes that parttake in the game (including dead snakes).
		 * 
		 * @return The number of total snakes that parttake in the game (including dead snakes).
		 */
		inline std::size_t getNumSnakes() const noexcept { return snakes.size(); }
		inline const Snake& getSnake(std::size_t index) const noexcept { return snakes[index]; }
		/**
		 * @brief Returns the squads that have at least one living snake remaining within State::getSnakes().
		 * 
		 * @return A set containing the squads that have at least one living snake remaining within State::getSnakes().
		 */
		inline const std::set<SnakeFlags>& getLivingSquads() const noexcept { return livingSquads; }
		inline const FieldFlags& getFieldInfos() const noexcept { return fields; }
		inline unsigned getWidth() const noexcept { return width; }
		inline unsigned getHeight() const noexcept { return height; }
		DLLEXPORT bool isInBounds(const Position& pos) const noexcept;
		/**
		 * @brief Checks if the field at \p pos is blocked by any of the snakes in \p mask.
		 * 
		 * @param pos The position for which to check if it is blocked.
		 * @param mask The snakes for which to check if they block the field at \p pos.
		 * @param ignoreTailtips True iff the last element of a snakes tail should not be considered blocked.
		 * @return true iff the field at \p pos is blocked by any of the snakes in \p mask. 
		 */
		DLLEXPORT bool isBlocked(const Position& pos, const SnakeFlags& mask, bool ignoreTailtips=false) const noexcept;
		DLLEXPORT std::size_t getSnakeIndexAt(const Position& pos, bool ignoreTailtips=false) const noexcept;
		DLLEXPORT bool isFoodAt(const Position& pos) const noexcept;
		DLLEXPORT bool isHazardAt(const Position& pos) const noexcept;
		DLLEXPORT void setHazardAt(const Position& pos, bool hazard = true) noexcept;

		DLLEXPORT friend std::ostream& operator<<(std::ostream& os, const State& state) noexcept;

		/**
		 * @brief Prints a board to the provided outputstream.
		 * @details The function prints a box of size \p width &times; \p height and calls the callback to print the cell
		 * for each position. It is assumed that the callback returns exactly \p cellWidth characters which are then
		 * printed to the stream.
		 * 
		 * @tparam F The type of the callback. It is kept generic to allow for any callable object to be passed.
		 * @param out The outputstream to print the state to.
		 * @param width The width of the state.
		 * @param height The height of the state.
		 * @param callback A callback called with a Position argument to retrieve what to print for the respective cell.
		 * @param cellWidth The width of a single state-cell.
		 */
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