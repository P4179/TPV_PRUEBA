#pragma once

#include "../utils/Vector2D.h"
#include "../ecs/Component.h"
#include "../game/ecs_def.h"
#include "../utils/checkML.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"

using namespace std;

struct Name : public ecs::Component {
private:
	Vector2D offset;
	float width;
	float height;
	Font* font;
	Texture* texture;
	SDLUtils* sdl;

public:
	constexpr static ecs::cmpId id = ecs::_NAME;

	Name(Vector2D offset, float width, float height, string name = " ")
		: offset(offset), width(width), height(height) {
		sdl = SDLUtils::instance();
		font = &sdl->fonts().at("ARIAL48");

		texture = new Texture(sdl->renderer(), name, *font, build_sdlcolor(0x000000ff));
	}

	virtual ~Name() {
		delete texture;
	}

	inline Texture* getName() const {
		return texture;
	}

	inline void setName(string newName) {
		if (newName != "") {
			delete texture;
			texture = new Texture(sdl->renderer(), newName, *font, build_sdlcolor(0x000000ff));
		}
	}

	inline Vector2D getOffset() const {
		return offset;
	}

	inline float getWidth() const {
		return width;
	}

	inline float getHeight() const {
		return height;
	}
};