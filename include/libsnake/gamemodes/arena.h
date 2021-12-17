#pragma once

#include "../gamemode.h"
#include "../definitions.h"

namespace ls::gm {

	class ArenaGamemode final : public ls::Gamemode {
	public:
		DLLEXPORT ArenaGamemode() noexcept;
		DLLEXPORT bool isGameOver(const State& state) const noexcept override;
		DLLEXPORT Winner getWinner(const State& state) const noexcept override;
		DLLEXPORT State stepState(const State& state, const std::vector<Move>& moves) const noexcept override;

		DLLEXPORT Move getUnblockedActions(const State& state, std::size_t snakeIdx) const noexcept override;
	};

	DLLEXPORT extern ArenaGamemode Arena;

}