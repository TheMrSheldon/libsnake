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
		/**
		 * @brief The SnakeFlags representing no player.
		 */
        constexpr static primitive None = 0;
		/**
		 * @brief The SnakeFlags representing the player at index 0.
		 */
		constexpr static primitive Player1 = 1<<0;
		/**
		 * @brief The SnakeFlags representing the player at index 1.
		 */
		constexpr static primitive Player2 = 1<<1;
		/**
		 * @brief The SnakeFlags representing the player at index 2.
		 */
		constexpr static primitive Player3 = 1<<2;
		/**
		 * @brief The SnakeFlags representing the player at index 3.
		 */
		constexpr static primitive Player4 = 1<<3;
		/**
		 * @brief The SnakeFlags representing the player at index 4.
		 */
		constexpr static primitive Player5 = 1<<4;
		/**
		 * @brief The SnakeFlags representing the player at index 5.
		 */
		constexpr static primitive Player6 = 1<<5;
		/**
		 * @brief The SnakeFlags representing the player at index 6.
		 */
		constexpr static primitive Player7 = 1<<6;
		/**
		 * @brief The SnakeFlags representing the player at index 7.
		 */
		constexpr static primitive Player8 = 1<<7;
		
        constexpr inline SnakeFlags(primitive flags = None) noexcept : flags(flags) {}
		constexpr inline bool containsAny(primitive snakes) const noexcept {
			return (flags & snakes) != None;
		}
		constexpr inline bool containsAll(primitive snakes) const noexcept {
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
		constexpr inline SnakeFlags& operator|=(const SnakeFlags& other) noexcept {
			flags |= other.flags;
			return *this;
		}
        constexpr inline SnakeFlags operator&(const SnakeFlags& other) const noexcept {
			return SnakeFlags(flags & other.flags);
		}
        constexpr inline SnakeFlags operator|(const SnakeFlags& other) const noexcept {
			return SnakeFlags(flags | other.flags);
		}

		/**
		 * @brief Inverts the flags.
		 * 
		 * @return An instance with the inverted flags set. 
		 */
		constexpr inline SnakeFlags operator~() const noexcept {
			return SnakeFlags(~flags);
		}

		/**
		 * @brief Counts the number of bits set.
		 * 
		 * @return The number of bits set.
		 */
		constexpr inline size_t size() const noexcept {
			return containsAny(Player1) + containsAny(Player2) + containsAny(Player3) + containsAny(Player4) +
				containsAny(Player5) + containsAny(Player6) + containsAny(Player7) + containsAny(Player8);
		}

		constexpr size_t getIndex() const noexcept {
			ASSERT(size() == 1, "The index may only be retrieved if the flags only contain one snake.");
			for (size_t i = 0;; ++i)
				if (containsAny(SnakeFlags::ByIndex(i).flags))
					return i;
			ASSERT(false, "No index found");
		}

		/**
		 * @brief Casts the snake instance to an integer in which the i-th bit is set iff the player at index i
		 * is part of this snake flags instance.
		 * 
		 * @return The integer representing this flag instance.
		 */
		constexpr operator primitive() const noexcept {
			return flags;
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