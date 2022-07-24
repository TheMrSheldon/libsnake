#pragma once

#include "../map.h"

namespace ls::map {
	class Standard : public Map {
	private:

	public:
		virtual ~Standard() = default;
		
		virtual void setup(ls::State& state) {
			/* Nothing to be done here */
		}

		virtual void update(ls::State& state) {
			/*
				We would only place food randomly.
				This is currently not simulated
			*/
		}
	};
}