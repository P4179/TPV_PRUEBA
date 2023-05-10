#include "AsteroidsSystem.h"

void AsteroidsSystem::createAsteroid(Vector2D pos, Vector2D vel, int gen) {
	if (numOfAsteroids_ < maxAsteroids) {

		ecs::Entity* asteroid = mngr_->addEntity(ecs::_grp_ASTEROIDS);

		float asteroidSize = sdl->consts().at("ASTEROID_SIZE");
		mngr_->addComponent<Transform>(asteroid, pos, asteroidSize * gen, asteroidSize * gen, vel * sdl->consts().at("ASTEROID_VELOCITY_FACTOR"));
		mngr_->addComponent<Generations>(asteroid, gen);

		Texture* texture;
		// asteroide tipo B
		if (sdlutils().rand().nextInt(0, 10) < 3) {
			texture = &sdl->images().at("asteroid_gold");
			// se añade solo para poder comprobar después que es del tipo B
			asteroid->addComponent<Follow>();
		}
		// asteroide tipo A
		else {
			texture = &sdl->images().at("asteroid_silver");
		}
		// textura del asteroide
		mngr_->addComponent<FramedImage>(asteroid, texture);

		// se incrementa el número de asteroides
		++numOfAsteroids_;
	}
}

void AsteroidsSystem::createChildren(int n, Transform* fatherTransform, int genSon) {
	Vector2D posFather = fatherTransform->getPos();
	Vector2D velFather = fatherTransform->getVel();
	float wFather = fatherTransform->getWidth();
	float hFather = fatherTransform->getHeight();

	for (int i = 0; i < n && numOfAsteroids_ < maxAsteroids; ++i) {
		int r = sdl->rand().nextInt(0, 360);
		// posición y velocidad del asteroide hijo
		Vector2D pos = posFather + velFather.rotate(r) * 2 * std::max(wFather, hFather);
		Vector2D vel = velFather.rotate(r) * sdl->consts().at("ASTEROID_CHILD_ACCELERATE");

		// se crea un nuevo asteroide hijo
		createAsteroid(pos, vel, genSon);
	}
}

Vector2D AsteroidsSystem::posNewAsteroid() {
	int startZone = sdl->consts().at("ASTEROID_START_ZONE");
	int endZone = sdl->consts().at("ASTEROID_END_ZONE");

	Vector2D p = Vector2D();

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

Vector2D AsteroidsSystem::velNewAsteroid(Vector2D p) {
	// posición aleatoria en el centro de la pantalla
	Vector2D c = Vector2D(sdl->width() / 2, sdl->height() / 2) +
		Vector2D(sdl->rand().nextInt(-100, 101), sdl->rand().nextInt(-100, 101));

	float speed = sdl->rand().nextInt(1, 10) / 10.0f;
	// vector de velocidad
	Vector2D v = (c - p).normalize() * speed;

	return v;
}

void AsteroidsSystem::createNewAsteroids(int n) {
	for (int i = 0; i < n; ++i) {

		Vector2D p = posNewAsteroid();
		Vector2D v = velNewAsteroid(p);
		int gen = sdl->rand().nextInt(1, 4);

		createAsteroid(p, v, gen);
	}
}

void AsteroidsSystem::onCollision_AsteroidBullet(ecs::Entity* a) {
	mngr_->setAlive(a, false);
	--numOfAsteroids_;

	Generations* gens = mngr_->getComponent<Generations>(a);

	int genFather = gens->getGen();
	int genSon = genFather - 1;

	if (genSon > 0) {
		// transform del asteroide padre
		Transform* fatherTransform = mngr_->getComponent<Transform>(a);
		createChildren(2, fatherTransform, genSon);
	}
	else if (numOfAsteroids_ <= 0) {
		ecs::Message m;
		m.id = ecs::_m_NO_ASTEROIDS;
		mngr_->send(m, true);
	}
}

void AsteroidsSystem::onRoundOver() {
	vector<ecs::Entity*> asteroids = mngr_->getEntities(ecs::_grp_ASTEROIDS);

	for (auto asteroid : asteroids) {
		asteroid->setAlive(false);
	}

	numOfAsteroids_ = 0;
}

void AsteroidsSystem::onRoundStart() {
	createNewAsteroids(initAsteroids);
}

void AsteroidsSystem::movement(ecs::Entity* asteroid, float frameTime) {
	Transform* transform = mngr_->getComponent<Transform>(asteroid);
	transform->setPos(transform->getPos() + transform->getVel() * frameTime);
}

void AsteroidsSystem::showAtOpossideSide(ecs::Entity* asteroid) {
	Transform* transform = mngr_->getComponent<Transform>(asteroid);
	Vector2D pos = transform->getPos();

	// derecha
	if (pos.getX() > sdl->width()) {
		transform->setPos(Vector2D(0, pos.getY()));
	}
	// izquierda
	else if (pos.getX() + transform->getWidth() < 0) {
		transform->setPos(Vector2D(sdl->width() - transform->getWidth(), pos.getY()));
	}
	// abajo
	else if (pos.getY() > sdl->height()) {
		transform->setPos(Vector2D(pos.getX(), 0));
	}
	// arriba
	else if (pos.getY() + transform->getHeight() < 0) {
		transform->setPos(Vector2D(pos.getX(), sdl->height() - transform->getHeight()));
	}
}

void AsteroidsSystem::follow(ecs::Entity* asteroid) {
	if (mngr_->hasComponent<Follow>(asteroid)) {
		Transform* transform = mngr_->getComponent<Transform>(asteroid);
		Vector2D v = transform->getVel();
		Vector2D p = transform->getPos();
		Vector2D q = fighterTransform->getPos();

		// se gira el vector de velocidad en un grado en cada iteración
		// para que vaya hacia el caza
		v = v.rotate(v.angle(q - p) > 0 ? 1.0f : -1.0f);

		transform->setVel(v);
	}
}

void AsteroidsSystem::receive(const ecs::Message& m) {
	switch (m.id) {
	case ecs::_m_ROUND_STARTED:
		onRoundStart();
		break;
	case ecs::_m_ROUND_FINISHED:
		onRoundOver();
		break;
	case ecs::_m_COLLISION_BULLET_ASTEROID:
		onCollision_AsteroidBullet(m.collision_bullet_asteroid_data.asteroid);
		break;
	}
}

void AsteroidsSystem::initSystem() {
	ecs::Entity* fighter = mngr_->getHandler(ecs::FIGHTER);
	fighterTransform = mngr_->getComponent<Transform>(fighter);
}

void AsteroidsSystem::update(float frameTime) {
	// cada cierto tiempo se añade un nuevo asteroide
	elapsedTime += frameTime;
	if (elapsedTime > timer) {
		elapsedTime = 0;

		createNewAsteroids(1);
	}

	vector<ecs::Entity*> asteroids = mngr_->getEntities(ecs::_grp_ASTEROIDS);
	for (auto asteroid : asteroids) {

		movement(asteroid, frameTime);

		showAtOpossideSide(asteroid);

		follow(asteroid);
	}
}