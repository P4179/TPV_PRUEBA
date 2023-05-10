#pragma once

#include <SDL.h>
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "Manager

using namespace std;

class Game {
private:
	Manager

public:
	// constructora de game, inicializa SDL y los gameObjects
	Game() {

	}

	// destructora de game, cierra SDL y destruye los punteros a gameObjects
	~Game() {

	}

	// bucle de juego
	void run();

};