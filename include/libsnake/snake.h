#pragma once

#include "position.h"
#include "move.h"

#include "definitions.h"

#include <vector>

namespace ls {
	class Snake final {
	private:
		const std::vector<Position> body;
		const Move direction;
		const int health;

		static Move getDirection(const std::vector<Position>& body) {
			if (body.size() <= 1)
				return Move::none;
			return body[0].directionFrom(body[1]);
		}

	public:
		Snake(std::vector<Position>&& body, Move direction, int health) noexcept : body(std::move(body)), direction(direction), health(health) {
			ASSERT(this->body.size() != 0, "The body may not be empty. It must at least contain a head");
		}
		Snake(std::vector<Position>&& body, int health) noexcept : body(std::move(body)), direction(getDirection(this->body)), health(health) {
			ASSERT(this->body.size() != 0, "The body may not be empty. It must at least contain a head");
		}

		inline const bool isDead() const noexcept { return getHealth() <= 0; }
		inline const Position& getHeadPos() const noexcept { return body[0];}
		inline const std::size_t length() const noexcept { return body.size(); }

		inline const Move& getDirection() const noexcept { return direction; }
		inline const int& getHealth() const noexcept { return health; }

		inline const std::vector<Position>& getBody() const noexcept { return body; }

		inline Snake afterMove(const Move& move, bool hasEaten, bool dead) const noexcept {
			if (dead)
				return Snake(std::vector<Position>(1, Position(-1, -1)), move, 0);
			const std::size_t newLength = body.size() + hasEaten;
			std::vector<Position> newbody;
			newbody.reserve(newLength);
			newbody.emplace_back(getHeadPos().after_move(move));
			for (std::size_t i = 0; i < body.size()-1; ++i)
				newbody.emplace_back(body[i]);
			if (hasEaten)
				newbody.emplace_back(newbody[newbody.size()-1]);
			return Snake(std::move(newbody), move, hasEaten? 100 : health-1);
		}
	};
}