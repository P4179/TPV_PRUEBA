#include "OnlineFighterSystem.h"
#include "BulletSystem.h"
#include "OnlineSystem.h"

void OnlineFighterSystem::fighterTransformMessage()
{
	ecs::Message m;
	m.id = ecs::_m_ONLINE_MESSAGE;
	m.nId = ecs::_m_FIGHTER_TRANSFORM;

	m.fighter_transform_data.posx = transform->getPos().getX();
	m.fighter_transform_data.posy = transform->getPos().getY();
	m.fighter_transform_data.rot = transform->getRot();
	m.fighter_transform_data.velx = transform->getVel().getX();
	m.fighter_transform_data.vely = transform->getVel().getY();

	mngr_->send(m, false);
}

void OnlineFighterSystem::updateFighterTransform(float x, float y, float r, float vx, float vy)
{
	transform2->setPos(Vector2D(x, y));
	transform2->setRot(r);
	transform2->setVel(Vector2D(vx, vy));
}

void OnlineFighterSystem::restartFighters()
{
	if (!switched) {
		transform->setPos(Vector2D(0, sdl->height() / 2));
		transform->setRot(0.0f);
	}
	else {
		transform->setPos(Vector2D(sdl->width() - offset, sdl->height() / 2));
		transform->setRot(0.0f);
	}
}

void OnlineFighterSystem::roundStart()
{
	mngr_->setActive(mngr_->getHandler(ecs::FIGHTER), true);
	mngr_->setActive(mngr_->getHandler(ecs::FIGHTER2), true);
	
	mngr_->getComponent<Health>(mngr_->getHandler(ecs::FIGHTER))->initLifes();
	mngr_->getComponent<Health>(mngr_->getHandler(ecs::FIGHTER2))->initLifes();

	ecs::Message m1;
	m1.id = ecs::_m_ONLINE_MESSAGE;
	m1.nId = ecs::_m_OTHER_NAME;
	std::copy(std::begin(nameTextChar), std::end(nameTextChar), m1.name_data.name);
	m1.name_data.size = nameText.size();
	mngr_->send(m1, true);
}

void OnlineFighterSystem::setName(ecs::Message m)
{
	char* name = m.name_data.name;
	int size = m.name_data.size;
	string nameString;
	for (int i = 0; i < size; ++i) {
		nameString.push_back(name[i]);
	}
	mngr_->getHandler(ecs::FIGHTER2)->getComponent<Name>()->setName(nameString);
}

void OnlineFighterSystem::substractOpponentHP()
{
	std::cout << "Quitada vida a jugador 2" << std::endl;
	mngr_->getComponent<Health>(mngr_->getHandler(ecs::FIGHTER2))->substractLife();
}

void OnlineFighterSystem::setFighterSide()
{
	transform2->setPos(Vector2D(0, sdl->height() / 2));
	mngr_->getHandler(ecs::FIGHTER2)->addComponent<Image>(&sdl->images().at("fighter"));
	switched = true;
}

void OnlineFighterSystem::receive(const ecs::Message& m) {
	switch (m.id) {
	case ecs::_m_FIGHTER_TRANSFORM:
		updateFighterTransform(m.fighter_transform_data.posx, m.fighter_transform_data.posy,
			m.fighter_transform_data.rot, m.fighter_transform_data.velx, m.fighter_transform_data.vely);
		break;
	case ecs::_m_CONNECTION_LOST:
		restartFighters();
		mngr_->setActive(mngr_->getHandler(ecs::FIGHTER), false);
		mngr_->setActive(mngr_->getHandler(ecs::FIGHTER2), false);
		break;
	case ecs::_m_CLIENT_CHOSEN:
		setFighterSide();
		name->setName(nameText);
		break;
	case ecs::_m_SERVER_CHOSEN:
		name->setName(nameText);
		break;
	case ecs::_m_ONLINE_GAME_START:
		restartFighters();
		roundStart();
		break;
	case ecs::_m_OTHER_NAME:
		setName(m);
		break;
	case ecs::_m_COLLISION_BULLET_PLAYER: //informado por m¨ª mismo
		restartFighters();
		break;
	case ecs::_m_SUBSTRACT_OPPONENT_HP://informado por el otro jugador
		restartFighters();
		substractOpponentHP();
		break;
	case ecs::_m_SHOOT:
		sendShootMsg(m);
		break;
	}
}


void OnlineFighterSystem::sendShootMsg(ecs::Message m) {
	ecs::Message m1 = m;
	m1.id = ecs::_m_ONLINE_MESSAGE;
	m1.nId = ecs::_m_ADD_BULLET;
	mngr_->send(m1, false);

}

void OnlineFighterSystem::initSystem() {
	// fighter2
	ecs::Entity* fighter2 = mngr_->addEntity(ecs::_grp_FIGHTER);

	float fighterSize = sdl->consts().at("FIGHTER_SIZE");
	transform2 = mngr_->addComponent<Transform>(fighter2, Vector2D(sdl->width() - offset, sdl->height() / 2), fighterSize, fighterSize);
	mngr_->addComponent<Image>(fighter2, &sdl->images().at("fighter2"));
	mngr_->addComponent<Name>(fighter2, Vector2D(0, fighterSize), fighterSize, 30);
	mngr_->addComponent<Health>(fighter2);

	mngr_->setHandler(ecs::FIGHTER2, fighter2);

	ecs::Entity* fighter = mngr_->getHandler(ecs::FIGHTER);
	transform = fighter->getComponent<Transform>();
	mngr_->setActive(fighter, false);
	mngr_->setActive(fighter2, false);

	name = mngr_->addComponent<Name>(fighter, Vector2D(0, fighterSize), fighterSize, 30);
}

void OnlineFighterSystem::update(float frameTime) {
	switch (currentState->getGameStateID())
	{
	case ecs::_gs_PLAYING:
		fighterTransformMessage();
		break;
	default:
		break;
	}
}