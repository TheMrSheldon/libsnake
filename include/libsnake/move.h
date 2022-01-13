#pragma once

namespace ls {
	/**
	 * @brief The Move class is an iterable flag-register for the 4 directions: up, down, left, and right.
	 */
	class Move final {
	public:
		/**
		 * @brief No bit is set -- a move in no direction.
		 */
		constexpr static int none = 0;
		/**
		 * @brief Only the "up"-bit is set.
		 * @see Move::isUp()
		 */
		constexpr static int up = 1;
		/**
		 * @brief Only the "left"-bit is set.
		 * @see Move::isLeft()
		 */
		constexpr static int left = 2;
		/**
		 * @brief Only the "down"-bit is set.
		 * @see Move::isDown()
		 */
		constexpr static int down = 4;
		/**
		 * @brief Only the "right"-bit is set.
		 * @see Move::isRight()
		 */
		constexpr static int right = 8;
	private:
		/**
		 * @brief Masks an int to only the bits used by the ls::Move flag-register.
		 */
		constexpr static int mask = 0b1111;
		/**
		 * @brief The flags stored in this ls::Move instance.
		 */
		int flags;
	public:
		/**
		 * @brief An iterator implementation for ls::Move.
		 * @details The iterator takes an ls::Move (stored in Iterator::move) and the first flag (stored in Iterator::flag).
		 * Incrementing and dereferencing the iterator repeatedly returns all flags stored within Iterator::move. Incrementing
		 * and dereferencing further results in Move::none.
		 */
		class Iterator final {
		private:
			/**
			 * @brief The ls::Move object to iterate over.
			 */
			const class Move& move;
			/**
			 * @brief The flag the iterator currently is on.
			 */
			int flag;
		public:
			/**
			 * @brief Constructs a new Iterator object that iterates over \p move starting with the flag \p flag.
			 * 
			 * @param move The ls::Move object to iterate over.
			 * @param flag The first flag of the iterator.
			 */
			Iterator(const class Move& move, int flag) : move(move), flag(flag) {
				// If the passed first flag of the iterator is not set in the move instance
				// we want to place the iterator on the next flag that is set in move.
				if (!move.containsFlag(flag))
					++(*this);
			}
			/**
			 * @brief Dereferences the iterator by returning a ls::Move object that has only the flag set that the iterator
			 * is currently on. The Move::end() iterator will return ls::Move::none.
			 * 
			 * @return The flag the iterator is currently on.
			 */
			constexpr inline Move operator*() {
				return flag;
			}
			/**
			 * @brief Increments the iterator. This places it on the first flag that is set in Iterator::move
			 * after the one the iterator is currently on. If Iterator::move has no further flags set the iterator
			 * is set to 0 (the Move::end() iterator).
			 * 
			 * @return A reference to this ls::Move::Iterator instance.
			 */
			constexpr inline Iterator& operator++() {
				do
					flag = (flag << 1) & Move::mask;
				while (!move.containsFlag(flag));
				return *this;
			}
			/**
			 * @brief Checks for inequality with the other Iterator instance. Two iterators are considered unequal if they are not on the same flag.
			 * Note that the inequality check does not take the underlying move that is iterated over into account.
			 * 
			 * @param other The other iterator to check for inequality with.
			 * @return true iff this operator and the \p other iterator are unequal.
			 */
			constexpr inline bool operator!=(const Iterator& other) const noexcept {
				return flag != other.flag;
			}
		};

		/**
		 * @brief Creates a new Move instance from the provided flags.
		 * 
		 * @param flags The flags that should be set. Default is Move::none.
		 */
		constexpr inline Move(int flags = Move::none) : flags(flags) {}

		/**
		 * @brief Checks if the bits that are set in \p flag are also set in this flag.
		 * @details If \p flag is Move::none (no bit is set) true is returned. Note that this may have more bits
		 * set than \p flag.
		 * 
		 * @param flag The flags to check for in these movement flags.
		 * @return true iff all bits that are set in \p flag are also set in this.
		 */
		constexpr inline bool containsFlag(const Move& flag) const noexcept {
			return (flag.flags == 0) || (flags & flag.flags);
		}

		/**
		 * @brief Checks if the Move::up bit is set in this flag.
		 * 
		 * @return true iff the Move::up bit is set.
		 */
		constexpr inline bool isUp() const noexcept {
			return containsFlag(Move::up);
		}
		/**
		 * @brief Checks if the Move::left bit is set in this flag.
		 * 
		 * @return true iff the Move::left bit is set.
		 */
		constexpr inline bool isLeft() const noexcept {
			return containsFlag(Move::left);
		}
		/**
		 * @brief Checks if the Move::down bit is set in this flag.
		 * 
		 * @return true iff the Move::down bit is set.
		 */
		constexpr inline bool isDown() const noexcept {
			return containsFlag(Move::down);
		}
		/**
		 * @brief Checks if the Move::right bit is set in this flag.
		 * 
		 * @return true iff the Move::right bit is set.
		 */
		constexpr inline bool isRight() const noexcept {
			return containsFlag(Move::right);
		}
		/**
		 * @brief Returns the x-direction of this move. If this move moves right, +1 is returned.
		 * If this move moves left, -1 is returned. If it moves right and left or if neither right
		 * nor left are set, it moves 0 in the x-direction.
		 * 
		 * @return The x-direction of this move.
		 */
		constexpr inline int deltaX() const noexcept {
			return isRight() - isLeft();
		}
		/**
		 * @brief Returns the y-direction of this move. If this move moves up, +1 is returned.
		 * If this move moves down, -1 is returned. If it moves up and down or if neither up
		 * nor down are set, it moves 0 in the y-direction.
		 * 
		 * @return The y-direction of this move.
		 */
		constexpr inline int deltaY() const noexcept {
			return isUp() - isDown();
		}

