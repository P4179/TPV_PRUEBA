#pragma once
#include "../ecs/System.h"
#include "../sdlutils/InputHandler.h"
#include "../game/GameStateMachine.h"
#include "../components/Health.h"
#include "../ecs/Entity.h"
#include "../utils/checkML.h"

// todos los estados
class GameCtrlSystem : public ecs::System {
private:
	InputHandler* ih;
	GameStateMachine* gm;
	GameState* currentState;
	ecs::Entity* fighter;

	// para gestionar el mensaje de que ha habido un choque entre el fighter y un un asteroide
	// tiene que avisar que ha acabado la ronda, quitar una vida al fighter, 
	// y si no hay m�s vidas avisar que ha acabado el juego (y quien es el ganador).
	void onCollision_FighterAsteroid();

	// para gestionar el mensaje de que no hay m�s asteroides. Tiene que avisar que
	// ha acabado la ronda y adem�s que ha acabado el juego (y quien es el ganador)
	void onAsteroidsExtinction();

	void onCollision_FighterBullet();

public:
	constexpr static ecs::sysId id = ecs::_sys_GAME_CTRL;

	GameCtrlSystem() : fighter(nullptr) {
		ih = InputHandler::instance();
		gm = GameStateMachine::instance();
		currentState = gm->currentState();
	}

	// Reaccionar a los mensajes recibidos (llamando a m�todos correspondientes).
	virtual void receive(const ecs::Message& m);

	// Inicializar el sistema, etc.
	virtual void initSystem();

	// si el juego no est� parado y el jugador pulsa SDLK_SPACE cambia el estado
	// como en la pr�ctica 1, etc. Tiene que enviar mensajes correspondientes cuando
	// empieza una ronda o cuando empieza una nueva partida.
	virtual void update(float frameTime);
};