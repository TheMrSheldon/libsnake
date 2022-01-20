#pragma once

#include "../gamemode.h"
#include "../definitions.h"

namespace ls::gm {

	class StandardGamemode : public ls::Gamemode {
	private:
		bool allowBodyCollision = false;
		bool sharedElimination = false;
		bool sharedHealth = false;
		bool sharedLength = false;
	public:
		DLLEXPORT StandardGamemode() noexcept;
		DLLEXPORT bool isGameOver(const State& state) const noexcept override;
		DLLEXPORT SnakeFlags getWinner(const State& state) const noexcept override;
		DLLEXPORT State stepState(const State& state, const std::vector<Move>& moves) const noexcept override;

		DLLEXPORT Move getUnblockedActions(const State& state, std::size_t snakeIdx) const noexcept override;

		DLLEXPORT virtual SnakeFlags getCollisionMask(const State& state, std::size_t snakeIdx) const;

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
	 * @brief The default instance of the standard gamemode
	 */
	DLLEXPORT extern StandardGamemode Standard;
}