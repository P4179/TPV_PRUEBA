#include "./MainMenuState.h"
#include "./Game.h"

void MainMenuState::quit() {
	Game::instance()->setExit(true);
}

void MainMenuState::play() {
	GameStateMachine::instance()->changeState<PlayState>();
}

MainMenuState::MainMenuState() {
	init();
}

void MainMenuState::init() {
	int offset = 150;

	// botón jugar
	int playW = 200;
	int playH = 100;
	ecs::Entity* playButton = manager_->addEntity();
	playButton->addComponent<Transform>(Vector2D(sdl->width() / 2 - playW / 2, offset), playW, playH);
	playButton->addComponent<Image>(&sdl->msgs().at("Play"));
	playButton->addComponent<Button>(play);

	// botón fuera de la partida
	int quitW = 200;
	int quitH = 100;
	ecs::Entity* quitButton = manager_->addEntity();
	quitButton->addComponent<Transform>(Vector2D(sdl->width() / 2 - quitW / 2, sdl->height() - 2 * offset), quitW, quitH);
	quitButton->addComponent<Image>(&sdl->msgs().at("Quit"));
	quitButton->addComponent<Button>(quit);
}