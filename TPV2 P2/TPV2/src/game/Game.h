#pragma once

#include <SDL.h>
#include "../sdlutils/macros.h"
#include "../utils/checkML.h"
#include "../utils/Singleton.h"
#include "../game/GameStateMachine.h"
#include "../game/MainMenuState.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

using namespace std;

const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;

class Game : public Singleton<Game> {
	friend Singleton<Game>;

private:
	SDLUtils* sdl;
	InputHandler* ih;
	bool _exit;
	GameStateMachine* stateMachine;

	// renderiza el estado actual
	void render() const;

	// refresh del input y maneja el input del estado actual
	void handleInput();

	Game();

public:
	// bucle principal del juego
	void run();

	inline void setExit(bool exit) {
		this->_exit = exit;
	}
};