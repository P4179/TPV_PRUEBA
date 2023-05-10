#include "./GameStateMachine.h"

void GameStateMachine::releaseTopState() {
	delete gameStates.top();
	gameStates.top() = nullptr;
	gameStates.pop();
}

void GameStateMachine::popState() {
	currentState()->setAlive(false);
}

void GameStateMachine::update(float frameTime) {
	currentState()->update(frameTime);
}

void GameStateMachine::render() {
	currentState()->render();
}

void GameStateMachine::handleInput() {
	currentState()->handleInput();
}

void GameStateMachine::refresh() {
	currentState()->refresh();

	// comprueba si algún estado de la pila no está vivo para eliminarlo
	// stack auxiliar para comprobar todos los estados
	stack<GameState*> aux;
	while (gameStates.size() > 0) {
		GameState* state = gameStates.top();
		if (!gameStates.top()->getAlive()) {
			releaseTopState();
		}
		else {
			aux.push(state);
			gameStates.pop();
		}
	}

	// se devuelven los estados de la pila auxiliar a la original
	while (aux.size() > 0) {
		gameStates.push(aux.top());
		aux.pop();
	}

}