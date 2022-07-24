#pragma once

#include "../map.h"

namespace ls::map {
	class Empty : public Map {
	private:

	public:
		virtual ~Empty() = default;
		
		virtual void setup(ls::State& state) const {
			/* Nothing to be done here */
		}

		virtual void update(ls::State& state, uint32_t turn) const {
			/*
				We would only place food randomly.
				This is currently not simulated
			*/
		}
	};
}