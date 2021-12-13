#pragma once

#include <inttypes.h>
#include <cstddef>

namespace ls {

    constexpr static uint8_t ByIndex(std::size_t index) noexcept {
        return 1<<index;
    }

    class Winner final {
    public:
        using snakes = uint8_t;
        
        constexpr static snakes None = 0;
        constexpr static snakes Player1 = ByIndex(0);
        constexpr static snakes Player2 = ByIndex(1);
        constexpr static snakes Player3 = ByIndex(2);
        constexpr static snakes Player4 = ByIndex(3);
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
        constexpr inline bool equals(snakes snakes) {
            return snakes == winner_flags;
        }

        constexpr inline bool operator==(const snakes& other) const noexcept {
            return other == winner_flags;
        }
        constexpr inline bool operator!=(const snakes& other) const noexcept {
            return other != winner_flags;
        }
    };
}