#include "./Follow.h"

void Follow::initComponent() {
	// se guarda la referencia al Transform de la entidad
	transform = ent_->getComponent<Transform>();
	// funciona como if(tr!=nullptr), pero produce un error si no se cumple la igualdad
	assert(transform != nullptr);

	ecs::Entity* fighter = mngr_->getHandler(ecs::FIGHTER);
	fighterTransform = fighter->getComponent<Transform>();
}

void Follow::update(float frameTime) {
	Vector2D v = transform->getVel();
	Vector2D p = transform->getPos();
	Vector2D q = fighterTransform->getPos();

	// se gira el vector de velocidad en un grado en cada iteración
	// para que vaya hacia el caza
	v = v.rotate(v.angle(q - p) > 0 ? 1.0f : -1.0f);

	transform->setVel(v);
}