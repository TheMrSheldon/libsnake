#pragma once

#include "standard.h"
#include "../definitions.h"

namespace ls::gm {
	class SquadGamemode final : public ls::gm::StandardGamemode {
	public:
		DLLEXPORT SquadGamemode() noexcept;
		DLLEXPORT virtual ~SquadGamemode() noexcept override;
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
	};

	/**
	 * @brief The default instance of the squad gamemode
	 */
	DLLEXPORT extern SquadGamemode Squad;
}