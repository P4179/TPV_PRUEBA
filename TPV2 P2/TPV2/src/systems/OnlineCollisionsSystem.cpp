#include "OnlineCollisionsSystem.h"
#include "OnlineSystem.h"

bool OnlineCollisionsSystem::hasCollided(const SDL_Rect& rect1, const SDL_Rect& rect2)
{
	return SDL_HasIntersection(&rect1, &rect2);
}

void OnlineCollisionsSystem::collisionBulletFighter()
{
	vector<ecs::Entity*> bullets = mngr_->getEntities(ecs::_grp_BULLETS);

	bool found = false;
	int i = 0;
	while (i < bullets.size() && !found) {
		Transform* bulletTransform = bullets[i]->getComponent<Transform>();
		// comprobar si asteroide y bala han colisionado
		if (hasCollided(fighterTransform->getRect(), bulletTransform->getRect())) {

			// sin han colisionado, entonces
			// se ejectua el sonido de explosión
			hitSound->play(0, 2);

			found = true;

			// se envía un mensaje de que han colisionado
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  			ecs::Message m2;
			m2.id = ecs::_m_ONLINE_MESSAGE;
			m2.nId = ecs::_m_COLLISION_BULLET_PLAYER;
			m2.bullet_player_collision_data.winner = 1;
			mngr_->getSystem<OnlineSystem>()->receive(m2);

			ecs::Message m;
			m.id = ecs::_m_COLLISION_BULLET_PLAYER;
			m.bullet_player_collision_data.winner = 0;
			mngr_->send(m, true);
		}
		++i;
	}
}

void OnlineCollisionsSystem::collisionBulletFighter2()
{
	vector<ecs::Entity*> bullets = mngr_->getEntities(ecs::_grp_BULLETS);

	bool found = false;
	int i = 0;
	while (i < bullets.size() && !found) {
		Transform* bulletTransform = bullets[i]->getComponent<Transform>();
		// comprobar si asteroide y bala han colisionado
		if (hasCollided(fighterTransform->getRect(), bulletTransform->getRect())) {

			// sin han colisionado, entonces
			// se ejectua el sonido de explosión
			hitSound->play(0, 2);

			found = true;

			// se envía un mensaje de que han colisionado
			ecs::Message m;
			m.id = ecs::_m_COLLISION_BULLET_PLAYER;
			m.bullet_player_collision_data.winner = 1;
			mngr_->send(m, true);

			ecs::Message m2;
			m2.id = ecs::_m_ONLINE_MESSAGE;
			m2.nId = ecs::_m_COLLISION_BULLET_PLAYER;
			m2.bullet_player_collision_data.winner = 0;
			mngr_->send(m, true);
		}
		++i;
	}
}

void OnlineCollisionsSystem::initSystem()
{
	ecs::Entity* fighter = mngr_->getHandler(ecs::FIGHTER);
	fighterTransform = mngr_->getComponent<Transform>(fighter);
}

void OnlineCollisionsSystem::update(float frameTime)
{
	switch (currentState->getGameStateID())
	{
	case ecs::_gs_PLAYING:
		collisionBulletFighter();
		collisionBulletFighter2();
		break;
	default:
		break;
	}
}
