#include "./CollisionsManager.h"

bool CollisionsManager::hasCollided(const SDL_Rect& rect1, const SDL_Rect& rect2) {
	return SDL_HasIntersection(&rect1, &rect2);
}

void CollisionsManager::deactivateBullets() {
	vector<ecs::Entity*> bullets = mngr_->getEntities(ecs::_grp_BULLETS);

	for (int i = 0; i < bullets.size(); ++i) {
		bullets[i]->setAlive(false);
	}
}

bool CollisionsManager::collisionAsteroidFighter(ecs::Entity* asteroid) {
	// transform del asteroid
	Transform* asteroidTransform = asteroid->getComponent<Transform>();

	// comprobar si asteroide y caza han colisionado
	if (hasCollided(asteroidTransform->getRect(), fighterTransform->getRect())) {
		hitSound->play(0, 1);

		// desactiva todos los asteroides
		asteroidsManager->destroyAllAsteroids();
		// desactiva todas las balas
		deactivateBullets();

		// pos caza en el centro
		fighterTransform->setPos(Vector2D(sdl->width() / 2, sdl->height() / 2));
		// velocidad caza cero
		fighterTransform->setVel(Vector2D(0, 0));
		// rotación caza cero
		fighterTransform->setRot(0);

		// quita una vida y marca el juego para la siguiente ronda o que ha terminado
		fighterHealth->substractLife();

		// JUEGO TERMINADO
		if (fighterHealth->getLifes() <= 0) {
			stateMachine->changeState<GameoverState>();
		}
		// SIGUIENTE RONDA
		else {
			asteroidsManager->createNewAsteroids(asteroidsManager->getInitAsteroids());
		}
		return true;
	}
}

bool CollisionsManager::collisionAsteroidBullet(ecs::Entity* asteroid) {
	vector<ecs::Entity*> bullets = mngr_->getEntities(ecs::_grp_BULLETS);

	// transform del asteroid
	Transform* asteroidTransform = asteroid->getComponent<Transform>();

	bool found = false;
	int i = 0;
	while (i < bullets.size() && !found) {
		Transform* bulletTransform = bullets[i]->getComponent<Transform>();
		// comprobar si asteroide y bala han colisionado
		if (hasCollided(asteroidTransform->getRect(), bulletTransform->getRect())) {
			explosionSound->play(0, 2);

			found = true;

			// desactiva la bala
			bullets[i]->setAlive(false);

			asteroidsManager->onCollision(asteroid);

			// HA GANADO
			if (asteroidsManager->getNumAsteroids() <= 0) {
				stateMachine->changeState<WinState>();
			}
		}
		++i;
	}
	return found;
}

void CollisionsManager::checkCollision() {
	vector<ecs::Entity*> asteroids = mngr_->getEntities(ecs::_grp_ASTEROIDS);

	bool found = false;
	int i = 0;
	while (i < asteroids.size() && !found) {
		// colisión asteroide-caza
		found = collisionAsteroidFighter(asteroids[i]);

		// si ha asteroide y caza no han colisionado se comprueba entre asteroide y bala
		if (!found) {
			// colisión asteroide-bala
			found = collisionAsteroidBullet(asteroids[i]);
		}

		++i;
	}
}

CollisionsManager::CollisionsManager() :
	asteroidsManager(nullptr), fighterTransform(nullptr), fighterHealth(nullptr),
	sdl(SDLUtils::instance()), stateMachine(GameStateMachine::instance()) {

	explosionSound = &sdl->soundEffects().at("explosion");
	hitSound = &sdl->soundEffects().at("hit");
}

void CollisionsManager::initComponent() {
	asteroidsManager = ent_->getComponent<AsteroidsManager>();
	ecs::Entity* fighter = mngr_->getHandler(ecs::FIGHTER);

	fighterTransform = fighter->getComponent<Transform>();
	fighterHealth = fighter->getComponent<Health>();
}

void CollisionsManager::update(float frameTime) {
	checkCollision();
}