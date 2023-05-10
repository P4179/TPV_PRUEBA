#pragma once

#include "../utils/Vector2D.h"
#include "../ecs/Component.h"
#include "../game/ecs_def.h"
#include "../utils/checkML.h"
#include <SDL.h>

struct Transform : public ecs::Component {
private:
	Vector2D position_;
	Vector2D velocity_;
	float width_;
	float height_;
	float rotation_;

public:
	constexpr static ecs::cmpId id = ecs::_TRANSFORM;

	Transform(Vector2D position, float width, float height, Vector2D velocity = Vector2D(0, 0), float rotation = 0)
		: position_(position), velocity_(velocity), width_(width), height_(height), rotation_(rotation) {}

	virtual ~Transform() { };

	inline Vector2D& getPos() {
		return position_;
	}

	inline Vector2D& getVel() {
		return velocity_;
	}

	inline float getWidth() const {
		return width_;
	}

	inline float getHeight() const {
		return height_;
	}

	inline float getRot() const {
		return rotation_;
	}

	inline void setVel(Vector2D newVel) {
		velocity_ = newVel;
	}

	inline void setPos(Vector2D newPos) {
		position_ = newPos;
	}

	inline void setRot(float newRot) {
		rotation_ = newRot;
	}

	inline SDL_Rect getRect() const {
		SDL_Rect rect;
		rect.x = position_.getX();
		rect.y = position_.getY();
		rect.w = width_;
		rect.h = height_;

		return rect;
	}
};