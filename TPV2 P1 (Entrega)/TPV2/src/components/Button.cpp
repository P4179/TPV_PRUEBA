#include "./Button.h"

bool Button::mouseIsOnRect() {
	int mouseX = ih->getMousePos().first;
	int mouseY = ih->getMousePos().second;

	SDL_Rect rect = transform->getRect();

	return mouseX > rect.x && mouseX < rect.x + rect.w &&
		mouseY > rect.y && mouseY < rect.y + rect.h;
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