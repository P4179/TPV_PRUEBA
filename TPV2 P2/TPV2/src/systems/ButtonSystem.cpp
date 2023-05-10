#include "ButtonSystem.h"
#include "../game/Game.h"
#include "../game/ConnectionState.h"

void ButtonSystem::play() {
	GameStateMachine::instance()->changeState<PlayState>();
}

void ButtonSystem::quit() {
	Game::instance()->setExit(true);
}

void ButtonSystem::online()
{
	GameStateMachine::instance()->changeState<ConnectionState>();
}

bool ButtonSystem::mouseIsOnButton(ecs::Entity* button) {
	Vector2D mousePos = Vector2D(ih->getMousePos().first, ih->getMousePos().second);

	SDL_Rect buttonRect = mngr_->getComponent<Transform>(button)->getRect();

	return mousePos.getX() > buttonRect.x && mousePos.getX() < buttonRect.x + buttonRect.w &&
		mousePos.getY() > buttonRect.y && mousePos.getY() < buttonRect.y + buttonRect.h;
}

void ButtonSystem::checkButtonState(ecs::Entity* button) {
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

void ButtonSystem::initSystem() {
	int offset = 150;

	// botón jugar
	int playW = 200;
	int playH = 100;
	ecs::Entity* playButton = mngr_->addEntity(ecs::_grp_BUTTONS);
	playButton->addComponent<Transform>(Vector2D(sdl->width() / 2 - playW / 2, sdl->height() - 3 * offset), playW, playH);
	array<Texture*, 3> playTextures{ &sdl->msgs().at("Play_Out"), &sdl->msgs().at("Play_Over"), &sdl->msgs().at("Play_Clicked") };
	playButton->addComponent<Button>(play, playTextures);

	// botón online
	int onlineW = 300;
	int onlineH = 100;
	ecs::Entity* onlineButton = mngr_->addEntity(ecs::_grp_BUTTONS);
	onlineButton->addComponent<Transform>(Vector2D(sdl->width() / 2 - onlineW / 2, sdl->height() - 2 * offset), onlineW, onlineH);
	array<Texture*, 3> onlineTextures{ &sdl->msgs().at("Online_Out"), &sdl->msgs().at("Online_Over"), &sdl->msgs().at("Online_Clicked") };
	onlineButton->addComponent<Button>(online, onlineTextures);

	// botón fuera de la partida
	int quitW = 200;
	int quitH = 100;
	ecs::Entity* quitButton = mngr_->addEntity(ecs::_grp_BUTTONS);
	quitButton->addComponent<Transform>(Vector2D(sdl->width() / 2 - quitW / 2, sdl->height() - offset), quitW, quitH);
	array<Texture*, 3> quitTextures{ &sdl->msgs().at("Quit_Out"), &sdl->msgs().at("Quit_Over"), &sdl->msgs().at("Quit_Clicked") };
	quitButton->addComponent<Button>(quit, quitTextures);

}

void ButtonSystem::update(float frameTime) {
	vector<ecs::Entity*> buttons = mngr_->getEntities(ecs::_grp_BUTTONS);
	for (auto button : buttons) {
		checkButtonState(button);
	}
}