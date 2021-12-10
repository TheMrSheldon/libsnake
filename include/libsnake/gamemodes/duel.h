#pragma once

#include "../gamemode.h"

#include "../definitions.h"

namespace ls::gm {

    class DuelGamemode final : public ls::Gamemode<2> {
    public:
        DLLEXPORT bool isGameOver(const State& state) const noexcept override;
        DLLEXPORT Winner getWinner(const State& state) const noexcept override;
        DLLEXPORT State stepState(const State& state, const std::array<Move, 2>& moves) const noexcept override;
    };

    extern DuelGamemode Duel;
}