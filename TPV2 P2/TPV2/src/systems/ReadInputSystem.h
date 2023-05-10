#pragma once
#include <iostream>
#include <vector>
#include "../ecs/System.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "../components/Transform.h"
#include "../components/SeparateLetters.h"
#include "../utils/checkML.h"

class ReadInputSystem : public ecs::System
{
private:
	const int WIDTH = 20;
	const int HEIGHT = 30;
	const int OFFSET = -100;

	InputHandler* ih;
	SDLUtils* sdl;
	std::string letter;
	SeparateLetters* separateLet;
	ecs::Entity* name;
	bool server_;

public:
	constexpr static ecs::sysId id = ecs::_sys_READ_INPUT;

	ReadInputSystem(bool server) : ih(InputHandler::instance()), sdl(SDLUtils::instance()),
		server_(server), separateLet(nullptr), name(nullptr), letter() { }

	// iniciar datos del sistema
	virtual void initSystem();

	virtual void update(float frameTime);
};

