#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../components/Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/checkML.h"
#include <cassert>

class DisableOnExit : public ecs::Component {
private:
	Transform* transform;
	SDLUtils* sdl;

public:
	constexpr static ecs::cmpId id = ecs::_DISABLE_ON_EXIT;

	DisableOnExit() : transform(nullptr), sdl(SDLUtils::instance()) { }

	virtual void initComponent();

	// si se sale de la pantalla se elimina
	virtual void update(float frameTime);
};