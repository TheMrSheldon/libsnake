#pragma once

#include "standard.h"
#include "../definitions.h"

namespace ls::gm {

	class ChallengeGamemode final : public ls::gm::StandardGamemode {
	public:
		DLLEXPORT ChallengeGamemode() noexcept;
		DLLEXPORT bool isGameOver(const State& state) const noexcept override;
		DLLEXPORT SnakeFlags getWinner(const State& state) const noexcept override;
	};

	/**
	 * @brief The default instance of the challenge gamemode
	 */
	DLLEXPORT extern ChallengeGamemode Challenge;
}