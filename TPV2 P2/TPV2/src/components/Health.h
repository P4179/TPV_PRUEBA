#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../utils/checkML.h"
#include "../game/ecs_def.h"

struct Health : public ecs::Component {
private:
	int lifes,initLife;
	Texture* texture;

public:
	constexpr static ecs::cmpId id = ecs::_HEALTH;

	Health(int lifes = 3, Texture* texture = &SDLUtils::instance()->images().at("heart")) : lifes(lifes), texture(texture),initLife(lifes) { }

	inline Texture* getTexture() const {
		return texture;
	}

	inline int getLifes() const {
		return lifes;
	}

	// pone las vidas a 0
	inline void resetLifes() {
		lifes = 0;
	}

	inline void initLifes() {
		lifes = initLife;
	}

	// resta una vida
	inline void substractLife() {
		--lifes;
	}
};