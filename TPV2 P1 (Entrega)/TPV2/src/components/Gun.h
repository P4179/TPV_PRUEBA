#pragma once

#include "../ecs/Component.h"
#include "../utils/checkML.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/DisableOnExit.h"
#include "../components/Image.h"
#include "../ecs/Manager.h"
#include "./Transform.h"

class Gun : public ecs::Component {
private:
	InputHandler* ih;
	Transform* transform;
	SDLUtils* sdl;
	SoundEffect* fireSound;
	float timer;
	int wBullet;
	int hBullet;
	float elapsedTime;

	// calcula la posición de la bala
	Vector2D posBullet();

	// calcula la velocidad de la bala
	Vector2D velBullet();

	// crea una nueva bala y la añade al grupo apropiado
	void createBullet();

public:
	constexpr static ecs::cmpId id = ecs::_GUN;

	Gun(float bulletFrequency);

	// se llama cuando se añade el componente a la entidad
	virtual void initComponent();

	// si se pulsa S, se dispara una bala
	virtual void handleInput();

	// se el tiempo transcurrido para saber cada cuanto se puede disparar una bala
	virtual void update(float frameTime);
};