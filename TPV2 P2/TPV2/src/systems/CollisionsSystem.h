#pragma once
#include "../ecs/System.h"
#include "../components/Transform.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../utils/checkML.h"

// solo en playstate
class CollisionsSystem : public ecs::System {
private:
	Transform* fighterTransform;
	SDLUtils* sdl;
	SoundEffect* explosionSound;
	SoundEffect* hitSound;

	bool hasCollided(const SDL_Rect& rect1, const SDL_Rect& rect2);

	bool collisionAsteroidFighter(ecs::Entity* asteroid);

	// comprobar si un asteriode ha chocado con alguna de las balas que hay en el juego
	bool collisionAsteroidBullet(ecs::Entity* asteroid);

	bool collisionBulletFighter();

	void fighterBulletProcessCollision();

public:
	constexpr static ecs::sysId id = ecs::_sys_COLLISIONS;

	CollisionsSystem() : fighterTransform(nullptr) {
		sdl = SDLUtils::instance();
		explosionSound = &sdl->soundEffects().at("explosion");
		hitSound = &sdl->soundEffects().at("hit");
	}

	// Inicializar el sistema, etc.
	virtual void initSystem();

	// si el juego está parado no hacer nada, en otro caso comprobar colisiones como
	// en la práctica 1 y enviar mensajes correspondientes.
	virtual void update(float frameTime);
};