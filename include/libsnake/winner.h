#pragma once

#include "definitions.h"

#include <inttypes.h>
#include <cstddef>
#include <ostream>

namespace ls {

	constexpr static uint8_t ByIndex(std::size_t index) noexcept {
		ASSERT(index < 8, "There may be at most 8 snakes.");
		return 1<<index;
	}

	class Winner final {
	public:
		/**
		 * @brief According to the official battlesnake rules (https://docs.battlesnake.com/references/rules#game-board-and-boundaries)
		 * there can be at most eight snakes in a game.
		 */
		using snakes = uint8_t;
		
		constexpr static snakes None = 0;
		constexpr static snakes Player1 = ByIndex(0);
		constexpr static snakes Player2 = ByIndex(1);
		constexpr static snakes Player3 = ByIndex(2);
		constexpr static snakes Player4 = ByIndex(3);
		constexpr static snakes Player5 = ByIndex(4);
		constexpr static snakes Player6 = ByIndex(5);
		constexpr static snakes Player7 = ByIndex(6);
		constexpr static snakes Player8 = ByIndex(7);
	private:
		snakes winner_flags;
	
	public:
		constexpr inline Winner(snakes flags = None) noexcept : winner_flags(flags) {}
		constexpr inline bool containsAny(snakes snakes) {
			return (winner_flags & snakes) != None;
		}
		constexpr inline bool containsAll(snakes snakes) {
			return (winner_flags & snakes) == snakes;
		}

		constexpr inline bool operator==(const snakes& other) const noexcept {
			return other == winner_flags;
		}
		constexpr inline bool operator!=(const snakes& other) const noexcept {
			return other != winner_flags;
		}
		constexpr inline Winner& operator&=(const Winner& other) noexcept {
			winner_flags &= other.winner_flags;
			return *this;
		}

		constexpr inline Winner operator~() const noexcept {
			return Winner(~winner_flags);
		}

		constexpr static inline Winner ByIndex(size_t idx) noexcept {
			return Winner(1<<idx);
		}
		constexpr static inline Winner FromTo(size_t fromInclusive, size_t toExclusive) noexcept {
			const size_t num = toExclusive-fromInclusive;
			const size_t lowestBitsSet = (1<<num)-1;
			return Winner(lowestBitsSet << fromInclusive);
		}

		friend std::ostream& operator<<(std::ostream& os, const ls::Winner& winner) noexcept;
	};

	inline std::ostream& operator<<(std::ostream& os, const ls::Winner& winner) noexcept {
		if (winner.winner_flags == Winner::None)
			return os << "Winner::None";
		int i = 0;
		os << "Winner::{";
		for (unsigned i = 0; winner.winner_flags >> i != Winner::None; ++i) {
			if ((winner.winner_flags>>i) & 1) {
				if (i > 0)
					os << ", ";
				os << i;
			}
		}
		return os << "}";
	}
}