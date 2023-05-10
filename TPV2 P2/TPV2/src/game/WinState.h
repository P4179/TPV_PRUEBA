#pragma once

#include "./GameState.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/KeyToContinue.h"
#include "../utils/checkML.h"
#include "../systems/GameCtrlSystem.h"

class RenderSystem;

class WinState : public GameState {
private:
	RenderSystem* renderSystem;
	GameCtrlSystem* gameCtrlSystem;

	// se sale del juego
	static void finishGame();

public:
	WinState() : GameState(ecs::_s_WIN), renderSystem(nullptr), gameCtrlSystem(nullptr) { }

	virtual void onEnter();
};