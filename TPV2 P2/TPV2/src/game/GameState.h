#pragma once

#include "../ecs/Manager.h"
#include "../utils/checkML.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "ecs_def.h"
#include <list>

// Clase abstracta
class GameState {
protected:
	const ecs::stateId id;
	ecs::gameStateId gId;

	ecs::Manager* manager_;
	SDLUtils* sdl;
	InputHandler* ih;
	// indica si el estado está vivo o no para eliminarlo al hacer refresh en la máquina de estados
	bool alive;
	list<ecs::System*> stateSystems;

	GameState(ecs::stateId id);

public:
	virtual ~GameState() {
		stateSystems.clear();
		delete manager_;
	}

	// método virtual puro
	// se llama justo después de que se haya creado el estado
	virtual void onEnter() = 0;

	// update del manager
	virtual void update(float frameTime);

	// refresh del manager
	void refresh();

	// se envían los mensajes que se habían enviado anteriormente con delay
	void flushMessages();

	inline void setAlive(bool alive) {
		this->alive = alive;
	}

	inline bool getAlive() {
		return alive;
	}

	inline ecs::stateId getStateID() const {
		return id;
	}

	inline ecs::gameStateId getGameStateID() const {
		return gId;
	}

	inline void setGameStateID(ecs::gameStateId gsid) {
		gId = gsid;
	}

	inline void addSystem(ecs::System* sys) {
		stateSystems.push_back(sys);
	}
};