#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../game/ecs_def.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../utils/checkML.h"
#include "./Transform.h"

class Image : public ecs::Component {
private:
	// se necesita el componente transform para consultar las características físicas de la entidad
	Transform* tr_;
	Texture* tex_;

public:
	constexpr static ecs::cmpId id = ecs::_IMAGE;

	Image(Texture* tex) : tr_(nullptr), tex_(tex) { }

	virtual void initComponent();

	virtual void render();
};