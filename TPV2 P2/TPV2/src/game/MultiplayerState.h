#pragma once
#include <string>

#include "./GameState.h"
#include "../game/PauseState.h"
#include "../systems/CollisionsSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/OnlineSystem.h"
#include "../systems/OnlineFighterSystem.h"
#include "../systems/FighterSystem.h"

class MultiplayerState : public GameState
{
private:
	bool server;
	std::string ip;
	string name;

	BulletSystem* bulletsSystem;
	CollisionsSystem* collisionsSystem;
	FighterSystem* fighterSystem;
	OnlineFighterSystem* onlinefighterSystem;
	GameCtrlSystem* gameCtrlSystem;
	RenderSystem* renderSystem;
	OnlineSystem* onlineSystem;

	static void pauseGame();
public:
	MultiplayerState() :
		server(false), ip(""), name(""), GameState(ecs::_s_MULTIPLAYER), bulletsSystem(nullptr), collisionsSystem(nullptr),
		fighterSystem(nullptr), onlinefighterSystem(nullptr), gameCtrlSystem(nullptr), renderSystem(nullptr), onlineSystem(nullptr) { }

	MultiplayerState(bool s, string name) :
		server(s), ip("177.00.222"), name(name), GameState(ecs::_s_MULTIPLAYER), bulletsSystem(nullptr), collisionsSystem(nullptr),
		fighterSystem(nullptr), onlinefighterSystem(nullptr), gameCtrlSystem(nullptr), renderSystem(nullptr), onlineSystem(nullptr) { }

	virtual void onEnter();
};
