#pragma once

#include "./GameState.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/KeyToContinue.h"
#include "../utils/checkML.h"

class GameCtrlSystem;
class RenderSystem;

class GameoverState : public GameState {
private:
	GameCtrlSystem* gameCtrlSystem;
	RenderSystem* renderSystem;

	// finaliza el juego
	static void finishGame();

public:
	GameoverState() : GameState(ecs::_s_GAMEOVER), gameCtrlSystem(nullptr), renderSystem(nullptr) { }
	virtual void onEnter();
};