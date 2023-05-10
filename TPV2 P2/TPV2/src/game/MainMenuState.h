#pragma once

#include "./GameState.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/Button.h"
#include "../utils/checkML.h"
#include "../game/PlayState.h"
#include "../game/MultiplayerState.h"
#include "../systems/RenderSystem.h"

class ButtonSystem;

class MainMenuState : public GameState {
private:
	GameCtrlSystem* gameCtrlSystem;
	RenderSystem* renderSystem;
	ButtonSystem* buttonSystem;

public:
	MainMenuState() : 
		GameState(ecs::_s_MAIN_MENU), gameCtrlSystem(nullptr), renderSystem(nullptr), buttonSystem(nullptr) { }

	virtual void onEnter();
};