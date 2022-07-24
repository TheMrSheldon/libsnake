#pragma once

#include "../map.h"

namespace ls::map {
	class ArcadeMaze : public Map {
	private:
	public:
		virtual ~ArcadeMaze() = default;

		virtual void setup(ls::State &state) const;

		virtual void update(ls::State &state) const {
			/*
				We would only place food randomly.
				This is currently not simulated
			*/
		}
	};
} // namespace ls::map