		/**
		 * @brief Returns a move instance that contains the opposite directions of this move.
		 * @details Note the difference with the ~-operator which inverts the flags on the move
		 * instance: e.g. ~left is up|down|right whereas opposite(left) is right. It is also possible
		 * to get the opposite of a move which has multiple flags set: opposite(up|left) is down|right
		 * additionally, opposite(up|left|right) is down|right|left.
		 * 
		 * @return A new ls::Move instance pointing in the opposite direction of this move.
		 */
		constexpr inline Move opposite() const noexcept {
			// Rotate input-bits right by 2
			return Move(((flags >> 2) | (flags << 2)) & Move::mask);
		}

		/**
		 * @brief Calculates the number of bits set in this instance.
		 * 
		 * @return The number of bits set in this instance.
		 */
		constexpr inline unsigned size() const noexcept {
			return isUp() + isDown() + isLeft() + isRight();
		}
		
		/**
		 * @brief Checks this instance for equality with \p other.
		 * @details Checks this instance for equality with \p other. Two instances of ls::Move
		 * are considered equal iff they have the same flags set.
		 * 
		 * @param other The ls::Move instance to check for equality with.
		 * @return true iff this ls::Move instance is equal to \p other.
		 */
		constexpr inline bool operator==(const Move& other) const noexcept {
			return flags == other.flags;
		}
		/**
		 * @brief Checks this instance for inequality with \p other.
		 * @details Checks this instance for inequality with \p other. Two instances of ls::Move
		 * are considered unequal iff they do not have the same flags set.
		 * 
		 * @param other The ls::Move instance to check for inequality with.
		 * @return true iff this ls::Move instance is not equal to \p other.
		 */
		constexpr inline bool operator!=(const Move& other) const noexcept {
			return flags != other.flags;
		}
		/**
		 * @brief Intersects the flags stored in this ls::Move instance with the \p other and
		 * stores the result in this.
		 * @details The intersection has only those flags set that are set in both, this and
		 * \p other.
		 * 
		 * @param other The ls::Move instance to intersect with.
		 * @return A reference to this ls::Move instance.
		 */
		constexpr inline Move& operator&=(const Move& other) noexcept {
			flags &= other.flags;
			return *this;
		}
		/**
		 * @brief Joins the flags stored in this ls::Move instance with the \p other and
		 * stores the result in this.
		 * @details The union has only those flags set that are set in both, this and
		 * \p other.
		 * 
		 * @param other The ls::Move instance to join with.
		 * @return A reference to this ls::Move instance.
		 */
		constexpr inline Move& operator|=(const Move& other) noexcept {
			flags |= other.flags;
			return *this;
		}
		/**
		 * @brief Intersects the flags stored in this ls::Move instance with the \p other.
		 * @details Returns a new ls::Move instance that is the intersection of this ls::Move with
		 * the \p other. The intersection has only those flags set that are set in both, this and
		 * \p other.
		 * 
		 * @param other The ls::Move instance to intersect with.
		 * @return A new ls::Move instance that is the intersection of this move and \p other.
		 */
		constexpr inline Move operator&(const Move& other) const noexcept {
			return Move(flags & other.flags);
		}
		/**
		 * @brief Join the flags stored in this ls::Move instance with the \p other.
		 * @details Returns a new ls::Move instance that is the union of this ls::Move with
		 * the \p other. The union has all those flags set that are set at least one of this and
		 * \p other.
		 * 
		 * @param other The ls::Move instance to join with.
		 * @return A new ls::Move instance that is the union of this move and \p other.
		 */
		constexpr inline Move operator|(const Move& other) const noexcept {
			return Move(flags | other.flags);
		}
		/**
		 * @brief Invers all flags of this move. As such the resulting ls::Move instance will contain
		 * every flag except for the ones set in this instance.
		 * 
		 * @return A new ls::Move instance with only the flags set that are not set in this instance.
		 */
		constexpr inline Move operator~() const noexcept {
			return Move((~flags) & Move::mask);
		}

		/**
		 * @brief Returns an iterator to the first move stored within these flags.
		 * 
		 * @return The iterator to the first move stored within these flags. 
		 */
		inline Iterator begin() const noexcept {
			return Iterator(*this, 1);
		}
		/**
		 * @brief Returns an iterator to the last move stored within these flags.
		 * 
		 * @return The iterator to the last move stored within these flags. 
		 */
		inline Iterator end() const noexcept {
			return Iterator(*this, 0);
		}

		/**
		 * @brief Calculates the move between the two coordinate (from and to) passed via \p fromX, \p fromY and \p toX and \p toY.
		 * @details The Move::right flag is set iff toX > fromX. The Move::left flag is set iff toX < fromX. The Move::up flag
		 * is set iff toY > fromY. The Move::down flag is set iff toY < fromY. 
		 * 
		 * @param fromX The x component of the source coordinate.
		 * @param fromY The y component of the source coordinate.
		 * @param toX The x component of the target coordinate.
		 * @param toY The y component of the target coordinate.
		 * @return The move between the two provided coordinates.
		 */
		constexpr static inline Move getDirection(const unsigned fromX, const unsigned fromY, const unsigned toX, const unsigned toY) noexcept {
			const bool right = toX > fromX;
			const bool left = toX < fromX;
			const bool up = toY > fromY;
			const bool down = toY < fromY;
			return Move(right*Move::right | left*Move::left | up*Move::up | down*Move::down);
		}
	};
}