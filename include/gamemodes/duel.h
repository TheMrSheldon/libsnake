#pragma once

#include "../gamemode.h"

namespace ls::gm {

    class DuelGamemode final : ls::Gamemode<2> {
        bool isGameover(const State& state) const noexcept;
        Winner getWinner(const State& state) const noexcept;
        State stepState(const State& state, const std::array<Move, 2>& moves) const noexcept;
    };

}