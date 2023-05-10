#pragma once

#include "./GameState.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/Health.h"
#include "../components/DeAcceleration.h"
#include "../components/ShowAtOpposideSide.h"
#include "../components/FighterCtrl.h"
#include "../components/Gun.h"
#include "../utils/checkML.h"
#include "../game/AsteroidsManager.h"
#include "../game/CollisionsManager.h"
#include "../components/KeyToContinue.h"
#include "../game/PauseState.h"

class PlayState : public GameState {
private:
	// se pausa el juego
	static void pauseGame();

public:
	PlayState();

	virtual void init();
};