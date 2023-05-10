#pragma once
#include "../ecs/System.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/SDLNetUtils.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/Name.h"
#include "../components/Health.h"
#include "../utils/checkML.h"
#include "../game/GameStateMachine.h"


using namespace std;
class OnlineFighterSystem : public ecs::System
{
private:
	SDLUtils* sdl;
	GameState* currentState;
	Transform* transform;
	Transform* transform2;
	SoundEffect* hitSound;
	bool server;
	const Uint8 timer;
	bool switched;

	const float offset;
	Name* name;
	char nameTextChar[10];
	string nameText;

	//actualiza el segundo fighter
	void updateFighterTransform(float x, float y, float r, float vx, float vy);

	void fighterTransformMessage();

	void setFighterSide();

	//reinicia naves
	void restartFighters();

	void roundStart();

	void setName(ecs::Message m);

	void substractOpponentHP();

	void sendShootMsg(ecs::Message m);

public:
	constexpr static ecs::sysId id = ecs::_sys_ONLINE_FIGHTER;

	OnlineFighterSystem() : transform(nullptr), transform2(nullptr), server(false), offset(50.0f), timer(10), 
		switched(false), name(nullptr), nameText(""), nameTextChar() {
		sdl = SDLUtils::instance();
		currentState = GameStateMachine::instance()->currentState();
		hitSound = &sdl->soundEffects().at("hit");
		for (int i = 0; i < nameText.size(); ++i) {
			nameTextChar[i] = nameText[i];
		}
	}

	OnlineFighterSystem(string name) : transform(nullptr), transform2(nullptr), server(false), offset(50.0f), timer(10), 
		switched(false), name(nullptr), nameText(name), nameTextChar() {
		sdl = SDLUtils::instance();
		currentState = GameStateMachine::instance()->currentState();
		hitSound = &sdl->soundEffects().at("hit");

		for (int i = 0; i < nameText.size(); ++i) {
			nameTextChar[i] = nameText[i];
		}
	}


	// Reaccionar a los mensajes recibidos (llamando a métodos correspondientes).
	virtual void receive(const ecs::Message& m);

	// Crear la entidad del caza, añadir sus componentes, asociarla con un handler
	// correspondiente, etc.
	virtual void initSystem();

	// Si el juego est?parado no hacer nada, en otro caso actualizar la velocidad
	// del caza y moverlo como en la práctica 1 (acelerar, desacelerar, etc). Además,
	// si el juego no est?parado y el jugador pulsa la tecla de disparo, enviar un
	// mensaje con las características físicas de la bala. Recuerda que se puede disparar
	// sólo una bala cada 0.25sec.
	virtual void update(float frameTime);
};

