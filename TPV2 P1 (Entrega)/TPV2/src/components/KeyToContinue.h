#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../game/ecs_def.h"
#include "../utils/checkML.h"

class KeyToContinue : public ecs::Component {
private:
	SDL_Keycode key;
	void (*callback)();
	InputHandler* ih;

public:
	constexpr static ecs::cmpId id = ecs::_BUTTON;

	KeyToContinue(SDL_Keycode key, void(*callback)()) 
		: key(key), callback(callback), ih(InputHandler::instance()) { }

	// si se pulsa la tecla key se ejecuta el método callback
	virtual void handleInput();
};