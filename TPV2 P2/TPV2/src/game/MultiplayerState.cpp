#include "MultiplayerState.h"

void MultiplayerState::pauseGame()
{
	GameStateMachine::instance()->pushState<PauseState>();
}

void MultiplayerState::onEnter()
{
	stateSystems.push_back(fighterSystem = manager_->addSystem<FighterSystem>());
	stateSystems.push_back(onlinefighterSystem = manager_->addSystem<OnlineFighterSystem>(name));
	stateSystems.push_back(bulletsSystem = manager_->addSystem<BulletSystem>());
	stateSystems.push_back(collisionsSystem = manager_->addSystem<CollisionsSystem>());
	stateSystems.push_back(gameCtrlSystem = manager_->addSystem<GameCtrlSystem>());
	stateSystems.push_back(renderSystem = manager_->addSystem<RenderSystem>());
	stateSystems.push_back(onlineSystem = manager_->addSystem<OnlineSystem>(server, ip));

	ecs::Message m;
	if (server) {
		m.id = ecs::_m_SERVER_CHOSEN;
	}
	else {
		m.id = ecs::_m_CLIENT_CHOSEN;
	}
	manager_->send(m);
	setGameStateID(ecs::_gs_CONNECTING);
}
