#pragma once

#include <inttypes.h>

#include "state.h"

namespace ls {
    template<std::size_t NSnakes>
    class Gamemode {
    private:
        Gamemode(const Gamemode& other) = delete;
        Gamemode& operator=(const Gamemode& other) = delete;
    public:
        virtual bool isGameOver(const State& state) const noexcept;
        virtual Winner getWinner(const State& state) const noexcept;
        virtual State stepState(const State& state, const std::array<Move, NSnakes>& moves) const noexcept;
    };
}