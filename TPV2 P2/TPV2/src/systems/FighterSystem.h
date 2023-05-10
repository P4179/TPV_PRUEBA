#pragma once

#include "../ecs/System.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../components/DeAcceleration.h"
#include "../components/Image.h"
#include "../components/Health.h"
#include "../components/FighterCtrl.h"
#include "../components/Gun.h"
#include "../components/ShowAtOpposideSide.h"
#include "../utils/checkML.h"

// solo en playstate
class FighterSystem : public ecs::System {
private:
	SDLUtils* sdl;
	InputHandler* ih;
	ecs::Entity* fighter;
	Transform* transform;
	DeAcceleration* deAcceleration;
	FighterCtrl* fighterCtrl;
	Gun* gun;
	float elapsedTime;
	SoundEffect* fireSound;

	bool server;
	const Uint8 timer;
	bool switched;

	const float offset;

	// para reaccionar al mensaje de que ha habido un choque entre el fighter y un asteroide
	// poner el caza en el centro con velocidad (0,0) y rotación 0
	// no hace falta desactivar la entidad (no dibujarla si el juego est?parado).
	void onCollision_FighterAsteroid();

	void restartFighters();

	// posición de bala, calculada a partir de la del padre
	Vector2D posBullet();

	// velocidad de la bala, calculada a partir de la del padre
	Vector2D velBullet();

	// mover el caza
	void movement(float frameTime);

	// desacelerar el caza
	void decelerate();

	// input de la nave
	void fighterInput(float frameTime);

	// mostrar la nave al otro lado en caso de que se salga de la pantalla
	void showAtOpposideSide();

	void setFighterSide();

public:
	constexpr static ecs::sysId id = ecs::_sys_FIGHTER;

	FighterSystem() : fighter(nullptr), transform(nullptr), deAcceleration(nullptr), fighterCtrl(nullptr), gun(nullptr), elapsedTime(0), 
		server(false), offset(50.0f), timer(10), switched(false) {
		sdl = SDLUtils::instance();
		ih = InputHandler::instance();
		fireSound = &SDLUtils::instance()->soundEffects().at("fire");
	}

	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	virtual void receive(const ecs::Message& m);

	// Crear la entidad del caza, añadir sus componentes, asociarla con un handler
	// correspondiente, etc.
	virtual void initSystem();

	// Si el juego est?parado no hacer nada, en otro caso actualizar la velocidad
	// del caza y moverlo como en la práctica 1 (acelerar, desacelerar, etc). Además,
	// si el juego no est?parado y el jugador pulsa la tecla de disparo, enviar un
	// mensaje con las características físicas de la bala. Recuerda que se puede disparar
	// sólo una bala cada 0.25sec.
	virtual void update(float frameTime);
};