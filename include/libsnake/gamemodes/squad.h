#pragma once

#include "../definitions.h"
#include "standard.h"

namespace ls::gm {
	class SquadGamemode final : public ls::gm::StandardGamemode {
	private:
		bool allowBodyCollision = false;

	public:
		DLLEXPORT SquadGamemode(const ls::map::Map &map) noexcept;
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
		DLLEXPORT SnakeFlags getCollisionMask(const State &state, std::size_t snakeIdx) const noexcept override;

		/**
		 * @brief Modifies the gamerule to allow body collision
		 *
		 * Settings this to true allows members of the same squad to move over each other without dying.
		 *
		 * @param value the new value for the allowBodyCollisions gamerule.
		 * @see SquadGamemode::getAllowBodyCollisions
		 */
		void setAllowBodyCollisions(bool value) noexcept { this->allowBodyCollision = value; }
		bool getAllowBodyCollisions() const noexcept { return this->allowBodyCollision; }
	};
} // namespace ls::gm