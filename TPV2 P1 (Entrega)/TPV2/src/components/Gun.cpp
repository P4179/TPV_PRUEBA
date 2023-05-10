#include "./Gun.h"

Vector2D Gun::posBullet() {
	Vector2D p = transform->getPos();		// pos caza
	float w = transform->getWidth();	// anchura caza
	float h = transform->getHeight();	// altura caza
	float r = transform->getRot();	// rotación caza

	return p + Vector2D(w / 2.0f, h / 2.0f)
		- Vector2D(0.0f, h / 2.0f + 5.0f + 12.0f).rotate(r)
		- Vector2D(2.0f, 10.0f);
}

Vector2D Gun::velBullet() {
	Vector2D vel = transform->getVel();	// vector velocidad caza
	float r = transform->getRot();

	// el último valor no está en la fórmula
	// se le he añadido yo para que la bala vaya más lenta
	return (Vector2D(0.0f, -1.0f).rotate(r) * (vel.magnitude() + 5.0f)) * 0.05;
}

void Gun::createBullet() {
	ecs::Entity* bullet = mngr_->addEntity(ecs::_grp_BULLETS);
	bullet->addComponent<Transform>(posBullet(), wBullet, hBullet, velBullet(), transform->getRot());
	bullet->addComponent<Image>(&sdl->images().at("fire"));
	bullet->addComponent<DisableOnExit>();
}

Gun::Gun(float bulletFrequency) :
	transform(nullptr), timer(bulletFrequency * 1000), wBullet(5), hBullet(20), elapsedTime(0) {
	sdl = SDLUtils::instance();
	ih = InputHandler::instance();
	fireSound = &sdl->soundEffects().at("fire");
}

void Gun::initComponent() {
	transform = ent_->getComponent<Transform>();
	assert(transform != nullptr);
}

void Gun::handleInput() {
	if (elapsedTime > timer) {
		if (ih->isKeyDown(SDLK_s)) {
			// se asigna un canal concreto para asegurar que se reproduce el sonido
			// por si todos los canales están ocupados por el sonido del empuje
			fireSound->play(0, 0);

			createBullet();
			elapsedTime = 0;
		}
	}
}

void Gun::update(float frameTime) {
	elapsedTime += frameTime;
}