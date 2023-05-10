#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/checkML.h"
#include "../components/Transform.h"
#include "../ecs/Entity.h"

class ShowAtOpposideSide : public ecs::Component {
private:
	Transform* transform;
	SDLUtils* sdl;

public:
	constexpr static ecs::cmpId id = ecs::_SHOW_AT_OPPOSIDE_SIDE;

	ShowAtOpposideSide() : transform(nullptr), sdl(SDLUtils::instance()) { }

	// se llama cuando se añade el componente a la entidad
	virtual void initComponent();

	virtual void update(float frameTime);
};