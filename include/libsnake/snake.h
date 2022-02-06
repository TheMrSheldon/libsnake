#pragma once

#include "move.h"
#include "position.h"
#include "snake_flags.h"

#include "definitions.h"

#include <vector>

namespace ls {
	/**
	 * @brief Represents a snake object.
	 */
	class Snake final {
	private:
		/**
		 * @brief The position of the snakes body elements. The list is ordered such that the head is always at index 0
		 * and the last element of the tail is always the last element in the body.
		 * @details The tail should always contain one or more elements.
		 * 
		 * @see Snake::getBody()
		 */
		const std::vector<Position> body;
		/**
		 * @brief The direction the snake last moved in.
		 * 
		 * @see Snake::getDirection()
		 */
		const Move direction;
		/**
		 * @brief The health of this snake.
		 * 
		 * @see Snake::getHealth()
		 */
		const int health;

		/**
		 * @brief The squad this snake belongs to. The squad-identifier actually is a set of flags
		 * representing the indices of the snakes that are in the same squad. A snake that is not playing
		 * in a squad should that have only the flag set that corresponds to its own index.
		 * 
		 * @see Snake::getSquad()
		 */
		const SnakeFlags squad;

		/**
		 * @brief Calculates the direction of a snake based on its body.
		 * @details If the snake only has a head (its length is &#8804; 1) Move::none is returned. Otherwise the direction
		 * from its second body element (the one after the head) to its head is returned.
		 * 
		 * @see Position::directionFrom(Position)
		 * @param body The snakes body for which to calculate the direction.
		 * @return The direction the snake last moved in.
		 */
		inline static Move getDirection(const std::vector<Position>& body) {
			if (body.size() <= 1)
				return Move::none;
			return body[0].directionFrom(body[1]);
		}

	public:
		/**
		 * @brief Constructs a new Snake object given the provided body, direction and health. The direction may not coincide with the direction
		 * from the second element in the body to the head.
		 * @details Note that the data from \p body is moved into the snake's own body-vector and thus \p body is modified.
		 * 
		 * @param body The new snake's body.
		 * @param direction The new snake's direction. This may not be the same as the direction from the second element of the body to the head.
		 * @param health The new snake's health.
		 * @param squad The snake's squad. If the snake should not be part of a squad set it to ls::SnakeFlags::FromIndex with the index of the snake.
		 */
		Snake(std::vector<Position>&& body, Move direction, int health, SnakeFlags squad) noexcept : body(std::move(body)), direction(direction), health(health), squad(squad) {
			ASSERT(this->body.size() != 0, "The body may not be empty. It must at least contain a head");
		}
		/**
		 * @brief Constructs a new Snake object given the provided body and health. The snakes direction is inferred from its body.
		 * @details Note that the data from \p body is moved into the snake's own body-vector and thus \p body is modified.
		 * 
		 * @param body The new snake's body.
		 * @param health The new snake's health.
		 * @param squad The snake's squad. If the snake should not be part of a squad set it to ls::SnakeFlags::FromIndex with the index of the snake.
		 */
		Snake(std::vector<Position>&& body, int health, SnakeFlags squad) noexcept : Snake(std::move(body), getDirection(body), health, squad) {}

		/**
		 * @brief Checks if this snake is dead. The snake is considered dead iff its health is 0.
		 * 
		 * @see Snake::getHealth()
		 * @return true iff the snake is dead.
		 */
		inline const bool isDead() const noexcept { return getHealth() <= 0; }
		/**
		 * @brief Returns the position of this snake's head.
		 * 
		 * @return The position of this snake's head.
		 */
		inline const Position& getHeadPos() const noexcept { return body[0];}
		/**
		 * @brief Returns the length of this snake. That is the length of its body.
		 * 
		 * @see Snake::getBody()
		 * @return The length of this snake. 
		 */
		inline const std::size_t length() const noexcept { return body.size(); }

		/**
		 * @brief Returns the direction of this snake. That is the last movement the snake has performed.
		 * It is Move::none if the snake has not moved previously.
		 * 
		 * @return The direction of the snake.
		 */
		inline const Move& getDirection() const noexcept { return direction; }
		/**
		 * @brief Returns the health of this snake.
		 * 
		 * @return The health of this snake.
		 */
		inline const int& getHealth() const noexcept { return health; }
		/**
		 * @brief Returns this snake's body. That is the Positions at which each element of the snake's
		 * tail is located. The list is ordered according to the element's occurence in the snake's body.
		 * The head is at index 0 and the last element of the tail is at the last index of the body.
		 * 
		 * @return This snake's body.
		 */
		inline const std::vector<Position>& getBody() const noexcept { return body; }
		/**
		 * @brief Returns an identfiier that represents the snake's squad. The identifier actually is a set of flags
		 * representing the indices of the snakes that are in the same team. A snake that is not playing
		 * in a squad should that have only the flag set that corresponds to its own index.
		 * 
		 * @return An identifier representing the snake's squad.
		 */
		inline const SnakeFlags& getSquad() const noexcept { return squad; }

		/**
		 * @brief Constructs a new snake with the updated body, health and direction given the move and wether
		 * the snake has eaten or died.
		 * @details If the snake died, a snake with 0 health and its head at the coordinates (-1,-1) is returned.
		 * Otherwise the snakes body is updated by moving into the direction provided by \p move. If the snake has
		 * eaten the returned snake has 100 health (max health) and is longer by one element.
		 * 
		 * @param move The direction the snake moves in.
		 * @param head The new position of the head.
		 * @param hasEaten True iff the snake has eaten while moving in the direction of \p move.
		 * @param dead True iff the snake has died while moving in the direction of \p move.
		 * @param healthDelta The difference to the snakes health in the next turn. Ignored if \p hasEaten is set to true.
		 * @return The next snake-state after this snake was moved in direction \p move.
		 */
		inline Snake afterMove(const Move& move, Position head, bool hasEaten, bool dead, int healthDelta) const noexcept {
			if (dead)
				return Snake(std::vector<Position>(1, Position(-1, -1)), move, 0, squad);
			const std::size_t newLength = body.size() + hasEaten;
			std::vector<Position> newbody;
			newbody.reserve(newLength);
			newbody.emplace_back(head);
			for (std::size_t i = 0; i < body.size()-1; ++i)
				newbody.emplace_back(body[i]);
			if (hasEaten)
				newbody.emplace_back(newbody[newbody.size()-1]);
			return Snake(std::move(newbody), move, hasEaten? 100 : (health+healthDelta), squad);
		}
	};
}