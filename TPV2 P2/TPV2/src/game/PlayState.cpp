#include "./PlayState.h"
#include "../systems/RenderSystem.h"

void PlayState::onEnter() {
	stateSystems.push_back(fighterSystem = manager_->addSystem<FighterSystem>());
	stateSystems.push_back(bulletsSystem = manager_->addSystem<BulletSystem>());
	stateSystems.push_back(asteroidsSystem = manager_->addSystem<AsteroidsSystem>(30, 2, 50 * 1000));
	stateSystems.push_back(collisionsSystem = manager_->addSystem<CollisionsSystem>());
	stateSystems.push_back(gameCtrlSystem = manager_->addSystem<GameCtrlSystem>());
	stateSystems.push_back(renderSystem = manager_->addSystem<RenderSystem>());
}
