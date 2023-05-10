#pragma once

#include "../ecs/Component.h"
#include "../utils/checkML.h"
#include <vector>
#include <iostream>
#include "../sdlutils/Texture.h"
#include "../game/ecs_def.h"
#include "../sdlutils/SDLUtils.h"

using namespace std;

struct SeparateLetters : public ecs::Component {
private:
	string text;
	vector<Texture*> letters;
	SDLUtils* sdl;

public:
	constexpr static ecs::cmpId id = ecs::_SEPARATE_LETTERS;

	SeparateLetters() : text(), letters(), sdl(SDLUtils::instance()) { }

	virtual ~SeparateLetters() {
		for (auto letter : letters) {
			delete letter;
		}
	}

	void newLetter(string letter) {
		if (text.length() < 10) {
			text += letter;
			Texture* texture = new Texture(sdl->renderer(), letter, sdl->fonts().at("ARIAL48"),
				build_sdlcolor(0x000000ff));
			letters.push_back(texture);
		}
	}

	void deleteLastLetter() {
		if (text.length() > 0) {
			text.pop_back();

			delete letters.back();
			letters.pop_back();
		}
	}

	inline string getText() {
		return text;
	}

	inline vector<Texture*>* getLetters() {
		return &letters;
	}
};