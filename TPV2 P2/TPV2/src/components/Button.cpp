#include "./Button.h"

bool Button::mouseIsOnRect() {
	Vector2D mousePos = Vector2D(ih->getMousePos().first, ih->getMousePos().second);

	SDL_Rect rect = transform->getRect();

	return mousePos.getX() > rect.x && mousePos.getX() < rect.x + rect.w &&
		mousePos.getY() > rect.y && mousePos.getY() < rect.y + rect.h;
}

void Button::initComponent() {
	transform = ent_->getComponent<Transform>();
	// funciona como if(tr!=nullptr), pero produce un error si no se cumple la igualdad
	assert(transform != nullptr);
}

void Button::handleInput() {
	if (ih->getMouseButtonState(InputHandler::LEFT) && mouseIsOnRect()) {
		callback();
	}
}