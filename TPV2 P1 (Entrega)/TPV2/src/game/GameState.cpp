#include "./GameState.h"

GameState::GameState() : sdl(SDLUtils::instance()), ih(InputHandler::instance()), alive(true) {
	manager_ = new ecs::Manager();
}

void GameState::update(float frameTime) {
	manager_->update(frameTime);
}

void GameState::render() {
	manager_->render();
}

void GameState::handleInput() {
	manager_->handleInput();
}

void GameState::refresh() {
	manager_->refresh();
}