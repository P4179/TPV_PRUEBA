#include "ReadInputSystem.h"
#include "../game/GameStateMachine.h"
#include "../game/MultiplayerState.h"

void ReadInputSystem::initSystem()
{
	name = mngr_->addEntity();
	mngr_->addComponent<Transform>(name, Vector2D(sdl->width() / 2 + OFFSET, sdl->height() / 2), WIDTH, HEIGHT);
	separateLet = mngr_->addComponent<SeparateLetters>(name);
	mngr_->setHandler(ecs::NAME, name);
}

void ReadInputSystem::update(float frameTime)
{
	if (mngr_->isActive(name)) {
		if (ih->isKeyDown(SDLK_BACKSPACE)) {
			separateLet->deleteLastLetter();
		}
		else if (ih->getTextInput(letter)) {
			if (!ih->isKeyDown(SDLK_SPACE)) {
				separateLet->newLetter(letter);
			}
		}
	}

	if (ih->isKeyDown(SDLK_SPACE)) {
		GameStateMachine::instance()->changeState<MultiplayerState>(server_, separateLet->getText());
	}
}
