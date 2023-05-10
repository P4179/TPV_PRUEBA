#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../game/ecs_def.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../utils/checkML.h"
#include "./Transform.h"

struct Image : public ecs::Component {
private:
	Texture* tex_;

public:
	constexpr static ecs::cmpId id = ecs::_IMAGE;

	Image(Texture* tex) : tex_(tex) { }

	inline Texture* getTexture() const {
		return tex_;
	}
};