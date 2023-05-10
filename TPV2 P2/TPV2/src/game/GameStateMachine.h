#pragma once
#include <stack>
#include "../game/GameState.h"
#include "../utils/checkML.h"

class GameStateMachine : public Singleton<GameStateMachine> {
	friend Singleton<GameStateMachine>;

private:
	stack<GameState*> gameStates;

	// elimina memoria y quita de la pila al estado que está más arriba
	void releaseTopState();

	GameStateMachine() : gameStates() { }

public:
	virtual ~GameStateMachine() {
		while (gameStates.size() > 0) {
			releaseTopState();
		}
	}

	inline GameState* currentState() const {
		return gameStates.top();
	}

	// añade un estado sin borrar el que ya había
	// se utilizan templates porque de esta forma la memoria se crea memoria donde se destruye
	template<typename T, typename ...Ts>
	void pushState(Ts&& ...args) {
		GameState* state = new T(std::forward<Ts>(args)...);
		gameStates.push(state);
		state->onEnter();
	}

	// elimina el estado actual
	void popState();

	// cambia el estado actual por otro
	template<typename T, typename ...Ts>
	void changeState(Ts&& ...args) {
		// se comprueba que no está vacía la pila de estados
		if (!gameStates.empty()) {
			// se crea el estado
			GameState* state = new T(std::forward<Ts>(args)...);
			// se comprueba que el nuevo estado no es el mismo que el actual
			if (gameStates.top()->getStateID() != state->getStateID()) {
				gameStates.top()->setAlive(false);
				gameStates.push(state);
				state->onEnter();
			}
		}
	}

	// update del estado actual
	void update(float frameTime);

	void flushMessages();

	// refresh de las entidades del estado actual y de la propia pila de estados
	void refresh();
};