#pragma once

#include "../gamemode.h"
#include "../definitions.h"

namespace ls::gm {

	class ChallengeGamemode final : public ls::Gamemode {
	public:
		DLLEXPORT ChallengeGamemode() noexcept;
		DLLEXPORT bool isGameOver(const State& state) const noexcept override;
		DLLEXPORT SnakeFlags getWinner(const State& state) const noexcept override;
		DLLEXPORT State stepState(const State& state, const std::vector<Move>& moves) const noexcept override;

		DLLEXPORT Move getUnblockedActions(const State& state, std::size_t snakeIdx) const noexcept override;
	};

	/**
	 * @brief The default instance of the challenge gamemode
	 */
	DLLEXPORT extern ChallengeGamemode Challenge;
}