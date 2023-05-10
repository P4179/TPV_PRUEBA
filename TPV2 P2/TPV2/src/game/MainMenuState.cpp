#include "MainMenuState.h"
#include "Game.h"
#include "../systems/ButtonSystem.h"

void MainMenuState::onEnter() {
	stateSystems.push_back(buttonSystem = manager_->addSystem<ButtonSystem>());
	stateSystems.push_back(gameCtrlSystem = manager_->addSystem<GameCtrlSystem>());
	stateSystems.push_back(renderSystem = manager_->addSystem<RenderSystem>());
}
