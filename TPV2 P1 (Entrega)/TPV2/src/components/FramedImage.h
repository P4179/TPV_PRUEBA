#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/Texture.h"
#include "../utils/checkML.h"
#include "./Transform.h"

// clase que se encarga de renderizar un spritesheet y producir una animación con él
class FramedImage : public ecs::Component {
private:
	Texture* texture;
	Transform* transform;
	float elapsedTime;
	float timer;
	int row;
	int col;

public:
	constexpr static ecs::cmpId id = ecs::_IMAGE;

	FramedImage(Texture* texture) :
		texture(texture), transform(nullptr), elapsedTime(0), timer(50), row(0), col(0) { }

	virtual void initComponent();

	// se cambia de frame cada cierto tiempo
	virtual void update(float frameTime);

	// se renderiza un frame del spritesheet
	virtual void render();
};