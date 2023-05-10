#include "./WinState.h"
#include "./Game.h"

void WinState::finishGame() {
	Game::instance()->setExit(true);
}

WinState::WinState() : GameState() {
	init();
}

void WinState::init() {
	int winTextW = 300;
	int winTextH = 100;
	ecs::Entity* winText = manager_->addEntity();
	winText->addComponent<Transform>(Vector2D(sdl->width() / 2 - winTextW / 2, sdl->height() / 2 - winTextH / 2), winTextW, winTextH);
	winText->addComponent<Image>(&sdl->msgs().at("Win"));

	int pressSpaceW = 250;
	int pressSpaceH = 50;
	ecs::Entity* pressSpace = manager_->addEntity();
	pressSpace->addComponent<KeyToContinue>(SDLK_SPACE, finishGame);
	pressSpace->addComponent<Transform>(Vector2D(sdl->width() / 2 - pressSpaceW / 2, sdl->height() - 200), pressSpaceW, pressSpaceH);
	pressSpace->addComponent<Image>(&sdl->msgs().at("PressSpace"));
}