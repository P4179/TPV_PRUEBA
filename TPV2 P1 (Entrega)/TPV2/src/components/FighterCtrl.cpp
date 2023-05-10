#include "./FighterCtrl.h"

FighterCtrl::FighterCtrl(float thrust, float speedLimit)
	: transform(nullptr), thrust(thrust), speedLimit(speedLimit) {
	sdl = SDLUtils::instance();
	ih = InputHandler::instance();

	// se coge el sonido del map donde se han cargado todos los sonidos previamente
	thrustSound = &sdl->soundEffects().at("thrust");
}

void FighterCtrl::initComponent() {
	// se guarda la referencia al Transform de la entidad
	transform = ent_->getComponent<Transform>();
	// funciona como if(tr!=nullptr), pero produce un error si no se cumple la igualdad
	assert(transform != nullptr);
}

void FighterCtrl::handleInput() {
	float rot = transform->getRot();

	if (ih->isKeyDown(SDLK_LEFT)) {
		rot = rot - 5.0;
		transform->setRot(rot);
	}
	else if (ih->isKeyDown(SDLK_RIGHT)) {
		rot = rot + 5.0;
		transform->setRot(rot);
	}
	else if (ih->isKeyDown(SDLK_UP)) {
		// se reproduce el sonido una sola vez
		// como channel = -1 se reproduce en el primer canal vacío
		// de forma predeterminada hay 8 canales y el sonido que se escucha es una mezcla de todos ellos
		thrustSound->play();
		// cuando se termina de reproducir el sonido el canal se vacía

		Vector2D newVel = transform->getVel() + Vector2D(0, -1).rotate(rot) * thrust;
		if (newVel.magnitude() > speedLimit) {
			newVel = newVel.normalize() * speedLimit;
		}
		transform->setVel(newVel);
	}
}