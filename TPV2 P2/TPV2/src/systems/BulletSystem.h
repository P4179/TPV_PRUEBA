#pragma once

#include "../ecs/System.h"
#include "../components/Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/checkML.h"
#include "../ecs/Manager.h"

// solo en playstate
class BulletSystem : public ecs::System {
private:
	SDLUtils* sdl;
	Transform* fighterTransform;
	SoundEffect* fireSound;

	// para gestionar el mensaje de que el jugador ha disparado
	// añadir una bala al juego, como en la práctica 1
	void shoot(Vector2D pos, Vector2D vel, double width, double height);

	// para gestionar el mensaje de que ha habido un choque entre una bala y un
	// asteroide. Desactivar la bala “b?
	void onCollision_BulletAsteroid(ecs::Entity* b);

	// para gestionar el mensaje de que ha acabado la ronda
	// desactivar todas las balas
	void onRoundOver();

	// mover una bala
	void movement(ecs::Entity* bullet, float frameTime);

	// hacer que la bala desapezca si se ha salido de la pantalla
	void disableOnExit(ecs::Entity* bullet);

public:
	constexpr static ecs::sysId id = ecs::_sys_BULLET;

	BulletSystem() : sdl(SDLUtils::instance()), fighterTransform(nullptr) {
		fireSound = &SDLUtils::instance()->soundEffects().at("fire");
	}

	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	virtual void receive(const ecs::Message& m);

	// Inicializar el sistema, etc.
	virtual void initSystem();

	// Si el juego est?parado no hacer nada, en otro caso mover las balas y
	// desactivar las que salen de la ventana como en la práctica 1.
	void update(float frameTime);
};