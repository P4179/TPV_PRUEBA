#include "./GameoverState.h"
#include "./Game.h"

void GameoverState::finishGame() {
	Game::instance()->setExit(true);
}

GameoverState::GameoverState() : GameState() {
	init();
}

void GameoverState::init() {
	int gameoverW = 300;
	int gameoverH = 100;
	ecs::Entity* winText = manager_->addEntity();
	winText->addComponent<Transform>(Vector2D(sdl->width() / 2 - gameoverW / 2, sdl->height() / 2 - gameoverH / 2), gameoverW, gameoverH);
	winText->addComponent<Image>(&sdl->msgs().at("Gameover"));

	int pressSpaceW = 250;
	int pressSpaceH = 50;
	ecs::Entity* pressSpace = manager_->addEntity();
	pressSpace->addComponent<KeyToContinue>(SDLK_SPACE, finishGame);
	pressSpace->addComponent<Transform>(Vector2D(sdl->width() / 2 - pressSpaceW / 2, sdl->height() - 200), pressSpaceW, pressSpaceH);
	pressSpace->addComponent<Image>(&sdl->msgs().at("PressSpace"));
}