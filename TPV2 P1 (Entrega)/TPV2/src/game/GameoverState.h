#pragma once

#include "./GameState.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/KeyToContinue.h"
#include "../utils/checkML.h"

class GameoverState : public GameState {
private:
	// finaliza el juego
	static void finishGame();

public:
	GameoverState();

	virtual void init();
};