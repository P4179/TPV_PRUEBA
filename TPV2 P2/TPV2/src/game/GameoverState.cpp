#include "./GameoverState.h"
#include "./Game.h"

void GameoverState::finishGame() {
	Game::instance()->setExit(true);
}

void GameoverState::onEnter() {
	stateSystems.push_back(gameCtrlSystem = manager_->addSystem<GameCtrlSystem>());
	stateSystems.push_back(renderSystem = manager_->addSystem<RenderSystem>());
}
