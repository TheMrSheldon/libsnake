#pragma once

#include "../map.h"

namespace ls::map {
	class Empty : public Map {
	private:

	public:
		virtual ~Empty() = default;
		
		virtual void setup(const ls::State& state) {
			/* Nothing to be done here */
		}

		virtual void update(const ls::State& state) {
			/*
				We would only place food randomly.
				This is currently not simulated
			*/
		}
	};
}