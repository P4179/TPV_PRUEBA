#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../utils/checkML.h"
#include "../ecs/Manager.h"
#include "./Transform.h"
#include <cassert>

struct Follow : public ecs::Component {
private:
	Transform* transform;
	Transform* fighterTransform;

public:
	constexpr static ecs::cmpId id = ecs::_FOLLOW;

	Follow() : transform(nullptr), fighterTransform(nullptr) { }

	// MODELO GAMEOBJECTS - COMPONENTES
	virtual void initComponent();

	virtual void update(float frameTime);
};