#include "./DeAcceleration.h"

void DeAcceleration::initComponent() {
	transform = ent_->getComponent<Transform>();
	assert(transform != nullptr);
}

void DeAcceleration::update(float frameTime) {
	Vector2D vel = transform->getVel() * deAcceleration;
	// si la velocidad es muy baja, se pone a 0
	if (vel.magnitude() < limit) {
		vel = Vector2D(0, 0);
	}
	transform->setVel(vel);
}