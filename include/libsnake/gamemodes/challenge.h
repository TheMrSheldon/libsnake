#pragma once

#include "../definitions.h"
#include "standard.h"

namespace ls::gm {

	class ChallengeGamemode final : public ls::gm::StandardGamemode {
	public:
		DLLEXPORT ChallengeGamemode(const ls::map::Map &map) noexcept;
		DLLEXPORT virtual ~ChallengeGamemode() noexcept override;
		DLLEXPORT bool isGameOver(const State &state) const noexcept override;
		DLLEXPORT SnakeFlags getWinner(const State &state) const noexcept override;
	};
} // namespace ls::gm