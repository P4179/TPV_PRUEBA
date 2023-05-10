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
#include "../systems/AsteroidsSystem.h"
#include "../systems/BulletSystem.h"
#include "../systems/CollisionsSystem.h"
#include "../systems/FighterSystem.h"
#include "../systems/GameCtrlSystem.h"

class RenderSystem;

class PlayState : public GameState {
private:
	AsteroidsSystem* asteroidsSystem;
	BulletSystem* bulletsSystem;
	CollisionsSystem* collisionsSystem;
	FighterSystem* fighterSystem;
	GameCtrlSystem* gameCtrlSystem;
	RenderSystem* renderSystem;

public:
	PlayState() : 
		GameState(ecs::_s_PLAY), asteroidsSystem(nullptr), bulletsSystem(nullptr), collisionsSystem(nullptr),
		fighterSystem(nullptr), gameCtrlSystem(nullptr), renderSystem(nullptr) { }

	virtual void onEnter();
};