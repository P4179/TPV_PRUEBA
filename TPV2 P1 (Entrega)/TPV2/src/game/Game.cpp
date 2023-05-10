#include "./Game.h"

void Game::render() const {
	sdlutils().clearRenderer();
	stateMachine->render();
	sdlutils().presentRenderer();
}

void Game::handleInput() {
	ih->refresh();
	// se para el juego si se cierra la ventana de SDL
	if (ih->closeWindowEvent()) {
		_exit = true;
	}
	stateMachine->handleInput();
}

Game::Game() : _exit(false) {
	// Initialise the SDLGame singleton
	SDLUtils::init("TVP2 P1", 800, 600,
		"resources/config/asteroid.resources.json");

	// reference to the SDLUtils Singleton. You could use it as a pointer as well,
	// I just prefer to use . instead of ->, it is just a matter of taste, nothing
	// else!
	//
	// you can also use the inline method sdlutils() that simply returns the value
	// of *SDLUtils::instance() --- it is defined at the end of SDLUtils.h
	//
	sdl = SDLUtils::instance();

	//show the cursor
	sdl->showCursor();

	// reference to the input handler (we could use a pointer, I just . rather than ->).
	// you can also use the inline method ih() that is defined in InputHandler.h
	ih = InputHandler::instance();

	stateMachine = GameStateMachine::init();

	// pila de estados
	stateMachine->pushState<MainMenuState>();
}

void Game::run() {
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();

	// bucle de juego
	while (!_exit) {
		handleInput();
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime >= FRAME_RATE) {
			stateMachine->update(frameTime);
			startTime = SDL_GetTicks();
		}
		render();
		stateMachine->refresh();
	}
}