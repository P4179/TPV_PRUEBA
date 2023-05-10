#include "./GameState.h"

GameState::GameState(ecs::stateId id) :
	id(id), gId(ecs::_gs_CONNECTING), sdl(SDLUtils::instance()), ih(InputHandler::instance()), alive(true) {
	manager_ = new ecs::Manager();
}

void GameState::update(float frameTime)
{
	for (auto sys : stateSystems)
		sys->update(frameTime);
}

void GameState::refresh() {
	manager_->refresh();
}

void GameState::flushMessages() {
	manager_->flushMessages();
}