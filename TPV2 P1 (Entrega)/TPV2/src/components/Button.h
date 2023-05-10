#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../components/Transform.h"
#include "../ecs/Entity.h"
#include "../utils/checkML.h"

class Button : public ecs::Component {
private:
	InputHandler* ih;
	Transform* transform;
	void(*callback)();

	// comprueba si el ratón está sobre el botón
	bool mouseIsOnRect();

public:
	constexpr static ecs::cmpId id = ecs::_BUTTON;

	Button(void(*callback)()) : ih(InputHandler::instance()), callback(callback), transform(nullptr) { }

	virtual void initComponent();

	// si se clica sobre un botón se llama a callback
	virtual void handleInput();
};