#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../components/Transform.h"
#include "../ecs/Entity.h"
#include "../utils/checkML.h"
#include "../sdlutils/SDLUtils.h"

struct FighterCtrl : public ecs::Component {
private:
	SoundEffect* thrustSound;
	float thrust;
	float speedLimit;

public:
	constexpr static ecs::cmpId id = ecs::_CTRL;

	FighterCtrl(float thrust, float speedLimit)
		: thrust(thrust), speedLimit(speedLimit) {

		// se coge el sonido del map donde se han cargado todos los sonidos previamente
		thrustSound = &SDLUtils::instance()->soundEffects().at("thrust");
	}

	inline float getThrust() const {
		return thrust;
	}

	inline float getSpeedLimit() const {
		return speedLimit;
	}

	inline SoundEffect* getThrustSound() const {
		return thrustSound;
	}
};