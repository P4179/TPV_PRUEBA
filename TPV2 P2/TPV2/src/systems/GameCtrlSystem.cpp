#include "GameCtrlSystem.h"
#include "../game/PauseState.h"
#include "../game/GameState.h"
#include "../game/WinState.h"
#include "../game/MainMenuState.h"
#include "../game/GameoverState.h"

void GameCtrlSystem::onCollision_FighterAsteroid() {
	// enviar un mensaje informando que la ronda ha terminado
	ecs::Message m1;
	m1.id = ecs::_m_ROUND_FINISHED;
	// los mensajes siempre se envían con delay
	mngr_->send(m1, true);

	// se quita una vida al caza
	Health* fighterHealth = mngr_->getComponent<Health>(fighter);
	fighterHealth->substractLife();

	// se ha perdido, hay que notificar a los demas sistemas
	if (fighterHealth->getLifes() <= 0) {
		gm->changeState<GameoverState>();
	}
	// en caso de que queden vidas, se empieza una nueva ronda
	else {
		ecs::Message m2;
		m2.id = ecs::_m_ROUND_STARTED;
		mngr_->send(m2, true);
	}
}

void GameCtrlSystem::onAsteroidsExtinction() {
	// se notifica que ha acabado la ronda
	ecs::Message m1;
	m1.id = ecs::_m_ROUND_FINISHED;
	mngr_->send(m1, true);

	gm->changeState<WinState>();
}

void GameCtrlSystem::onCollision_FighterBullet() {
	Health* fighterHealth;
	// se quita una vida al caza
	fighterHealth = mngr_->getComponent<Health>(fighter);
	fighterHealth->substractLife();
	std::cout << "Quitada vida a jugador" << std::endl;

	// se ha perdido, hay que notificar a los demas sistemas
	if (fighterHealth->getLifes() <= 0) {
		ecs::Message m1;
		m1.id = ecs::_m_GAMEOVER;
		mngr_->send(m1);
	}
}

void GameCtrlSystem::receive(const ecs::Message& m) {
	switch (m.id) {
	case ecs::_m_COLLISION_FIGHTER_ASTEROID:
		onCollision_FighterAsteroid();
		break;

	case ecs::_m_NO_ASTEROIDS:
		onAsteroidsExtinction();
		break;

	case ecs::_m_BUTTON_PRESSED:
		m.button_pressed_data.callback();
		break;

	case ecs::_m_COLLISION_BULLET_PLAYER:
		onCollision_FighterBullet();
		break;
	}

}

void GameCtrlSystem::initSystem() {
	if (currentState->getStateID() == ecs::_s_PLAY) {
		// se notifica que ha empezado una nueva ronda, 
		// para realizar el commit inicial de asteroides
		ecs::Message m;
		m.id = ecs::_m_ROUND_STARTED;
		mngr_->send(m, true);
	}

	fighter = mngr_->getHandler(ecs::FIGHTER);
}

void GameCtrlSystem::update(float frameTime) {
	if (ih->isKeyDown(SDLK_SPACE)) {
		switch (currentState->getStateID()) {
		case ecs::_s_PLAY:
			gm->pushState<PauseState>(fighter);
			break;

		case ecs::_s_PAUSE:
			gm->popState();
			break;

		case ecs::_s_WIN:
		case ecs::_s_GAMEOVER:
			gm->changeState<MainMenuState>();
			break;
		}

		switch (currentState->getGameStateID()) {
		case ecs::_gs_GAMEOVER:
			gm->changeState<MainMenuState>();
			break;
		}
	}
}
