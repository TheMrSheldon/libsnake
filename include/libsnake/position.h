#pragma once

#include "move.h"

#include <ostream>

namespace ls {
	/**
	 * @brief Represents a 2D-coordinate.
	 */
	struct Position final {
		/**
		 * @brief The x coordinate of this position.
		 */
		int x;
		/**
		 * @brief The y coordinate of this position.
		 */
		int y;

		/**
		 * @brief Construct a new Position object from the specified x- and y-coordinates.
		 * 
		 * @param x The x coordinate of the new position. Default is 0.
		 * @param y The y coordinate of the new position. Default is 0.
		 */
		inline Position(int x = 0, int y = 0) noexcept : x(x), y(y) {}

		/**
		 * @brief Checks if two positions are equal.
		 * @details Two positions are considered equal if their x- and y-coordinates are
		 * the same.
		 * 
		 * @param other The position to check equality with.
		 * @return true iff the other position is equal to this one.
		 */
		inline bool operator==(const Position& other) const noexcept {
			return x == other.x && y == other.y;
		}

		/**
		 * @brief Checks if two positions are unequal.
		 * @details Two positions are considered unequal if their x- or y- coordinate
		 * is different.
		 * 
		 * @param other The position to check for inequality with.
		 * @return true iff the other position is different from this one. 
		 */
		inline bool operator!=(const Position& other) const noexcept {
			return x != other.x || y != other.y;
		}

		/**
		 * @brief Componentwise adds two positions.
		 * 
		 * @param other The position to add to this position.
		 * @return The sum of this position with \p other.
		 */
		inline Position operator+(const Position& other) const noexcept {
			return Position(x + other.x, y + other.y);
		}

		/**
		 * @brief Componentwise subtracts two positions.
		 * 
		 * @param other The position to subtract from this position.
		 * @return The difference of this position and \p other.
		 */
		inline Position operator-(const Position& other) const noexcept {
			return Position(x - other.x, y - other.y);
		}

		/**
		 * @brief Calculates the position after the move is made.
		 * @details Calculates the position after the move is made. A move is a step by one
		 * in all directions set in the move.
		 * 
		 * @param move The move to be applied to the position.
		 * @return The position after the move was applied.
		 */
		inline Position after_move(const Move& move) const noexcept {
			return Position(x + move.deltaX(), y + move.deltaY());
		}

		inline Position mod(int modx, int mody) const noexcept {
			return Position((x%modx + modx)%modx, (y%mody + mody)%mody);
		}

		/**
		 * @brief Componentwise clamps this position to the coordinates of \p min and \p max.
		 * 
		 * @param min The lower bound to clamp the coordinates to.
		 * @param max The upper bound to clamp the coordinates to.
		 * @return The clamped position.
		 */
		inline Position clamp(const Position& min, const Position& max) const noexcept {
			return Position(std::min(max.x, std::max(min.x, x)), std::min(max.y, std::max(min.y, y)));
		}

		/**
		 * @brief Calculates the direction between this pointe and \p from.
		 * 
		 * @see ls::Move::getDirection
		 * @param from The position to which to calculate the direction.
		 * @return The move that represents the direction from the position \p from to this position. 
		 */
		inline Move directionFrom(const Position& from) const noexcept {
			return ls::Move::getDirection(from.x, from.y, x, y);
		}

		/**
		 * @brief Writes a character-representation of this position to the provided stream.
		 * 
		 * @param os The stream to write the character-representation of the position to.
		 * @param pos The position to write to the string.
		 * @return std::ostream& The stream after the position was written to it.
		 */
		friend std::ostream& operator<<(std::ostream& os, const ls::Position& pos) noexcept;
	};

	inline std::ostream& operator<<(std::ostream& os, const ls::Position& pos) noexcept {
		return os << '<' << pos.x << ',' <<  pos.y << '>';
	}
}