#include "./ShowAtOpposideSide.h";

// se llama cuando se añade el componente a la entidad
void ShowAtOpposideSide::initComponent() {
	transform = ent_->getComponent<Transform>();
	assert(transform != nullptr);
}

void ShowAtOpposideSide::update(float frameTime) {
	Vector2D pos = transform->getPos();
	float x = pos.getX();
	float y = pos.getY();
	float w = transform->getWidth();
	float h = transform->getHeight();

	// derecha
	if (x > sdl->width()) {
		transform->setPos(Vector2D(0, y));
	}
	// izquierda
	else if (x + w < 0) {
		transform->setPos(Vector2D(sdl->width() - w, y));
	}
	// abajo
	else if (y > sdl->height()) {
		transform->setPos(Vector2D(x, 0));
	}
	// arriba
	else if (y + h < 0) {
		transform->setPos(Vector2D(x, sdl->height() - h));
	}
}