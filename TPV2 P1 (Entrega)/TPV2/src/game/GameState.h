#pragma once

#include "../ecs/Manager.h"
#include "../utils/checkML.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

// Clase abstracta
class GameState {
protected:
	ecs::Manager* manager_;
	SDLUtils* sdl;
	InputHandler* ih;
	// indica si el estado est� vivo o no para eliminarlo al hacer refresh en la m�quina de estados
	bool alive;

	GameState();
	
public:
	virtual ~GameState() {
		delete manager_;
	}

	// m�todo virtual puro
	// se crean las entidades del estado
	virtual void init() = 0;

	// no son virtuales porque no hay ning�n hijo que los redefina
	// update del manager
	void update(float frameTime);

	// render del manager
	void render();

	// handleInput del manager
	void handleInput();

	// refres del manager
	void refresh();

	inline void setAlive(bool alive) {
		this->alive = alive;
	}

	inline bool getAlive() {
		return alive;
	}
};