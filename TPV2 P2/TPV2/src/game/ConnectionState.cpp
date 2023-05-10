#include "ConnectionState.h"

void ConnectionState::onEnter()
{
	stateSystems.push_back(onlineButtonSystem = manager_->addSystem<OnlineButtonSystem>());
	stateSystems.push_back(gameCtrlSystem = manager_->addSystem<GameCtrlSystem>());
	stateSystems.push_back(renderSystem = manager_->addSystem<RenderSystem>());
}
