#pragma once

#include "map.h"
#include "state.h"

#include <inttypes.h>
#include <vector>

namespace ls {
	/**
	 * @brief The abstract Gamemode-class should be implemented by the actual gamemodes according to
	 * their own gamerules. A gamemode may be viewed as the instance enforcing the rules by calculating
	 * the next gamestate from a previous one and determining if the game is over and who won.
	 */
	class Gamemode {
	protected:
		/**
		 * @brief The map this gamemode is played on
		 */
		const ls::map::Map &map;

	private:
		/**
		 * @brief Deleted sind gamemodes should not be copyable
		 */
		Gamemode(const Gamemode &other) = delete;
		/**
		 * @brief Deleted sind gamemodes should not be copyable
		 */
		Gamemode &operator=(const Gamemode &other) = delete;

	protected:
		/**
		 * @brief Construct a new Gamemode object
		 *
		 * @param map
		 */
		Gamemode(const ls::map::Map &map) noexcept : map(map) {}

	public:
		/**
		 * @brief Destroy the Gamemode object. Virtual since the class is virtual.
		 */
		virtual ~Gamemode() = default;

		/**
		 * @brief Checks if the game in the provided state is over.
		 *
		 * @param state The state for which to check if it is gameover.
		 * @return Wether the game in the provided state is over or not.
		 */
		virtual bool isGameOver(const State &state) const noexcept = 0;

		/**
		 * @brief Returns the flags of all snakes that have won the game.
		 * @details The returned flags may contain
		 * multiple snakes. This may indicate a tie (e.g. when both snakes win in a 1v1) but could also
		 * indicate a winning party (e.g. in Squadmode).
		 * If the game is not over #ls::SnakeFlags::None is returned.
		 *
		 * @param state The state for which to return the winners.
		 * @return Flags containing the flags that have won the game of the state.
		 */
		virtual SnakeFlags getWinner(const State &state) const noexcept = 0;

		/**
		 * @brief Steps the provided state. This means that it calculates the state of play after the
		 * provided moves (\p moves) are played. \p moves contains the moves for each snake (even the
		 * dead ones) such that the move of the snake at index i in #ls::State::getSnakes() is at index i
		 * in \p moves.
		 *
		 * @param state The state which should be stepped. The state itself will not be modified.
		 * @param turn The number of turns played in the game.
		 * @param moves The moves of each snake at the corresponding position in #ls::State::getSnakes().
		 * 	As such \p moves should have exactly the same number of arguments as #ls::State::getSnakes().
		 * @return The state after each of the moves were applied.
		 */
		virtual State stepState(const State &state, uint32_t turn, const std::vector<Move> &moves) const noexcept = 0;

		/**
		 * @brief Returns the move-flags of all the unblocked actions for the snake of the given index.
		 * @details It is not required that all the returned moves returned are not blocked. The
		 * simplest implementation of this method could simply return all moves.
		 *
		 * @param state The state for which to return the snake's actions.
		 * @param snakeIdx The snake for which to return the actions.
		 * @return The possible moves of the snake at \p snakeIdx.
		 */
		virtual Move getUnblockedActions(const State &state, std::size_t snakeIdx) const noexcept = 0;
	};
} // namespace ls