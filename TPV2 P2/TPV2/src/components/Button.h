#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../components/Transform.h"
#include "../ecs/Entity.h"
#include "../utils/checkML.h"
#include "../sdlutils/Texture.h"

// Ambos son lo mismo, sirve para dar
// using Callback = void(*)();
typedef void(*Callback)();

class Button : public ecs::Component {
public:
	enum State
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};

private:
	// MODELO GAMEOBJECTS - COMPONENTS
	InputHandler* ih;
	Transform* transform;

	Callback callback;
	State currentState;
	array<Texture*, 3> textures;
	// se utiliza para que haya que dejar de pulsar al bot�n
	// para que se pueda volver a utilizar el rat�n
	bool released;

	// comprueba si el rat�n est� sobre el bot�n
	bool mouseIsOnRect();

public:
	constexpr static ecs::cmpId id = ecs::_BUTTON;

	Button(Callback callback, array<Texture*, 3> textures) :
		callback(callback), textures(textures), currentState(MOUSE_OUT), released(true) {
		// MODELO GAMEOBJECTS - COMPONENTES
		ih = InputHandler::instance();
		transform = nullptr;
	}

	inline Callback getCallback() const {
		return callback;
	}

	inline void setState(State newState) {
		currentState = newState;
	}

	inline Texture* getCurrentTexture() const {
		return textures[currentState];
	}

	inline bool getReleased() const {
		return released;
	}

	inline void setReleased(bool released) {
		this->released = released;
	}

	// MODELO GAMEOBJECTS - COMPONENTES
	virtual void initComponent();

	// si se clica sobre un bot�n se llama a callback
	virtual void handleInput();
};