#pragma once

#include "../gamemode.h"
#include "../definitions.h"

namespace ls::gm {

	class SquadGamemode final : public ls::Gamemode {
	private:
		bool allowBodyCollision;
		bool sharedElimination;
		bool sharedHealth;
		bool sharedLength;
	public:
		DLLEXPORT SquadGamemode() noexcept;
		DLLEXPORT bool isGameOver(const State& state) const noexcept override;
		DLLEXPORT SnakeFlags getWinner(const State& state) const noexcept override;
		DLLEXPORT State stepState(const State& state, const std::vector<Move>& moves) const noexcept override;

		DLLEXPORT Move getUnblockedActions(const State& state, std::size_t snakeIdx) const noexcept override;

		void setAllowBodyCollisions(bool value) noexcept { this->allowBodyCollision = value; }
		bool getAllowBodyCollisions() const noexcept { return this->allowBodyCollision; }
		void setSharedElimination(bool value) noexcept { this->sharedElimination = value; }
		bool getSharedElimination() const noexcept { return this->sharedElimination; }
		void setSharedHealth(bool value) noexcept { this->sharedHealth = value; }
		bool getSharedHealth() const noexcept { return this->sharedHealth; }
		void setSharedLength(bool value) noexcept { this->sharedLength = value; }
		bool getSharedLength() const noexcept { return this->sharedLength; }
	};

	/**
	 * @brief The default instance of the squad gamemode
	 */
	DLLEXPORT extern SquadGamemode Squad;
}