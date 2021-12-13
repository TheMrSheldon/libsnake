#pragma once

#include <inttypes.h>

#include "state.h"

namespace ls {
    template<std::size_t NSnakes>
    class Gamemode {
    private:
        Gamemode(const Gamemode& other) = delete;
        Gamemode& operator=(const Gamemode& other) = delete;
    protected:
        Gamemode() noexcept = default;
        virtual ~Gamemode() = default;
    public:
        virtual bool isGameOver(const State& state) const noexcept = 0;
        virtual Winner getWinner(const State& state) const noexcept = 0;
        virtual State stepState(const State& state, const std::array<Move, NSnakes>& moves) const noexcept = 0;
		
		virtual Move getUnblockedActions(const State& state, std::size_t snakeIdx) const noexcept = 0;
    };
}