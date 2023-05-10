#pragma once
#include "../ecs/System.h"
#include "SDL_stdinc.h"
#include "../game/GameStateMachine.h"
#include "../game/PlayState.h"
#include "../utils/checkML.h"
#include "../components/Button.h"
#include "../components/FramedImage.h"

// todos los estados
class RenderSystem : public ecs::System {
private:
	const int BIG_WIDTH = 500;
	const int BIG_HEIGHT = 100;

	const int PRESS_SPACE_WIDTH = 250;
	const int PRESS_SPACE_HEIGHT = 50;
	const int PRESS_SPACE_OFFSET = -200;

	const int FINISH_WIDTH = 300;
	const int FINIHS_HEIGHT = 100;

	const int INTRODUCE_OFFSET = -150;

	GameStateMachine* gm;
	GameState* currentState;
	float elapsedTime;
	// se coge aqu?porque es la misma todo el rato
	// y as?no hace falta que todas las balas tengan el componente Image
	Texture* bulletImage;
	SDLUtils* sdl;
	ecs::Entity* fighter;
	ecs::Entity* fighter2;
	//std::vector<ecs::Entity*>* grp_FIGHTERS;

	Vector2D waitingPos;
	std::string waitingText;
	ecs::Entity* waiting;
	ecs::Entity* name;

	void onCollisionFighterBullet(bool win);

	// dibujar todas las balas
	void drawBullets();

	// dibujar el caza
	void drawFighter();

	// dibujar el caza
	void drawFighter2();

	// dibujar las vidas del caza
	void drawFighterHealth();
	void drawFighterHealth2();

	// dibujar el nombre del caza, si es que tiene
	void drawFighterName(ecs::Entity* name);

	// animación del asteroide
	// se cambia el frame cada cierto tiempo
	void asteroidNextFrame(FramedImage* asteroidFramedImage, float frameTime);

	// dibujar asteroides
	void drawAsteroids(float frameTime);

	// dibujar botones
	void drawButtons();

	// dibujar el nombre mientras se va escribiendo
	void drawName();
	
	// dibujar texto
	void drawText();

	// añadir texto al manager
	// se añaden unos u otros dependiendo del estado
	void addText();

	ecs::Entity* createText(Vector2D pos, float width, float height, string msg);

public:
	constexpr static ecs::sysId id = ecs::_sys_RENDER;

	RenderSystem() : elapsedTime(0), fighter(nullptr), fighter2(nullptr), waiting(nullptr), name(nullptr) {
		sdl = SDLUtils::instance();
		gm = GameStateMachine::instance();
		currentState = gm->currentState();
		bulletImage = &sdl->images().at("fire");
	}

	// Inicializar el sistema, etc.
	virtual void initSystem();

	virtual void receive(const ecs::Message& m);

	// - Dibujar asteroides, balas y caza (sólo si el juego no est?parado).
	// - Dibujar las vidas (siempre).
	// - Dibujar los mensajes correspondientes: si el juego est?parado, etc (como en
	// la práctica 1)
	virtual void update(float frameTime);
};