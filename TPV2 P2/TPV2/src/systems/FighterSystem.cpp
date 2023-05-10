#include "FighterSystem.h"

void FighterSystem::onCollision_FighterAsteroid() {
	// pos caza en el centro
	transform->setPos(Vector2D(sdl->width() / 2, sdl->height() / 2));
	// velocidad caza cero
	transform->setVel(Vector2D(0, 0));
	// rotación caza cero
	transform->setRot(0);
}



Vector2D FighterSystem::posBullet() {
	Vector2D p = transform->getPos();	// pos caza
	float w = transform->getWidth();	// anchura caza
	float h = transform->getHeight();	// altura caza
	float r = transform->getRot();		// rotación caza

	return p + Vector2D(w / 2.0f, h / 2.0f)
		- Vector2D(0.0f, h / 2.0f + 5.0f + 12.0f).rotate(r)
		- Vector2D(2.0f, 10.0f);
}

Vector2D FighterSystem::velBullet() {
	Vector2D vel = transform->getVel();	// vector velocidad caza
	float r = transform->getRot();

	// el último valor no est?en la fórmula
	// se le he añadido yo para que la bala vaya más lenta
	return (Vector2D(0.0f, -1.0f).rotate(r) * (vel.magnitude() + 5.0f)) * sdl->consts().at("BULLET_VELOCITY_FACTOR");
}

void FighterSystem::movement(float frameTime) {
	transform->setPos(transform->getPos() + transform->getVel() * frameTime);
}

void FighterSystem::decelerate() {
	Vector2D vel = transform->getVel() * deAcceleration->getDeceleration();
	// si la velocidad es muy baja, se pone a 0
	if (vel.magnitude() < deAcceleration->getLimit()) {
		vel = Vector2D(0, 0);
	}
	transform->setVel(vel);
}

void FighterSystem::fighterInput(float frameTime) {
	// Girar la nave
	float rot = transform->getRot();
	if (ih->isKeyDown(SDLK_LEFT)) {
		rot = rot - sdl->consts().at("FIGHTER_ROTATION");
	}
	else if (ih->isKeyDown(SDLK_RIGHT)) {
		rot = rot + sdl->consts().at("FIGHTER_ROTATION");
	}
	transform->setRot(rot);

	// Empujar la nave
	if (ih->isKeyDown(SDLK_UP)) {
		// se reproduce el sonido una sola vez
		// como channel = -1 se reproduce en el primer canal vacío
		// de forma predeterminada hay 8 canales y el sonido que se escucha es una mezcla de todos ellos
		fighterCtrl->getThrustSound()->play();
		// cuando se termina de reproducir el sonido el canal se vacía

		Vector2D newVel = transform->getVel() + Vector2D(0, -1).rotate(rot) * fighterCtrl->getThrust();
		if (newVel.magnitude() > fighterCtrl->getSpeedLimit()) {
			newVel = newVel.normalize() * fighterCtrl->getSpeedLimit();
		}
		transform->setVel(newVel);
	}

	// Disparar
	elapsedTime += frameTime;
	if (elapsedTime > gun->getTimer()) {
		if (ih->isKeyDown(SDLK_s)) {
			// mensaje con la información de la nave
			// para calcular las características física de la bala a partir de la misma
			ecs::Message m;
			m.id = ecs::_m_SHOOT;
			m.shoot_data.pos = posBullet();
			m.shoot_data.vel = velBullet();
			m.shoot_data.width = gun->getWBullet();
			m.shoot_data.height = gun->getHBullet();
			mngr_->send(m, true);

			m.id = ecs::_m_ADD_BULLET;
			mngr_->send(m, true);

			elapsedTime = 0;
		}
	}
}

void FighterSystem::showAtOpposideSide() {
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

void FighterSystem::setFighterSide()
{
	transform->setPos(Vector2D(sdl->width() - offset, sdl->height() / 2));
	mngr_->getHandler(ecs::FIGHTER)->addComponent<Image>(&sdl->images().at("fighter2"));
	switched = true;
}


void FighterSystem::receive(const ecs::Message& m) {
	switch (m.id) {
	case ecs::_m_COLLISION_FIGHTER_ASTEROID:
		onCollision_FighterAsteroid();
		break;
//	case ecs::_m_SERVER_CHOSEN:
		//restartFighters();
	//	break;
	//case ecs::_m_CLIENT_CHOSEN:
		//setFighterSide();
	//	break;
	//case ecs::_m_SUBSTRACT_OPPONENT_HP:
	case ecs::_m_COLLISION_BULLET_PLAYER:
	//	restartFighters();
		break;
	}
}

void FighterSystem::initSystem() {
	// fighter
	fighter = mngr_->addEntity(ecs::_grp_FIGHTER);

	float fighterSize = sdl->consts().at("FIGHTER_SIZE");
	transform = mngr_->addComponent<Transform>(fighter, Vector2D(sdl->width() / 2, sdl->height() / 2), fighterSize, fighterSize);
	// desaceleración y límite
	deAcceleration = mngr_->addComponent<DeAcceleration>(fighter);
	mngr_->addComponent<Image>(fighter, &sdl->images().at("fighter"));
	mngr_->addComponent<Health>(fighter);
	// empuje y límite de velocidad
	fighterCtrl = mngr_->addComponent<FighterCtrl>(fighter, sdl->consts().at("FIGHTER_THRUST"), sdl->consts().at("FIGHTER_SPEED_LIMIT"));
	// frecuencia de disparo
	gun = mngr_->addComponent<Gun>(fighter, sdl->consts().at("FIGHTER_BULLETS_FREQUENCY"));

	mngr_->setHandler(ecs::FIGHTER, fighter);
}

void FighterSystem::update(float frameTime) {
	if (mngr_->isActive(fighter)) {
		movement(frameTime);
		decelerate();
		fighterInput(frameTime);
		showAtOpposideSide();
	}
}