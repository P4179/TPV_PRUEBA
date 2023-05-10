#pragma once

#include "../ecs/System.h"
#include "../components/Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/checkML.h"
#include "../ecs/Manager.h"
#include "../game/GameStateMachine.h"

class OnlineButtonSystem : public ecs::System
{
private:
	InputHandler* ih;
	SDLUtils* sdl;
	GameStateMachine* gm;

	static void server();

	static void client();

	bool mouseIsOnButton(ecs::Entity* button);

	void checkButtonState(ecs::Entity* button);

public:
	constexpr static ecs::sysId id = ecs::_sys_ONLINE_BUTTON;

	OnlineButtonSystem() {
		ih = InputHandler::instance();
		sdl = SDLUtils::instance();
		gm = GameStateMachine::instance();
	}

	virtual void initSystem();

	virtual void update(float frameTime);
};

