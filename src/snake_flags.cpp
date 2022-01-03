#include <libsnake/snake_flags.h>

using namespace ls;

constexpr SnakeFlags::primitive SnakeFlags::None;
constexpr SnakeFlags::primitive SnakeFlags::Player1;
constexpr SnakeFlags::primitive SnakeFlags::Player2;
constexpr SnakeFlags::primitive SnakeFlags::Player3;
constexpr SnakeFlags::primitive SnakeFlags::Player4;
constexpr SnakeFlags::primitive SnakeFlags::Player5;
constexpr SnakeFlags::primitive SnakeFlags::Player6;
constexpr SnakeFlags::primitive SnakeFlags::Player7;
constexpr SnakeFlags::primitive SnakeFlags::Player8;

namespace ls {
    std::ostream& operator<<(std::ostream& os, const ls::SnakeFlags& flags) noexcept {
        if (flags.flags == SnakeFlags::None)
            return os << "Snakes::None";
        int i = 0;
        os << "Snakes::{";
        for (unsigned i = 0; flags.flags >> i != SnakeFlags::None; ++i) {
            if ((flags.flags>>i) & 1) {
                if (i > 0)
                    os << ", ";
                os << i;
            }
        }
        return os << "}";
    }
}