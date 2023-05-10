#include "OnlineSystem.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../game/ConnectionState.h"

Uint8 SDLNetUtils::buffer[]{};

void OnlineSystem::deserializeID(ecs::msgId_type id)
{
	ecs::Message m;
	m.id = id;
	switch (id)
	{
	case ecs::_m_FIGHTER_TRANSFORM:
		m.deserializeTransform(msg);
		break;
	case ecs::_m_ADD_BULLET:
		m.deserializeBullet(msg);
		break;
	//case ecs::_m_COLLISION_BULLET_PLAYER:
	//	m.deserializePlayerBulletCollision(msg);
	//	break;
	case ecs::_m_OTHER_NAME:
		m.deserializeName(msg);
		break;
	case ecs::_m_GAMEOVER:
		m.deserializeGameover(msg);
		break;
	case ecs::_m_SUBSTRACT_OPPONENT_HP:
		m.deserializeHP(msg);
		break;
	}
	mngr_->send(m);
}

void OnlineSystem::sendMessage(Uint8* end) {
	msgSize_t msgSize = end - SDLNetUtils::buffer;
	// convert to network endianness
	Uint16 size = msgSize;
	assert(size <= SDLNetUtils::bufferSize_);

	// send the message size as the header
	auto result = SDLNet_TCP_Send(client, reinterpret_cast<Uint8*>(&size),
		sizeof(msgSize_t));
	if (result != sizeof(msgSize_t))
		return;
	// send the message itself
	result = SDLNet_TCP_Send(client, SDLNetUtils::buffer, msgSize);
}

void OnlineSystem::deserializeTransform(ecs::msgId_type id)
{
	ecs::Message m;
	m.id = id;
	m.deserializeTransform(msg);

	mngr_->send(m);
}

//void OnlineSystem::serializeTransform(ecs::Message m)
//{
//	Uint8* end = m.serializeTransform(SDLNetUtils::buffer);
//	msgSize_t msgSize = end - SDLNetUtils::buffer;
//
//	// convert to network endianness
//	Uint16 size = msgSize;
//	assert(size <= SDLNetUtils::bufferSize_);
//
//	// send the message size as the header
//	auto result = SDLNet_TCP_Send(client, reinterpret_cast<Uint8*>(&size),
//		sizeof(msgSize_t));
//	if (result != sizeof(msgSize_t))
//		return;
//	// send the message itself
//	result = SDLNet_TCP_Send(client, SDLNetUtils::buffer, msgSize);
//
//}

void OnlineSystem::deserializeOnlineBullet(ecs::msgId_type id)
{
	ecs::Message m;
	m.id = id;
	m.deserializeBullet(msg);
	mngr_->send(m);
	
}


//void OnlineSystem::serializeOnlineBullet(ecs::Message m)
//{
//	Uint8* end = m.serializeBullet(SDLNetUtils::buffer);
//	msgSize_t msgSize = end - SDLNetUtils::buffer;
//
//	// convert to network endianness
//	Uint16 size = msgSize;
//	assert(size <= SDLNetUtils::bufferSize_);
//
//	// send the message size as the header
//	auto result = SDLNet_TCP_Send(client, reinterpret_cast<Uint8*>(&size),
//		sizeof(msgSize_t));
//	if (result != sizeof(msgSize_t))
//		return;
//	// send the message itself
//	result = SDLNet_TCP_Send(client, SDLNetUtils::buffer, msgSize);
//}
//
void OnlineSystem::deserializeBulletFighterCollision(ecs::msgId_type id)
{
	ecs::Message m;
	m.id = id;
	m.deserializePlayerBulletCollision(msg);

	mngr_->send(m);
}

