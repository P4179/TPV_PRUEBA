#include "RenderSystem.h"
#include "../components/Name.h"
#include "../components/SeparateLetters.h"

void RenderSystem::onCollisionFighterBullet(bool win)
{
	mngr_->setActive(waiting, false);

	mngr_->setActive(mngr_->getHandler(ecs::FIGHTER), false);
	mngr_->setActive(mngr_->getHandler(ecs::FIGHTER2), false);

	if (win) {
		createText(Vector2D(sdl->width() / 2 - FINISH_WIDTH / 2, sdl->height() / 2 - FINIHS_HEIGHT / 2), FINISH_WIDTH, FINIHS_HEIGHT, "Win");
		createText(Vector2D(sdl->width() / 2 - PRESS_SPACE_WIDTH / 2, sdl->height() + PRESS_SPACE_OFFSET), PRESS_SPACE_WIDTH, PRESS_SPACE_HEIGHT, "PressSpace");
	}
	else {
		createText(Vector2D(sdl->width() / 2 - FINISH_WIDTH / 2, sdl->height() / 2 - FINIHS_HEIGHT / 2), FINISH_WIDTH, FINIHS_HEIGHT, "Gameover");
		createText(Vector2D(sdl->width() / 2 - PRESS_SPACE_WIDTH / 2, sdl->height() + PRESS_SPACE_OFFSET), PRESS_SPACE_WIDTH, PRESS_SPACE_HEIGHT, "PressSpace");
	}
}

void RenderSystem::drawBullets() {
	vector<ecs::Entity*> bullets = mngr_->getEntities(ecs::_grp_BULLETS);
	for (auto bullet : bullets) {
		if (mngr_->isActive(bullet)) {
			Transform* transform = mngr_->getComponent<Transform>(bullet);
			Image* image = mngr_->getComponent<Image>(bullet);

			bulletImage->render(transform->getRect(), transform->getRot());
		}
	}
}

void RenderSystem::drawFighter() {
	if (mngr_->isActive(fighter)) {
		Transform* transform = mngr_->getComponent<Transform>(fighter);
		Image* image = mngr_->getComponent<Image>(fighter);
		image->getTexture()->render(transform->getRect(), transform->getRot());
	}
}

void RenderSystem::drawFighter2()
{
	if (mngr_->isActive(fighter2) && mngr_->isActive(fighter)) {
		Transform* transform = mngr_->getComponent<Transform>(fighter);
		Image* image = mngr_->getComponent<Image>(fighter);
		image->getTexture()->render(transform->getRect(), transform->getRot());

		Transform* transform2 = mngr_->getComponent<Transform>(fighter2);
		Image* image2 = mngr_->getComponent<Image>(fighter2);
		image2->getTexture()->render(transform2->getRect(), transform2->getRot());
	}
}

void RenderSystem::drawFighterHealth() {
	if (mngr_->isActive(fighter)) {
		Health* health = mngr_->getComponent<Health>(fighter);

		SDL_Rect dest;
		dest.w = dest.h = sdl->consts().at("FIGHTER_HEALTH_SIZE");
		dest.y = 0;
		// renderiza cada corazón uno detrás de otro
		for (int i = 0; i < health->getLifes(); ++i) {
			dest.x = 0 + dest.w * i;

			health->getTexture()->render(dest);
		}
	}

}

void RenderSystem::drawFighterHealth2() {
	if (mngr_->isActive(fighter2)) {
		Health* health = mngr_->getComponent<Health>(fighter2);

		SDL_Rect dest;
		dest.w = dest.h = sdl->consts().at("FIGHTER_HEALTH_SIZE");
		dest.y = 0;
		// renderiza cada corazón uno detrás de otro
		for (int i = 0; i < health->getLifes(); ++i) {
			dest.x = sdl->width() - dest.w - dest.w * i;

			health->getTexture()->render(dest);
		}
	}
}
void RenderSystem::drawFighterName(ecs::Entity* fighter)
{
	if (mngr_->isActive(fighter)) {
		Transform* transform = mngr_->getComponent<Transform>(fighter);

		Name* name = mngr_->getComponent<Name>(fighter);
		SDL_Rect rect;
		rect.x = transform->getPos().getX() + name->getOffset().getX();
		rect.y = transform->getPos().getY() + name->getOffset().getY();
		rect.w = name->getWidth();
		rect.h = name->getHeight();
		name->getName()->render(rect);
	}
}

