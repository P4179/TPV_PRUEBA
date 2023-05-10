#pragma once
#include <stack>
#include "../game/GameState.h"
#include "../utils/checkML.h"

class GameStateMachine : public Singleton<GameStateMachine> {
	friend Singleton<GameStateMachine>;

private:
	stack<GameState*> gameStates;

	inline GameState* currentState() const {
		return gameStates.top();
	}

	// elimina memoria y quita de la pila al estado que está más arriba
	void releaseTopState();

	GameStateMachine() : gameStates() { }

public:
	virtual ~GameStateMachine() {
		while (gameStates.size() > 0) {
			releaseTopState();
		}
	}

	// añade un estado
	// se utilizan templates porque de esta forma la memoria se crea donde se destruye
	template<typename T>
	void pushState() {
		gameStates.push(new T);
	}

	// marca el estado que hay más arriba como no vivo
	void popState();

	// marca el estado de arriba como no vivo y añade otro
	template<typename T>
	void changeState() {
		popState();
		pushState<T>();
	}

	// update del estado actual
	void update(float frameTime);

	// render del estado actual
	void render();

	// handleInput del estado actual
	void handleInput();

	// refresh de las entidades del estado actual y de la propia pila de estados
	void refresh();
};