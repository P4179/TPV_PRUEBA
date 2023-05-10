#pragma once

#include "../ecs/Component.h"
#include "../utils/checkML.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "./Transform.h"

struct Gun : public ecs::Component {
private:
	float timer;
	int wBullet;
	int hBullet;

public:
	constexpr static ecs::cmpId id = ecs::_GUN;

	Gun(float bulletFrequency) : timer(bulletFrequency), wBullet(5), hBullet(20) { }

	inline float getTimer() const {
		return timer;
	}

	inline float getWBullet() const {
		return wBullet;
	}

	inline float getHBullet() const {
		return hBullet;
	}
};