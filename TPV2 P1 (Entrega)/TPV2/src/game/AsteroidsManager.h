#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "../components/Transform.h"
#include "../components/FramedImage.h"
#include "../components/ShowAtOpposideSide.h"
#include "../components/Generations.h"
#include "../components/Follow.h"
#include "../utils/checkML.h"

class AsteroidsManager : public ecs::Component {
private:
	int maxAsteroids;
	int numAsteroids;
	SDLUtils* sdl;
	float elapsedTime;
	float timer;
	int initAsteroids;

	// crea un asteroide a partir de una posición, una velocidad y una generación
	void createAsteroid(Vector2D pos, Vector2D vel, int gen);

	// posición de un nuevo asteroide
	Vector2D posNewAsteroid();
	// velocidad de un nuevo asteroide a partir de su posiición
	Vector2D velNewAsteroid(Vector2D p);

	// crea cero, uno o dos hijos de un asteroide que se ha destruido
	void createSons(int n, Transform* fatherTransform, int genSon);

	// añadir un nuevo asteroide cada cierto tiempo
	void addAsteroidFrequently();

public:
	constexpr static ecs::cmpId id = ecs::_ASTEROIDS_MANAGER;

	// llamada implícita a la constructora del padre
	AsteroidsManager(int maxAsteroids, float timer, int initAsteroids)
		: maxAsteroids(maxAsteroids), numAsteroids(0), sdl(SDLUtils::instance()), elapsedTime(0), timer(timer), initAsteroids(initAsteroids) { }

	// los nuevos asteroides iniciales se crean en el initComponent
	// porque entonces ya está disponible la referencia al manager
	virtual void initComponent();

	inline int getNumAsteroids() const {
		return numAsteroids;
	}

	inline int getInitAsteroids() const {
		return initAsteroids;
	}

	// crea nuevos asteroides, es decir, que no son hijos de otro
	void createNewAsteroids(int n);

	virtual void update(float frameTime);

	// divide un asteroide
	// a es una asteroide que haya chocado con una bala
	void onCollision(ecs::Entity* a);

	// marca como no vivos todos los asteroides que hay
	void destroyAllAsteroids();
};