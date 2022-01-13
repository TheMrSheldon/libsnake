#pragma once

#include "standard.h"
#include "../definitions.h"

namespace ls::gm {
	//FIXME: sharedElimination, sharedHealth, and sharedLength are currently not factored in when stepping the state
	
	class SquadGamemode final : public ls::gm::StandardGamemode {
	private:
		bool allowBodyCollision;
		bool sharedElimination;
		bool sharedHealth;
		bool sharedLength;
	public:
		DLLEXPORT SquadGamemode() noexcept;
		/**
		 * @brief A game in squad-mode is over iff there is at most one squad remaining.
		 * 
		 * @param state The state for which to check if it is gameover.
		 * @return true iff the provided gamestate is gameover in squad-mode. 
		 */
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
		/**
		 * @brief Returns flags indicating with which snakes this snake collides.
		 * @details The snake collision in squad-mode depends on the ruleset. If body collisions between
		 * squad-members are allowed squad-members may run into each others tails without dieing. Note however
		 * that a head-to-head collision of squad members will still count as a collision.
		 * 
		 * @param state 
		 * @param snakeIdx 
		 * @return Flags indicating with which snakes this snake collides
		 */
		DLLEXPORT SnakeFlags getCollisionMask(const State& state, std::size_t snakeIdx) const noexcept override;

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