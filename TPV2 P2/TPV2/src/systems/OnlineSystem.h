#pragma once
#include "../ecs/System.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/SDLNetUtils.h"
#include "../game/GameStateMachine.h"
#include "../utils/checkML.h"
#include <string>
#include <cassert>

typedef uint8_t id_type;
using msgSize_t = Uint16;

class OnlineSystem : public	ecs::System
{
	std::string ip;
	GameState* currentState;

	SDLNet_SocketSet set;
	TCPsocket client, masterSocket;

	Uint8* msg;
	int result;
	bool isServer;


	void sendMessage(Uint8* end); //en "end" meter el m¨¦todo de serialize correspondiente de ecs_def
	void deserializeID(ecs::msgId_type id);
	void deserializeTransform(ecs::msgId_type id);
	//void serializeTransform(ecs::Message m);
	void deserializeOnlineBullet(ecs::msgId_type id);
	//void serializeOnlineBullet(ecs::Message m);
	void deserializeBulletFighterCollision(ecs::msgId_type id);
	//void serializeBulletFighterCollision(ecs::Message m);
	void deserializeName(ecs::msgId_type id);
	/*void serializeName(ecs::Message m);*/
	void deserializeGameover(ecs::msgId_type id);
	/*void serializeGameover(ecs::Message m);*/
	void deserializeHP(ecs::msgId_type id);
	/*void serializeHP(ecs::Message m);*/

	void processOnlineMessage(ecs::Message m);

public:
	constexpr static ecs::sysId id = ecs::_sys_ONLINE;

	OnlineSystem();
	OnlineSystem(bool s, std::string ip_);
	~OnlineSystem();

	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	virtual void receive(const ecs::Message& m);

	// Inicializar el sistema, etc.
	virtual void initSystem();

	// Si el juego est?parado no hacer nada, en otro caso mover las balas y
	// desactivar las que salen de la ventana como en la práctica 1.
	void update(float frameTime);
	
	void openServer();
	bool connectClient();
	bool openClient();

	void receiveM();
	void send();

	void error();
};

