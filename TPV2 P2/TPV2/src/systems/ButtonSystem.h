#pragma once

#include "../ecs/System.h"
#include "../components/Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../utils/checkML.h"
#include "../ecs/Manager.h"
#include "../game/GameStateMachine.h"

// mainmenustate, pausestate, gameoverstate, winstate
class ButtonSystem : public ecs::System {
private:
	InputHandler* ih;
	SDLUtils* sdl;
	GameStateMachine* gm;

	static void play();

	inline static void quit();

	static void online();

	bool mouseIsOnButton(ecs::Entity* button);

	void checkButtonState(ecs::Entity* button);

public:
	constexpr static ecs::sysId id = ecs::_sys_BUTTON;

	ButtonSystem() {
		ih = InputHandler::instance();
		sdl = SDLUtils::instance();
		gm = GameStateMachine::instance();
	}

	virtual void initSystem();

	virtual void update(float frameTime);
};