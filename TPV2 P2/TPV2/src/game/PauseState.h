#pragma once

#include "./GameState.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/KeyToContinue.h"
#include "./GameStateMachine.h"
#include "../utils/checkML.h"

class GameCtrlSystem;
class RenderSystem;

class PauseState : public GameState {
private:
	GameCtrlSystem* gameCtrlSystem;
	RenderSystem* renderSystem;
	ecs::Entity* fighterPlay;

public:
	// Necesario un constructor predeterminado
	PauseState() : GameState(ecs::_s_PAUSE), gameCtrlSystem(nullptr), renderSystem(nullptr), fighterPlay(nullptr) { }

	PauseState(ecs::Entity* fighter) : 
		GameState(ecs::_s_PAUSE), gameCtrlSystem(nullptr), renderSystem(nullptr), fighterPlay(fighter) { }

	virtual void onEnter();
};