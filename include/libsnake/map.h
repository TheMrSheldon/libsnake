#pragma once

#include <string>

#include "state.h"

namespace ls::map {
	class Map {
	private:

	public:
		virtual ~Map() = default;
		virtual void setup(ls::State& state) const = 0;
		virtual void update(ls::State& state) const = 0;
	};

	Map& getMap(const std::string& name);
}