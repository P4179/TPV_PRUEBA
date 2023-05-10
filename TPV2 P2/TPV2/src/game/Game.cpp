#include "./Game.h"

void Game::render() const {
	sdlutils().clearRenderer();
	// stateMachine->render();
	sdlutils().presentRenderer();
}

void Game::handleInput() {
	ih->refresh();
	// se para el juego si se cierra la ventana de SDL
	if (ih->closeWindowEvent()) {
		_exit = true;
	}
	// stateMachine->handleInput();
}

Game::Game() : _exit(false) {
	// Initialise the SDLGame singleton
	SDLUtils::init("TVP2 P1", WIN_WIDTH, WIN_HEIGHT,
		"resources/config/asteroid.resources.json", 
		"resources/config/asteroid.config.json");

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
	uint32_t startTime, frameTime = 0;

	// bucle de juego
	while (!_exit) {
		startTime = sdl->currRealTime();

		handleInput();

		// actualiza update, render y handleinput de todos los objetos/sistemas del juego
		sdlutils().clearRenderer();
		stateMachine->update(frameTime);
		sdlutils().presentRenderer();

		// procesar los mensajes pendientes
		stateMachine->flushMessages();
		// eliminar entidades no vivas
		stateMachine->refresh();

		// se calcula el tiempo que ha durado el frame y si ha tardado menos que el framerate,
		// se suspende el juego para que el tiempo entre ticks sea mínimo el framerate
		frameTime = sdl->currRealTime() - startTime;

		if (frameTime < sdl->consts().at("FRAME_RATE")) {
			SDL_Delay(sdl->consts().at("FRAME_RATE") - frameTime);
			frameTime = sdl->consts().at("FRAME_RATE");
		}
	}
}