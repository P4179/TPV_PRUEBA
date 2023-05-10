#include "./PauseState.h"
#include "../systems/RenderSystem.h"

void PauseState::onEnter() {
	Health* health = fighterPlay->getComponent<Health>();
	int lifes = health->getLifes();
	Texture* texture = health->getTexture();

	ecs::Entity* fighter = manager_->addEntity();
	manager_->addComponent<Health>(fighter, lifes, texture);
	manager_->setHandler(ecs::FIGHTER, fighter);	

	stateSystems.push_back(gameCtrlSystem = manager_->addSystem<GameCtrlSystem>());
	stateSystems.push_back(renderSystem = manager_->addSystem<RenderSystem>());
}