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
		bool wrappedBoard = false;
	public:
		DLLEXPORT StandardGamemode() noexcept;
		DLLEXPORT virtual ~StandardGamemode() noexcept;
		DLLEXPORT bool isGameOver(const State& state) const noexcept override;
		/**
		 * @brief Returns the winner of the match.
		 * @details Returns the winner of the match. If the game is not over (two or more squads alive)
		 * SnakeFlags::None is returned. If the game is a tie (all squads eliminated) all snakes are winners.
		 * If a single squad is left alive, the snakes in this squad are the winners. It may be that one snake
		 * from the squad has died and thus is the winner without being alive to see the day.
		 * 
		 * @param state The state for which to determine the winner.
		 * @return The winner of the match. 
		 */
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
		void setWrappedBoard(bool value) noexcept { this->wrappedBoard = value; }
		bool isBoardWrapped() const noexcept { return this->wrappedBoard; }
	};

	/**
	 * @brief The default instance of the standard gamemode
	 */
	DLLEXPORT extern StandardGamemode Standard;
}