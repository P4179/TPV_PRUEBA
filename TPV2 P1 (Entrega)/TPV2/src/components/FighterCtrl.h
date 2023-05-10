#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../components/Transform.h"
#include "../ecs/Entity.h"
#include "../utils/checkML.h"
#include "../sdlutils/SDLUtils.h"

class FighterCtrl : public ecs::Component {
private:
	InputHandler* ih;
	Transform* transform;
	SDLUtils* sdl;
	SoundEffect* thrustSound;
	float thrust;
	float speedLimit;

public:
	constexpr static ecs::cmpId id = ecs::_CTRL;

	FighterCtrl(float thrust, float speedLimit);

	virtual void initComponent();

	// gira o acelera el caza
	virtual void handleInput();
};