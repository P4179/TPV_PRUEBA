#pragma once

#include "../ecs/Component.h"
#include "../utils/checkML.h"

class Generations : public ecs::Component {
private:
	int gen;

public:
	constexpr static ecs::cmpId id = ecs::_GENERATIONS;

	Generations(int initialGen) : gen(initialGen) { }

	inline int getGen() const {
		return gen;
	}

	inline void setGen(int gen) {
		this->gen = gen;
	}
};