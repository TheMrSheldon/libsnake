#pragma once

#include "../gamemode.h"
#include "../definitions.h"

namespace ls::gm {

	class StandardGamemode : public ls::Gamemode {
	public:
		DLLEXPORT StandardGamemode() noexcept;
		DLLEXPORT bool isGameOver(const State& state) const noexcept override;
		DLLEXPORT SnakeFlags getWinner(const State& state) const noexcept override;
		DLLEXPORT State stepState(const State& state, const std::vector<Move>& moves) const noexcept override;

		DLLEXPORT Move getUnblockedActions(const State& state, std::size_t snakeIdx) const noexcept override;

		DLLEXPORT virtual SnakeFlags getCollisionMask(const State& state, std::size_t snakeIdx) const;
	};

	/**
	 * @brief The default instance of the standard gamemode
	 */
	DLLEXPORT extern StandardGamemode Standard;
}