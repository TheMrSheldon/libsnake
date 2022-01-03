#pragma once

#include "../gamemode.h"
#include "../definitions.h"

namespace ls::gm {

	class SquadGamemode final : public ls::Gamemode {
	public:
		DLLEXPORT SquadGamemode() noexcept;
		DLLEXPORT bool isGameOver(const State& state) const noexcept override;
		DLLEXPORT SnakeFlags getWinner(const State& state) const noexcept override;
		DLLEXPORT State stepState(const State& state, const std::vector<Move>& moves) const noexcept override;

		DLLEXPORT Move getUnblockedActions(const State& state, std::size_t snakeIdx) const noexcept override;
	};

	/**
	 * @brief The default instance of the squad gamemode
	 */
	DLLEXPORT extern SquadGamemode Squad;
}