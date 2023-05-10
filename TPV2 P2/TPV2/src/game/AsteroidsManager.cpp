#include "./AsteroidsManager.h"

void AsteroidsManager::createAsteroid(Vector2D pos, Vector2D vel, int gen) {
	if (numAsteroids < maxAsteroids) {

		ecs::Entity* asteroid = mngr_->addEntity(ecs::_grp_ASTEROIDS);

		asteroid->addComponent<Transform>(pos, (10.0f + 5.0f) * gen, (10.0f + 5.0f) * gen, vel * 0.05);
		asteroid->addComponent<ShowAtOpposideSide>();
		asteroid->addComponent<Generations>(gen);

		Texture* texture;
		// asteroide tipo B
		if (sdlutils().rand().nextInt(0, 10) < 3) {
			texture = &sdl->images().at("asteroid_gold");
		}
		// asteroide tipo A
		else {
			texture = &sdl->images().at("asteroid_silver");
			// asteroid->addComponent<Follow>();
		}
		// textura del asteroide
		asteroid->addComponent<FramedImage>(texture);

		// se incrementa el número de asteroides
		++numAsteroids;
	}
}

Vector2D AsteroidsManager::posNewAsteroid() {
	int startZone = 10;
	int endZone = 100;

	Vector2D p;

	int rand = sdl->rand().nextInt(0, 4);
	switch (rand) {
		// izquierda
	case 0:
		p = Vector2D(sdl->rand().nextInt(startZone, endZone),
			sdl->rand().nextInt(startZone, sdl->height() - startZone));
		break;
		// derecha
	case 1:
		p = Vector2D(sdl->rand().nextInt(sdl->width() - endZone, sdl->width() - startZone),
			sdl->rand().nextInt(startZone, sdl->height() - startZone));
		break;
		// arriba
	case 2:
		p = Vector2D(sdl->rand().nextInt(startZone, sdl->width() - startZone),
			sdl->rand().nextInt(startZone, endZone));
		break;
		// abajo
	case 3:
		p = Vector2D(sdl->rand().nextInt(startZone, sdl->width() - startZone),
			sdl->rand().nextInt(sdl->height() - endZone, sdl->height() - startZone));
		break;
	}
	return p;
}

Vector2D AsteroidsManager::velNewAsteroid(Vector2D p) {
	// posición aleatoria en el centro de la pantalla
	Vector2D c = Vector2D(sdl->width() / 2, sdl->height() / 2) +
		Vector2D(sdl->rand().nextInt(-100, 101), sdl->rand().nextInt(-100, 101));

	float speed = sdl->rand().nextInt(1, 10) / 10.0f;
	// vector de velocidad
	Vector2D v = (c - p).normalize() * speed;

	return v;
}

void AsteroidsManager::createSons(int n, Transform* fatherTransform, int genSon) {
	Vector2D posFather = fatherTransform->getPos();
	Vector2D velFather = fatherTransform->getVel();
	float wFather = fatherTransform->getWidth();
	float hFather = fatherTransform->getHeight();

	for (int i = 0; i < n && numAsteroids < maxAsteroids; ++i) {
		int r = sdl->rand().nextInt(0, 360);
		// posición y velocidad del asteroide hijo
		Vector2D pos = posFather + velFather.rotate(r) * 2 * std::max(wFather, hFather);
		Vector2D vel = velFather.rotate(r) * 1.1f;

		// se crea un nuevo asteroide hijo
		createAsteroid(pos, vel, genSon);
	}
}

void AsteroidsManager::addAsteroidFrequently() {
	if (elapsedTime > timer) {
		elapsedTime = 0;

		createNewAsteroids(1);
	}
}

void AsteroidsManager::initComponent() {
	createNewAsteroids(initAsteroids);
}

void AsteroidsManager::createNewAsteroids(int n) {
	for (int i = 0; i < n; ++i) {

		Vector2D p = posNewAsteroid();
		Vector2D v = velNewAsteroid(p);
		int gen = sdl->rand().nextInt(1, 4);

		createAsteroid(p, v, gen);
	}
}

	// a es una asteroide que haya chocado con una bala
void AsteroidsManager::onCollision(ecs::Entity* a) {
	a->setAlive(false);
	--numAsteroids;

	Generations* gens = a->getComponent<Generations>();

	int genFather = gens->getGen();
	int genSon = genFather - 1;

	if (genSon > 0) {

		// transform del asteroide padre
		Transform* fatherTransform = a->getComponent<Transform>();
		createSons(2, fatherTransform, genSon);
	}
}

void AsteroidsManager::destroyAllAsteroids() {
	// se obtiene el grupo asteroides
	vector<ecs::Entity*> asteroids = mngr_->getEntities(ecs::_grp_ASTEROIDS);

	for (int i = 0; i < asteroids.size(); ++i) {
		asteroids[i]->setAlive(false);
	}

	numAsteroids = 0;
}

void AsteroidsManager::update(float frameTime) {
	elapsedTime += frameTime;

	addAsteroidFrequently();
}