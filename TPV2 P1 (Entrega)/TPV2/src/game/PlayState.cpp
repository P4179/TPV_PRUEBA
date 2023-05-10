#include "./PlayState.h"

void PlayState::pauseGame() {
	GameStateMachine::instance()->pushState<PauseState>();
}

// llamada implícita a la constructora vacía del padre (no haría falta ponerlo)
PlayState::PlayState() : GameState() {
	init();
}

void PlayState::init() {
	// fighter
	ecs::Entity* fighter = manager_->addEntity();
	fighter->addComponent<Transform>(Vector2D(sdl->width() / 2, sdl->height() / 2), 50, 50);
	fighter->addComponent<DeAcceleration>(0.95);
	fighter->addComponent<Image>(&sdl->images().at("fighter"));
	fighter->addComponent<Health>(3, &sdl->images().at("heart"));
	fighter->addComponent<FighterCtrl>(0.2, 3 * 0.05);
	fighter->addComponent<Gun>(0.25);
	fighter->addComponent<ShowAtOpposideSide>();
	manager_->setHandler(ecs::FIGHTER, fighter);

	// managers
	ecs::Entity* managerContainer = manager_->addEntity();
	managerContainer->addComponent<AsteroidsManager>(30, 5000, 10);
	managerContainer->addComponent<CollisionsManager>();

	// pausar juego
	ecs::Entity* pressSpace = manager_->addEntity();
	pressSpace->addComponent<KeyToContinue>(SDLK_SPACE, pauseGame);
}