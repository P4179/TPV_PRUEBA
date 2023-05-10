#pragma once
#include "../ecs/Entity.h"
#include "../ecs/System.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/checkML.h"
#include "../game/GameStateMachine.h"

class OnlineCollisionsSystem : public ecs::System
{
private:
	GameState* currentState;

	Transform* fighterTransform;
	Transform* fighter2Transform;
	SDLUtils* sdl;
	SoundEffect* hitSound;

	bool hasCollided(const SDL_Rect& rect1, const SDL_Rect& rect2);

	void collisionBulletFighter();
	void collisionBulletFighter2();

public:
	constexpr static ecs::sysId id = ecs::_sys_ONLINE_COLLISIONS;

	OnlineCollisionsSystem() : fighterTransform(nullptr), fighter2Transform(nullptr) {
		sdl = SDLUtils::instance();
		currentState = GameStateMachine::instance()->currentState();
		hitSound = &sdl->soundEffects().at("hit");
	}

	// Inicializar el sistema, etc.
	virtual void initSystem();

	// si el juego está parado no hacer nada, en otro caso comprobar colisiones como
	// en la práctica 1 y enviar mensajes correspondientes.
	virtual void update(float frameTime);
};

