#pragma once

#include "../ecs/Component.h"
#include "../game/AsteroidsManager.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../ecs/Entity.h"
#include "../utils/checkML.h"
#include "../game/GameStateMachine.h"
#include "../game/WinState.h"
#include "../game/GameoverState.h"

class CollisionsManager : public ecs::Component {
private:
	AsteroidsManager* asteroidsManager;
	Transform* fighterTransform;
	Health* fighterHealth;
	SDLUtils* sdl;
	SoundEffect* explosionSound;
	SoundEffect* hitSound;
	GameStateMachine* stateMachine;

	// determina si dos entidades a partir de sus SDL_Rect han colisionado
	bool hasCollided(const SDL_Rect& rect1, const SDL_Rect& rect2);

	void deactivateBullets();

	bool collisionAsteroidFighter(ecs::Entity* asteroid);

	bool collisionAsteroidBullet(ecs::Entity* asteroid);

	// comprueba colisiones de los asteroides con el caza y las balas
	void checkCollision();

public:
	constexpr static ecs::cmpId id = ecs::_COLLISIONS_MANAGER;

	CollisionsManager();

	// inicia asteroidsManager y el transform y el health del fighter
	virtual void initComponent();

	virtual void update(float frameTime);
};