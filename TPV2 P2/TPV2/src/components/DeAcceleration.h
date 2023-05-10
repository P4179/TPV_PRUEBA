#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../utils/checkML.h"
#include <cassert>

struct DeAcceleration : public ecs::Component {
private:
	SDLUtils* sdl;
	float deAcceleration;
	float limit;

public:
	constexpr static ecs::cmpId id = ecs::_DE_ACCELERATION;

	DeAcceleration() : sdl(SDLUtils::instance()), deAcceleration(sdl->consts().at("FIGHTER_DEACCELERATION")), limit(sdl->consts().at("FIGHTER_LIMIT")) { }

	inline float getDeceleration() const {
		return deAcceleration;
	}

	inline float getLimit() const {
		return limit;
	}
};