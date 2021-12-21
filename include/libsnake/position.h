#pragma once

#include "move.h"

#include <ostream>

namespace ls {
	struct Position final {
		int x, y;

		inline Position(int x = 0, int y = 0) noexcept : x(x), y(y) {}

		inline bool operator==(const Position& other) const noexcept {
			return x == other.x && y == other.y;
		}
		inline bool operator!=(const Position& other) const noexcept {
			return x != other.x || y != other.y;
		}
		inline Position operator+(const Position& other) const noexcept {
			return Position(x + other.x, y + other.y);
		}
		inline Position operator-(const Position& other) const noexcept {
			return Position(x - other.x, y - other.y);
		}

		inline Position after_move(const Move& move) const noexcept {
			return Position(x + move.deltaX(), y + move.deltaY());
		}

		inline Position clamp(const Position& min, const Position& max) const noexcept {
			return Position(std::min(max.x, std::max(min.x, x)), std::min(max.y, std::max(min.y, y)));
		}

		inline Move directionFrom(const Position& from) const noexcept {
			return ls::Move::getDirection(from.x, from.y, x, y);
		}

		friend std::ostream& operator<<(std::ostream& os, const ls::Position& pos) noexcept;
	};

	inline std::ostream& operator<<(std::ostream& os, const ls::Position& pos) noexcept {
		return os << '<' << pos.x << ',' <<  pos.y << '>';
	}
}