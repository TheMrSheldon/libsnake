#pragma once

#include "../map.h"

namespace ls::map {
	class ArcadeMaze : public Map {
	private:
	public:
		virtual ~ArcadeMaze() = default;

		DLLEXPORT virtual void setup(ls::State &state) const;

		virtual void update(ls::State &state, uint32_t turn) const {
			/*
				We would only place food randomly.
				This is currently not simulated
			*/
		}
	};
} // namespace ls::map