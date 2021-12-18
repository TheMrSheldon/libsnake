#pragma once

#include "state.h"

#include <inttypes.h>
#include <vector>

namespace ls {
	class Gamemode {
	private:
		Gamemode(const Gamemode& other) = delete;
		Gamemode& operator=(const Gamemode& other) = delete;
	protected:
		Gamemode() noexcept = default;
		virtual ~Gamemode() = default;
	public:
		virtual bool isGameOver(const State& state) const noexcept = 0;
		virtual SnakeFlags getWinner(const State& state) const noexcept = 0;
		virtual State stepState(const State& state, const std::vector<Move>& moves) const noexcept = 0;
		
		virtual Move getUnblockedActions(const State& state, std::size_t snakeIdx) const noexcept = 0;
	};
}