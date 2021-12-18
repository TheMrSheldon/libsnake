#pragma once

#include "definitions.h"

#include <inttypes.h>
#include <ostream>

namespace ls {
	class SnakeFlags final {
	private:
		/**
		 * @brief According to the official battlesnake rules (https://docs.battlesnake.com/references/rules#game-board-and-boundaries)
		 * there can be at most eight snakes in a game.
		 */
        using primitive = uint8_t;
		primitive flags;
	public:
        constexpr static primitive None = 0;
		constexpr static primitive Player1 = 1<<0;
		constexpr static primitive Player2 = 1<<1;
		constexpr static primitive Player3 = 1<<2;
		constexpr static primitive Player4 = 1<<3;
		constexpr static primitive Player5 = 1<<4;
		constexpr static primitive Player6 = 1<<5;
		constexpr static primitive Player7 = 1<<6;
		constexpr static primitive Player8 = 1<<7;

        constexpr inline SnakeFlags(primitive flags = None) noexcept : flags(flags) {}
		constexpr inline bool containsAny(primitive snakes) {
			return (flags & snakes) != None;
		}
		constexpr inline bool containsAll(primitive snakes) {
			return (flags & snakes) == snakes;
		}

		constexpr inline bool operator==(const primitive& other) const noexcept {
			return other == flags;
		}
		constexpr inline bool operator!=(const primitive& other) const noexcept {
			return other != flags;
		}
		constexpr inline SnakeFlags& operator&=(const SnakeFlags& other) noexcept {
			flags &= other.flags;
			return *this;
		}
        constexpr inline SnakeFlags operator&(const SnakeFlags& other) const noexcept {
			return SnakeFlags(flags & other.flags);
		}

		constexpr inline SnakeFlags operator~() const noexcept {
			return SnakeFlags(~flags);
		}

		constexpr static inline SnakeFlags ByIndex(size_t idx) noexcept {
			return SnakeFlags(1<<idx);
		}
		constexpr static inline SnakeFlags FromTo(size_t fromInclusive, size_t toExclusive) noexcept {
            ASSERT(fromInclusive <= 7, "There may be at most 8 snakes thus from should be at most 7.");
            ASSERT(toExclusive <= 8, "There may be at most 8 snakes thus to should be at most 8.");
			const size_t num = toExclusive-fromInclusive;
			const size_t lowestBitsSet = (1<<num)-1;
			return SnakeFlags((primitive)(lowestBitsSet << fromInclusive));
		}

		DLLEXPORT friend std::ostream& operator<<(std::ostream& os, const ls::SnakeFlags& flags) noexcept;
	};
}