//void OnlineSystem::serializeBulletFighterCollision(ecs::Message m)
//{
//	Uint8* end = m.serializePlayerBulletCollision(SDLNetUtils::buffer);
//	msgSize_t msgSize = end - SDLNetUtils::buffer;
//
//	// convert to network endianness
//	Uint16 size = msgSize;
//	assert(size <= SDLNetUtils::bufferSize_);
//
//	// send the message size as the header
//	auto result = SDLNet_TCP_Send(client, reinterpret_cast<Uint8*>(&size),
//		sizeof(msgSize_t));
//	if (result != sizeof(msgSize_t))
//		return;
//	// send the message itself
//	result = SDLNet_TCP_Send(client, SDLNetUtils::buffer, msgSize);
//}

void OnlineSystem::deserializeName(ecs::msgId_type id)
{
	ecs::Message m;
	m.id = id;
	m.deserializeName(msg);

	mngr_->send(m);
}

//void OnlineSystem::serializeName(ecs::Message m)
//{
//	Uint8* end = m.serializeName(SDLNetUtils::buffer);
//	msgSize_t msgSize = end - SDLNetUtils::buffer;
//
//	// convert to network endianness
//	Uint16 size = msgSize;
//	assert(size <= SDLNetUtils::bufferSize_);
//
//	// send the message size as the header
//	auto result = SDLNet_TCP_Send(client, reinterpret_cast<Uint8*>(&size),
//		sizeof(msgSize_t));
//	if (result != sizeof(msgSize_t))
//		return;
//	// send the message itself
//	result = SDLNet_TCP_Send(client, SDLNetUtils::buffer, msgSize);
//}

void OnlineSystem::deserializeGameover(ecs::msgId_type id)
{
	ecs::Message m;
	m.id = id;
	m.deserializeGameover(msg);

	mngr_->send(m);
}

//void OnlineSystem::serializeGameover(ecs::Message m)
//{
//	Uint8* end = m.serializeGameover(SDLNetUtils::buffer);
//	msgSize_t msgSize = end - SDLNetUtils::buffer;
//
//	// convert to network endianness
//	Uint16 size = msgSize;
//	assert(size <= SDLNetUtils::bufferSize_);
//
//	// send the message size as the header
//	auto result = SDLNet_TCP_Send(client, reinterpret_cast<Uint8*>(&size),
//		sizeof(msgSize_t));
//	if (result != sizeof(msgSize_t))
//		return;
//	// send the message itself
//	result = SDLNet_TCP_Send(client, SDLNetUtils::buffer, msgSize);
//}

void OnlineSystem::deserializeHP(ecs::msgId_type id)
{
	ecs::Message m;
	m.id = id;
	m.deserializeHP(msg);

	mngr_->send(m);
}

//void OnlineSystem::serializeHP(ecs::Message m)
//{
//	Uint8* end = m.serializeHP(SDLNetUtils::buffer);
//	msgSize_t msgSize = end - SDLNetUtils::buffer;
//
//	// convert to network endianness
//	Uint16 size = msgSize;
//	assert(size <= SDLNetUtils::bufferSize_);
//
//	// send the message size as the header
//	auto result = SDLNet_TCP_Send(client, reinterpret_cast<Uint8*>(&size),
//		sizeof(msgSize_t));
//	if (result != sizeof(msgSize_t))
//		return;
//	// send the message itself
//	result = SDLNet_TCP_Send(client, SDLNetUtils::buffer, msgSize);
//}

void OnlineSystem::processOnlineMessage(ecs::Message m)
{
	switch (m.nId)
	{
	case ecs::_m_FIGHTER_TRANSFORM:
		sendMessage(m.serializeTransform(SDLNetUtils::buffer));
		break;
	//case ecs::_m_COLLISION_BULLET_PLAYER:
		//sendMessage(m.serializePlayerBulletCollision(SDLNetUtils::buffer));
	//	break;
	case ecs::_m_OTHER_NAME:
		sendMessage(m.serializeName(SDLNetUtils::buffer));
		break;
	case ecs::_m_GAMEOVER:
		sendMessage(m.serializeGameover(SDLNetUtils::buffer));
		break;
	case ecs::_m_SUBSTRACT_OPPONENT_HP:
		sendMessage(m.serializeHP(SDLNetUtils::buffer));
		break;
	case ecs::_m_ADD_BULLET:
		sendMessage(m.serializeBullet(SDLNetUtils::buffer));
		break;
	default:
		break;
	}

}

