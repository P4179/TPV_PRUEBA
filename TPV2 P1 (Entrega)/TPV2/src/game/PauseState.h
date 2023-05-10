#pragma once

#include "./GameState.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/KeyToContinue.h"
#include "./GameStateMachine.h"
#include "../utils/checkML.h"

class PauseState : public GameState {
private:
	// se reanuda el juego
	static void resumeGame();

public:
	PauseState();

	virtual void init();
};