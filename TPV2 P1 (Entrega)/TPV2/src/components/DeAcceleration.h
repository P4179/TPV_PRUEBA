#pragma once

#include "../ecs/Component.h"
#include "../components/Transform.h"
#include "../ecs/Entity.h"
#include "../utils/checkML.h"
#include <cassert>

class DeAcceleration : public ecs::Component {
private:
	Transform* transform;
	float deAcceleration;
	float limit;

public:
	constexpr static ecs::cmpId id = ecs::_DE_ACCELERATION;

	DeAcceleration(float deAcceleration) : deAcceleration(deAcceleration), limit(0.05), transform(nullptr) { }

	virtual void initComponent();

	// se desacelera
	virtual void update(float frameTime);
};