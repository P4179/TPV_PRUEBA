#include "./WinState.h"
#include "./Game.h"

void WinState::finishGame() {
	Game::instance()->setExit(true);
}

void WinState::onEnter() {
	stateSystems.push_back(gameCtrlSystem = manager_->addSystem<GameCtrlSystem>());
	stateSystems.push_back(renderSystem = manager_->addSystem<RenderSystem>());
}
