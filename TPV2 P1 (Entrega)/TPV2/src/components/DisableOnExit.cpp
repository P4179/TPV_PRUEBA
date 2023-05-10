#include "./DisableOnExit.h"

void DisableOnExit::initComponent() {
	// se guarda la referencia al Transform de la entidad
	transform = ent_->getComponent<Transform>();
	// funciona como if(tr!=nullptr), pero produce un error si no se cumple la igualdad
	assert(transform != nullptr);
}

void DisableOnExit::update(float frameTime) {
	Vector2D pos = transform->getPos();
	float x = pos.getX();
	float y = pos.getY();
	float w = transform->getWidth();
	float h = transform->getHeight();

	if (x > sdl->width() || x + w < 0 || y > sdl->height() || y + h < 0) {
		ent_->setAlive(false);
	}
}