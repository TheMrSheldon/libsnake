#pragma once

#include "../map.h"

namespace ls::map {
	class ArcadeMaze : public Map {
	private:
	public:
		virtual ~ArcadeMaze() = default;

		virtual void setup(ls::State &state);

		virtual void update(ls::State &state) {
			/*
				We would only place food randomly.
				This is currently not simulated
			*/
		}
	};
} // namespace ls::map