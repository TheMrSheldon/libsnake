#pragma once

#include <inttypes.h>
#include <string>

#include "definitions.h"
#include "state.h"

namespace ls::map {
	/**
	 * @brief Represents a battlesnake map.
	 *
	 * A map in battlesnake is a stateless class that provides two methods: one to setup a state (e.g. place hazards and
	 * food) and one to update a map after a turn (e.g. growing hazards).
	 */
	class Map {
	public:
		virtual ~Map() = default;
		/**
		 * @brief Called once to setup an existing board
		 *
		 * @param state the board that should be set up.
		 */
		virtual void setup(ls::State &state) const = 0;
		/**
		 * @brief Called to update an existing board every turn
		 *
		 * Called to update an existing board every turn. For a map that doesn't spawn food or hazards after initial
		 * creation, this method can be a no-op! For maps that just do standard random food spawning, delegating to one of
		 * the existing maps is a good way to handle that.
		 * #ls::map::Map::update is called at the end of each turn, after snakes have moved, been eliminated, etc.
		 *
		 * @param state the board that should be updated.
		 * @param turn the turn after which update is called for the board.
		 */
		virtual void update(ls::State &state, uint32_t turn) const = 0;
	};

	DLLEXPORT Map &getMap(const std::string &name);
} // namespace ls::map