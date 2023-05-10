#include "ChooseNameState.h"
#include "../systems/RenderSystem.h"

void ChooseNameState::onEnter()
{

	stateSystems.push_back(readInputSystem = manager_->addSystem<ReadInputSystem>(server_));
	stateSystems.push_back(gameCtrlSystem = manager_->addSystem<GameCtrlSystem>());
	stateSystems.push_back(renderSystem = manager_->addSystem <RenderSystem>());
}

void ChooseNameState::update(float frameTime)
{
	for (auto sys : stateSystems)
		sys->update(frameTime);
}
