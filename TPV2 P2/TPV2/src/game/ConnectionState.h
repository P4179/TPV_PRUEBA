#pragma once
#include "./GameState.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/Button.h"
#include "../utils/checkML.h"
#include "../game/PlayState.h"
#include "../game/MultiplayerState.h"
#include "../systems/RenderSystem.h"
#include "../systems/OnlineButtonSystem.h"

class ButtonSystem;

class ConnectionState : public GameState
{
private:
	GameCtrlSystem* gameCtrlSystem;
	RenderSystem* renderSystem;
	OnlineButtonSystem* onlineButtonSystem;

public:
	ConnectionState() :
		GameState(ecs::_s_CONNECT), gameCtrlSystem(nullptr), renderSystem(nullptr), onlineButtonSystem(nullptr) { }

	virtual void onEnter();
};

