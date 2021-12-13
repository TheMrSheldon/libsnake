#pragma once

#include "move.h"

namespace ls {
    struct Position final {
        unsigned x, y;

        inline Position(unsigned x = 0, unsigned y = 0) noexcept : x(x), y(y) {}

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

        inline Move directionFrom(const Position& from) const noexcept {
            return ls::Move::getDirection(from.x, from.y, x, y);
        }
    };
}