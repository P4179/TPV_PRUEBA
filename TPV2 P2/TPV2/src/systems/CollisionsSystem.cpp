#include "CollisionsSystem.h"
#include "OnlineSystem.h"

bool CollisionsSystem::hasCollided(const SDL_Rect& rect1, const SDL_Rect& rect2) {
	return SDL_HasIntersection(&rect1, &rect2);
}

bool CollisionsSystem::collisionAsteroidFighter(ecs::Entity* asteroid) {
	// transform del asteroid
	Transform* asteroidTransform = asteroid->getComponent<Transform>();

	// comprobar si asteroide y caza han colisionado
	if (hasCollided(asteroidTransform->getRect(), fighterTransform->getRect())) {
		hitSound->play(0, 1);

		ecs::Message m;
		m.id = ecs::_m_COLLISION_FIGHTER_ASTEROID;
		mngr_->send(m, true);

		return true;
	}

	return false;
}

bool CollisionsSystem::collisionAsteroidBullet(ecs::Entity* asteroid) {
	vector<ecs::Entity*> bullets = mngr_->getEntities(ecs::_grp_BULLETS);

	// transform del asteroid
	Transform* asteroidTransform = asteroid->getComponent<Transform>();

	bool found = false;
	int i = 0;
	while (i < bullets.size() && !found) {
		Transform* bulletTransform = bullets[i]->getComponent<Transform>();
		// comprobar si asteroide y bala han colisionado
		if (hasCollided(asteroidTransform->getRect(), bulletTransform->getRect())) {

			// sin han colisionado, entonces
			// se ejectua el sonido de explosión
			explosionSound->play(0, 2);

			found = true;

			// se envía un mensaje de que han colisionado
			ecs::Message m;
			m.id = ecs::_m_COLLISION_BULLET_ASTEROID;
			m.collision_bullet_asteroid_data.asteroid = asteroid;
			m.collision_bullet_asteroid_data.bullet = bullets[i];
			mngr_->send(m, true);
		}
		++i;
	}
	return found;
}

bool CollisionsSystem::collisionBulletFighter()
{
	vector<ecs::Entity*> bullets = mngr_->getEntities(ecs::_grp_BULLETS);

	bool found = false;
	int i = 0;
	while (i < bullets.size() && !found) {
		Transform* bulletTransform = bullets[i]->getComponent<Transform>();
		// comprobar si asteroide y bala han colisionado
		if (hasCollided(fighterTransform->getRect(), bulletTransform->getRect())) {
			found = true;
			fighterBulletProcessCollision();
		}
		++i;
	}

	return found;
}

void CollisionsSystem::fighterBulletProcessCollision()
{
	// sin han colisionado, entonces
	// se ejectua el sonido de explosión
	hitSound->play(0, 2);

	// se envía un mensaje de que han colisionado
	ecs::Message m;
	m.id = ecs::_m_COLLISION_BULLET_PLAYER;

	ecs::Message m2;
	m2.id = ecs::_m_ONLINE_MESSAGE;
	m2.nId = ecs::_m_SUBSTRACT_OPPONENT_HP;

	mngr_->send(m, true);
	mngr_->send(m2, true);
}

void CollisionsSystem::initSystem() {
	ecs::Entity* fighter = mngr_->getHandler(ecs::FIGHTER);
	fighterTransform = mngr_->getComponent<Transform>(fighter);
}

void CollisionsSystem::update(float frameTime) {
	vector<ecs::Entity*> asteroids = mngr_->getEntities(ecs::_grp_ASTEROIDS);

	bool found = collisionBulletFighter();

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