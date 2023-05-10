#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../utils/checkML.h"

// clase que se encarga de renderizar un spritesheet y producir una animación con él
struct FramedImage : public ecs::Component {
private:
	Texture* texture;
	float elapsedTime;
	float timer;
	int row;
	int col;

public:
	constexpr static ecs::cmpId id = ecs::_IMAGE;

	FramedImage(Texture* texture) :
		texture(texture), elapsedTime(0), timer(50), row(0), col(0) { }

	inline Texture* getTexture() const {
		return texture;
	}

	inline float getElapsedTime() const {
		return elapsedTime;
	}

	inline void increaseElapsedTime(float frameTime) {
		elapsedTime += frameTime;
	}

	inline void resetElapsedTime() {
		elapsedTime = 0;
	}

	inline float getTimer() const {
		return timer;
	}

	inline float getRow() const {
		return row;
	}

	inline float getCol() const {
		return col;
	}

	inline void increaseCol() {
		++col;
	}

	inline void increaseRow() {
		++row;
	}

	inline void setCol(int col) {
		this->col = col;
	}

	inline void setRow(int row) {
		this->row = row;
	}
};