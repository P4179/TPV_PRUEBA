#include "./PauseState.h"

void PauseState::resumeGame() {
	GameStateMachine::instance()->popState();
}

PauseState::PauseState() : GameState() {
	init();
}

void PauseState::init() {
	int pressSpaceW = 500;
	int pressSpaceH = 100;
	ecs::Entity* pressSpace = manager_->addEntity();
	pressSpace->addComponent<KeyToContinue>(SDLK_SPACE, resumeGame);
	pressSpace->addComponent<Transform>(Vector2D(sdl->width() / 2 - pressSpaceW / 2, sdl->height() / 2 - pressSpaceH / 2), pressSpaceW, pressSpaceH);
	pressSpace->addComponent<Image>(&sdl->msgs().at("PressSpace"));
}