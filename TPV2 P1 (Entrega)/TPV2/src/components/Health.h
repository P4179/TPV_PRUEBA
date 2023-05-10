#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../utils/checkML.h"
#include "../game/ecs_def.h"

class Health : public ecs::Component {
private:
	int lifes;
	Texture* texture;

public:
	constexpr static ecs::cmpId id = ecs::_HEALTH;

	Health(int lifes, Texture* texture) : lifes(lifes), texture(texture) { }

	inline int getLifes() const {
		return lifes;
	}

	// pone las vidas a 0
	inline void resetLifes() {
		lifes = 0;
	}

	// resta una vida
	inline void substractLife() {
		--lifes;
	}

	virtual void render();

};