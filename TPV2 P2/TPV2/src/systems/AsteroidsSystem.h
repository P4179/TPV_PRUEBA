#pragma once
#include "../ecs/System.h"
#include "SDL_stdinc.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Generations.h"
#include "../components/Transform.h"
#include "../components/Follow.h"
#include "../components/FramedImage.h"
#include "../ecs/Manager.h"
#include "../utils/checkML.h"

// solo en playstate
class AsteroidsSystem : public ecs::System {
private:
	SDLUtils* sdl;
	// el número actual de asteroides en el juego
	Uint8 numOfAsteroids_;
	// máximo de asteroides
	int maxAsteroids;
	// número inicial de asteroides cada ronda
	int initAsteroids;
	float elapsedTime;
	// cada cuanto aparece un nuevo asteroides
	float timer;
	Transform* fighterTransform;

	void createAsteroid(Vector2D pos, Vector2D vel, int gen);

	// crear 0, 1 o 2 asteroides hijos a partir de uno que se ha destruido
	void createChildren(int n, Transform* fatherTransform, int genSon);

	// posición de un nuevo asteroide
	Vector2D posNewAsteroid();

	// velocidad de un nuevo asteroide a partir de su posición
	Vector2D velNewAsteroid(Vector2D p);

	// crear nuevos asteroides, es decir, que no son hijos de otros
	void createNewAsteroids(int n);

	// para gestionar el mensaje de que ha habido un choque de un asteroide con una
	// bala. Desactivar el asteroide “a” y crear 2 asteroides como en la práctica 1,
	// y si no hay más asteroides enviar un mensaje correspondiente.
	void onCollision_AsteroidBullet(ecs::Entity* a);

	// para gestionar el mensaje de que ha acabado la ronda
	// desactivar todos los asteroides
	void onRoundOver();

	// para gestionar el mensaje de que ha empezado una ronda
	// añadir los asteroides iniciales
	void onRoundStart();

	// mover un asteroide
	void movement(ecs::Entity* asteroid, float frameTime);

	// hacer que si el asteroide se sale por un lado aparezca por el otro
	void showAtOpossideSide(ecs::Entity* asteroid);

	// hacer que siga al jugador, solo si es del tipo B, es decir,
	// tiene el componente Follow
	void follow(ecs::Entity* asteroid);

public:
	constexpr static ecs::sysId id = ecs::_sys_ASTEROIDS;

	// llamada implícita a la constructora del padre
	AsteroidsSystem(int maxAsteroids, int initAsteroids, float timer) :
		maxAsteroids(maxAsteroids), numOfAsteroids_(0), initAsteroids(initAsteroids), timer(timer), elapsedTime(0), fighterTransform(nullptr) {
		sdl = SDLUtils::instance();
	}

	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	virtual void receive(const ecs::Message& m);

	// Inicializar el sistema, etc.
	virtual void initSystem();

	// Si el juego está parado no hacer nada, en otro caso mover los asteroides como
	// en la práctica 1 y generar 1 asteroide nuevo cada 5 segundos (aparte
	// de los 10 al principio de cada ronda).
	virtual void update(float frameTime);
};