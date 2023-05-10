#pragma once

#include "./GameState.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/KeyToContinue.h"
#include "../utils/checkML.h"

class WinState : public GameState {
private:
	// se sale del juego
	static void finishGame();

public:
	WinState();

	virtual void init();
};