void RenderSystem::asteroidNextFrame(FramedImage* asteroidFramedImage, float frameTime) {
	asteroidFramedImage->increaseElapsedTime(frameTime);

	if (asteroidFramedImage->getElapsedTime() > asteroidFramedImage->getTimer()) {
		asteroidFramedImage->resetElapsedTime();

		// se coge el frame de la siguiente columna
		asteroidFramedImage->increaseCol();
		if (asteroidFramedImage->getCol() >= asteroidFramedImage->getTexture()->getCols()) {
			// si se han recorrido todas las columnas, se pasa a la siguiente fila
			asteroidFramedImage->increaseRow();
			asteroidFramedImage->setCol(0);

			// si se han recorrido todas las filas, se vuelve a la primera
			if (asteroidFramedImage->getRow() >= asteroidFramedImage->getTexture()->getRows()) {
				asteroidFramedImage->setRow(0);
			}
		}
	}
}

void RenderSystem::drawAsteroids(float frameTime) {
	vector<ecs::Entity*> asteroids = mngr_->getEntities(ecs::_grp_ASTEROIDS);
	for (auto asteroid : asteroids) {
		if (mngr_->isActive(asteroid)) {
			Transform* transform = mngr_->getComponent<Transform>(asteroid);
			FramedImage* framedImage = mngr_->getComponent<FramedImage>(asteroid);

			asteroidNextFrame(framedImage, frameTime);

			framedImage->getTexture()->renderFrame(transform->getRect(), framedImage->getRow(), framedImage->getCol());
		}
	}
}

void RenderSystem::drawButtons() {
	vector<ecs::Entity*> buttons = mngr_->getEntities(ecs::_grp_BUTTONS);
	for (auto button : buttons) {
		if (mngr_->isActive(button)) {
			Texture* texture = button->getComponent<Button>()->getCurrentTexture();
			SDL_Rect rect = button->getComponent<Transform>()->getRect();

			texture->render(rect);
		}
	}
}

void RenderSystem::drawName()
{
	if (mngr_->isActive(name)) {
		Transform* transform = mngr_->getComponent<Transform>(name);
		SeparateLetters* separateLet = mngr_->getComponent<SeparateLetters>(name);
		vector<Texture*>* letters = separateLet->getLetters();

		for (int i = 0; i < letters->size(); ++i) {
			SDL_Rect dest;
			dest.x = transform->getPos().getX() + i * transform->getWidth();
			dest.y = transform->getPos().getY();
			dest.w = transform->getWidth();
			dest.h = transform->getHeight();
			(*letters)[i]->render(dest);
		}
	}
}

void RenderSystem::drawText() {
	vector<ecs::Entity*> texts = mngr_->getEntities(ecs::_grp_TEXT);
	for (auto text : texts) {
		if (mngr_->isActive(text)) {
			Texture* texture = text->getComponent<Image>()->getTexture();
			SDL_Rect rect = text->getComponent<Transform>()->getRect();
			texture->render(rect);
		}
	}
}

