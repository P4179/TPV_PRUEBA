#pragma once

#include "./GameState.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/Button.h"
#include "../utils/checkML.h"
#include "../game/PlayState.h"

class MainMenuState : public GameState {
private:
	// se cierra el juego
	static void quit();

	// comienza el juego, es decir, se pasa a PlayState
	static void play();

public:
	MainMenuState();

	virtual void init();
};