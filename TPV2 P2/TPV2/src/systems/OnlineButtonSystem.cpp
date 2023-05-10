#include "OnlineButtonSystem.h"
#include "../game/Game.h"
#include "../game/ChooseNameState.h"

void OnlineButtonSystem::server()
{
	GameStateMachine::instance()->changeState<ChooseNameState>(true);
}

void OnlineButtonSystem::client()
{
	GameStateMachine::instance()->changeState<ChooseNameState>(false);
}

bool OnlineButtonSystem::mouseIsOnButton(ecs::Entity* button)
{
	Vector2D mousePos = Vector2D(ih->getMousePos().first, ih->getMousePos().second);

	SDL_Rect buttonRect = mngr_->getComponent<Transform>(button)->getRect();

	return mousePos.getX() > buttonRect.x && mousePos.getX() < buttonRect.x + buttonRect.w &&
		mousePos.getY() > buttonRect.y && mousePos.getY() < buttonRect.y + buttonRect.h;
}

void OnlineButtonSystem::checkButtonState(ecs::Entity* button)
{
	Button* buttonComp = button->getComponent<Button>();
	// el ratón está encima del botón
	if (mouseIsOnButton(button)) {
		buttonComp->setState(Button::MOUSE_OVER);
		// se ha clicado el botón
		if (ih->getMouseButtonState(InputHandler::LEFT) && buttonComp->getReleased()) {

			buttonComp->setReleased(false);
			buttonComp->setState(Button::CLICKED);

			ecs::Message m;
			m.id = ecs::_m_BUTTON_PRESSED;
			m.button_pressed_data.callback = buttonComp->getCallback();
			mngr_->send(m, true);

		}
		else if (!ih->getMouseButtonState(InputHandler::LEFT)) {
			buttonComp->setReleased(true);
			buttonComp->setState(Button::MOUSE_OVER);
		}
	}
	// el ratón está fuera del botón
	else {
		buttonComp->setState(Button::MOUSE_OUT);
	}
}

void OnlineButtonSystem::initSystem()
{
	int offset = 150;

	// botón de servidor
	int servW = 300;
	int servH = 100;
	ecs::Entity* serverButton = mngr_->addEntity(ecs::_grp_BUTTONS);
	serverButton->addComponent<Transform>(Vector2D(sdl->width() / 2 - servW / 2, sdl->height() - 3 * offset), servW, servH);
	array<Texture*, 3> serverTextures{ &sdl->msgs().at("Server_Out"), &sdl->msgs().at("Server_Over"), &sdl->msgs().at("Server_Clicked") };
	serverButton->addComponent<Button>(server, serverTextures);

	// botón de cliente
	int clientW = 300;
	int clientH = 100;
	ecs::Entity* clientButton = mngr_->addEntity(ecs::_grp_BUTTONS);
	clientButton->addComponent<Transform>(Vector2D(sdl->width() / 2 - clientW / 2, sdl->height() - 2 * offset), clientW, clientH);
	array<Texture*, 3> clientTextures{ &sdl->msgs().at("Client_Out"), &sdl->msgs().at("Client_Over"), &sdl->msgs().at("Client_Clicked") };
	clientButton->addComponent<Button>(client, clientTextures);
}

void OnlineButtonSystem::update(float frameTime)
{
	vector<ecs::Entity*> buttons = mngr_->getEntities(ecs::_grp_BUTTONS);
	for (auto button : buttons) {
		checkButtonState(button);
	}
}