void RenderSystem::addText() {
	ecs::stateId id = currentState->getStateID();

	switch (id) {
	case ecs::_s_PAUSE:
		createText(Vector2D(sdl->width() / 2 - BIG_WIDTH / 2, sdl->height() / 2 - BIG_HEIGHT / 2), BIG_WIDTH, BIG_HEIGHT, "PressSpace");
		break;
	case ecs::_s_NAME:
		createText(Vector2D(sdl->width() / 2 - BIG_WIDTH / 2, sdl->height() / 2 - BIG_HEIGHT / 2 + INTRODUCE_OFFSET), BIG_WIDTH, BIG_HEIGHT, "Introduce");
		createText(Vector2D(sdl->width() / 2 - PRESS_SPACE_WIDTH / 2, sdl->height() + PRESS_SPACE_OFFSET), PRESS_SPACE_WIDTH, PRESS_SPACE_HEIGHT, "PressSpace");
		break;
	case ecs::_s_WIN:
		createText(Vector2D(sdl->width() / 2 - FINISH_WIDTH / 2, sdl->height() / 2 - FINIHS_HEIGHT / 2), FINISH_WIDTH, FINIHS_HEIGHT, "Win");
		createText(Vector2D(sdl->width() / 2 - PRESS_SPACE_WIDTH / 2, sdl->height() + PRESS_SPACE_OFFSET), PRESS_SPACE_WIDTH, PRESS_SPACE_HEIGHT, "PressSpace");
		break;
	case ecs::_s_GAMEOVER:
		createText(Vector2D(sdl->width() / 2 - FINISH_WIDTH / 2, sdl->height() / 2 - FINIHS_HEIGHT / 2), FINISH_WIDTH, FINIHS_HEIGHT, "Gameover");
		createText(Vector2D(sdl->width() / 2 - PRESS_SPACE_WIDTH / 2, sdl->height() + PRESS_SPACE_OFFSET), PRESS_SPACE_WIDTH, PRESS_SPACE_HEIGHT, "PressSpace");
		break;
	case ecs::_s_MULTIPLAYER:
		ecs::gameStateId gId = currentState->getGameStateID();
		waiting = createText(Vector2D(sdl->width() / 2 - BIG_WIDTH / 2, sdl->height() / 2 - BIG_HEIGHT / 2), BIG_WIDTH, BIG_HEIGHT, "Waiting");
		break;
	}

	ecs::gameStateId gId = currentState->getGameStateID();
}

ecs::Entity* RenderSystem::createText(Vector2D pos, float width, float height, string msg)
{
	ecs::Entity* text = mngr_->addEntity(ecs::_grp_TEXT);
	mngr_->addComponent<Transform>(text, pos, width, height);
	mngr_->addComponent<Image>(text, &sdl->msgs().at(msg));
	return text;
}

void RenderSystem::initSystem() {
	fighter = mngr_->getHandler(ecs::FIGHTER);
	fighter2 = mngr_->getHandler(ecs::FIGHTER2);
	name = mngr_->getHandler(ecs::NAME);
	/*grp_FIGHTERS = mngr_->getGroup(ecs::_grp_FIGHTER);*/
	addText();
}

void RenderSystem::receive(const ecs::Message& m)
{
	switch (m.id)
	{
	case ecs::_m_GAMEOVER:
		onCollisionFighterBullet(m.gameover_data.winner);
		break;
	case ecs::_m_CONNECTION_LOST:
		mngr_->setActive(waiting, true);
		break;
	case ecs::_m_ONLINE_GAME_START:
		mngr_->setActive(waiting, false);
		break;
	default:
		break;
	}
}

void RenderSystem::update(float frameTime) {
	switch (currentState->getStateID()) {
	case ecs::_s_PLAY:
		drawAsteroids(frameTime);
		drawBullets();
		drawFighter();
		drawFighterHealth();
		break;

	case ecs::_s_MAIN_MENU:
		drawButtons();
		break;

	case ecs::_s_CONNECT:
		drawButtons();
		drawText();
		break;
	case ecs::_s_MULTIPLAYER:
		drawBullets();
		drawFighter2();
		drawFighterName(mngr_->getHandler(ecs::FIGHTER));
		drawFighterName(mngr_->getHandler(ecs::FIGHTER2));
		drawFighterHealth();
		drawFighterHealth2();

		drawText();
		break;
	case ecs::_s_PAUSE:
		drawFighterHealth();
		drawText();
		break;

	case ecs::_s_NAME:
		drawText();
		drawName();
		break;

	case ecs::_s_WIN:
	case ecs::_s_GAMEOVER:
		drawText();
		break;
	}
}
