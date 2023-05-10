#include "BulletSystem.h"

void BulletSystem::shoot(Vector2D pos, Vector2D vel, double width, double height) {
	// no se añade image porque todas las balas utilizan la misma,
	// por lo tanto, se coge directamente la textura en RenderSystem
	ecs::Entity* bullet = mngr_->addEntity(ecs::_grp_BULLETS);
	// se asigna un canal concreto para asegurar que se reproduce el sonido
	// por si todos los canales están ocupados por el sonido del empuje
	fireSound->play(0, 0);
	//float rot = -vel.angle(Vector2D(0.0f, -1.0f));
	mngr_->addComponent<Transform>(bullet, pos, width, height, vel, -vel.angle(Vector2D(0.0f, -1.0f)));
}

void BulletSystem::onCollision_BulletAsteroid(ecs::Entity* b) {
	b->setAlive(false);
}

void BulletSystem::onRoundOver() {
	vector<ecs::Entity*> bullets = mngr_->getEntities(ecs::_grp_BULLETS);
	for (auto bullet : bullets) {
		bullet->setAlive(false);
	}
}

void BulletSystem::movement(ecs::Entity* bullet, float frameTime) {
	Transform* transform = mngr_->getComponent<Transform>(bullet);
	transform->setPos(transform->getPos() + transform->getVel() * frameTime);
}

void BulletSystem::disableOnExit(ecs::Entity* bullet) {
	Transform* transform = mngr_->getComponent<Transform>(bullet);
	Vector2D pos = transform->getPos();

	if (pos.getX() > sdl->width() ||
		pos.getX() + transform->getWidth() < 0 ||
		pos.getY() > sdl->height() ||
		pos.getY() + transform->getHeight() < 0) {
		bullet->setAlive(false);
	}
}

void BulletSystem::receive(const ecs::Message& m) {
	switch (m.id) {
	case ecs::_m_ADD_BULLET:
		shoot(m.shoot_data.pos, m.shoot_data.vel, m.shoot_data.width, m.shoot_data.height);
		break;

	case ecs::_m_COLLISION_BULLET_ASTEROID:
		onCollision_BulletAsteroid(m.collision_bullet_asteroid_data.bullet);
		break;
	case ecs::_m_COLLISION_BULLET_PLAYER:
	case ecs::_m_ROUND_FINISHED:
		onRoundOver();
		break;
	}
}

void BulletSystem::initSystem() {
	ecs::Entity* fighter = mngr_->getHandler(ecs::FIGHTER);
	fighterTransform = mngr_->getComponent<Transform>(fighter);
}

void BulletSystem::update(float frameTime) {
	vector<ecs::Entity*> bullets = mngr_->getEntities(ecs::_grp_BULLETS);
	for (auto bullet : bullets) {
		movement(bullet, frameTime);

		disableOnExit(bullet);
	}
}