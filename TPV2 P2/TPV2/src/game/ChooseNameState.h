#pragma once
#include "./GameState.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/ReadInputSystem.h"

class RenderSystem;

class ChooseNameState : public GameState {
	GameCtrlSystem* gameCtrlSystem;
	RenderSystem* renderSystem;
	ReadInputSystem* readInputSystem;
	bool server_;
public:
	ChooseNameState(bool server) : GameState(ecs::_s_NAME), gameCtrlSystem(nullptr), renderSystem(nullptr), 
		readInputSystem(nullptr), server_(server) { }

	virtual void onEnter();

	virtual void update(float frameTime);
};