void OnlineSystem::error()
{
	std::cout << "sdlnet error" << std::endl;
}

OnlineSystem::OnlineSystem() : ip(""), currentState(nullptr), set(nullptr), client(nullptr), masterSocket(nullptr), result(0), isServer(false) {
	if (SDLNet_Init() < 0) {
		error();
	}
}

OnlineSystem::OnlineSystem(bool s, std::string ip_) : ip(ip_), set(nullptr), client(nullptr), masterSocket(nullptr), result(0), isServer(s) {
	if (SDLNet_Init() < 0) {
		error();
	}
	currentState = GameStateMachine::instance()->currentState();

	set = SDLNet_AllocSocketSet(1);
}

OnlineSystem::~OnlineSystem() {
	SDLNet_FreeSocketSet(set);
	if (client)
		SDLNet_TCP_Close(client);
	if (masterSocket)
		SDLNet_TCP_Close(masterSocket);
	SDLNet_Quit();
}

void OnlineSystem::openServer()
{
	IPaddress ip;
	if (SDLNet_ResolveHost(&ip, nullptr, 2042) < 0) {
		error();
	}
	masterSocket = SDLNet_TCP_Open(&ip);
	if (!masterSocket) {
		error();
	}
}

bool OnlineSystem::connectClient()
{
	client = SDLNet_TCP_Accept(masterSocket);
	if (client) {
		SDLNet_TCP_AddSocket(set, client);
	}
	return client;
}

bool OnlineSystem::openClient()
{
	IPaddress ip;
	if (SDLNet_ResolveHost(&ip, "127.0.0.1", 2042) < 0) {
		error();
	}
	client = SDLNet_TCP_Open(&ip);
	if (!client) {
		cout << "server not online" << endl;
		return false;
	}
	SDLNet_TCP_AddSocket(set, client);
	return true;
}

void OnlineSystem::receive(const ecs::Message& m)
{
	switch (m.id) {
	case ecs::_m_ONLINE_MESSAGE:
		processOnlineMessage(m);
		break;
	case ecs::_m_SERVER_CHOSEN:
		openServer();
		break;
	case ecs::_m_GAMEOVER:
		currentState->setGameStateID(ecs::_gs_GAMEOVER);
		break;
	}
}

void OnlineSystem::initSystem()
{
	if (SDLNet_Init() < 0) {
		error();
	}

	mngr_->getHandler(ecs::FIGHTER);
}

void OnlineSystem::update(float frameTime)
{
	switch (currentState->getGameStateID())
	{
	case ecs::_gs_CONNECTING:
		if (isServer) {
			if (connectClient()) {
				currentState->setGameStateID(ecs::_gs_PLAYING);
				ecs::Message m;
				m.id = ecs::_m_ONLINE_GAME_START;
				mngr_->send(m);
			}
		}
		else {
			if (openClient()) {
				currentState->setGameStateID(ecs::_gs_PLAYING);
				ecs::Message m;
				m.id = ecs::_m_ONLINE_GAME_START;
				mngr_->send(m);
			}
		}
		break;
	case ecs::_gs_PLAYING:
		receiveM();
		break;

	default:
		break;
	}
}

void OnlineSystem::receiveM()
{
	while (SDLNet_CheckSockets(set, 0) > 0) {
		msg = SDLNetUtils::receiveMsg(client);
		if (msg == nullptr) {
			cout << "server closed..." << endl;
			currentState->setGameStateID(ecs::_gs_CONNECTING);
			ecs::Message m;
			m.id = ecs::_m_CONNECTION_LOST;
			mngr_->send(m);
			SDLNet_TCP_DelSocket(set, client);
			if (client)
				SDLNet_TCP_Close(client);
		}
		else {
			Uint8 id;
			SDLNetUtils::deserialize(id, msg);
			deserializeID(id);
		}
	}
}

