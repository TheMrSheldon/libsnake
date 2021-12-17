#pragma once

namespace ls {

	class Move final {
	public:
		constexpr static int none = 0;
		constexpr static int up = 1;
		constexpr static int left = 2;
		constexpr static int down = 4;
		constexpr static int right = 8;
	private:
		constexpr static int mask = 0b1111;
		int flags;
	public:
		class Iterator final {
		private:
			const class Move& move;
			int flag;
		public:
			Iterator(const class Move& move, int flag) : move(move), flag(flag) {}
			constexpr inline Move operator*() {
				return flag;
			}
			constexpr inline Iterator& operator++() {
				do
					flag = (flag << 1) & Move::mask;
				while (!move.containsFlag(flag));
				return *this;
			}
			constexpr inline bool operator!=(const Iterator& other) const noexcept {
				return flag != other.flag;
			}
		};

		constexpr inline Move(int flags = 0) : flags(flags) {}

		constexpr inline bool containsFlag(const Move& flag) const noexcept {
			return (flag.flags == 0) || (flags & flag.flags);
		}

		constexpr inline bool isUp() const noexcept {
			return containsFlag(Move::up);
		}
		constexpr inline bool isLeft() const noexcept {
			return containsFlag(Move::left);
		}
		constexpr inline bool isDown() const noexcept {
			return containsFlag(Move::down);
		}
		constexpr inline bool isRight() const noexcept {
			return containsFlag(Move::right);
		}
		constexpr inline int deltaX() const noexcept {
			return isRight() - isLeft();
		}
		constexpr inline int deltaY() const noexcept {
			return isUp() - isDown();
		}

		constexpr inline Move opposite() const noexcept {
			// Rotate input-bits right by 2
			return Move(((flags >> 2) | (flags << 2)) & Move::mask);
		}

		constexpr inline unsigned size() const noexcept {
			return isUp() + isDown() + isLeft() + isRight();
		}

		constexpr inline bool operator==(const Move& other) const noexcept {
			return flags == other.flags;
		}
		constexpr inline bool operator!=(const Move& other) const noexcept {
			return flags != other.flags;
		}
		constexpr inline Move& operator&=(const Move& other) noexcept {
			flags &= other.flags;
			return *this;
		}
		constexpr inline Move& operator|=(const Move& other) noexcept {
			flags |= other.flags;
			return *this;
		}
		constexpr inline Move operator&(const Move& other) const noexcept {
			return Move(flags & other.flags);
		}
		constexpr inline Move operator|(const Move& other) const noexcept {
			return Move(flags | other.flags);
		}
		constexpr inline Move operator~() const noexcept {
			return Move((~flags) & Move::mask);
		}

		inline Iterator begin() const noexcept {
			return Iterator(*this, 1);
		}
		inline Iterator end() const noexcept {
			return Iterator(*this, 0);
		}

		constexpr static inline Move getDirection(const unsigned fromX, const unsigned fromY, const unsigned toX, const unsigned toY) noexcept {
			const bool right = toX > fromX;
			const bool left = toX < fromX;
			const bool up = toY > fromY;
			const bool down = toY < fromY;
			return Move(right*Move::right | left*Move::left | up*Move::up | down*Move::down);
		}
	};
}