#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <Vector2.h>

class Player;
class Box;
class Ball;


class Maths_TestApp : public aie::Application {
public:

	Maths_TestApp();
	virtual ~Maths_TestApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	bool CollisionCheck(Vector2 AABBmin, Vector2 AABBmax, Vector2 sphereCenter, double sphereRad);

	inline float min(float a, float b) { return a < b ? a : b; }
	inline float max(float a, float b) { return a > b ? a : b; }

	inline Vector2 min(const Vector2& a, const Vector2& b) {
		return { min(a.m_x, b.m_x), min(a.m_y, b.m_y) };
	}

	inline Vector2 max(const Vector2& a, const Vector2& b) {
		return { max(a.m_x, b.m_x), max(a.m_y, b.m_y) };
	}

	inline Vector2 clamp(const Vector2& t, const Vector2& a, const Vector2& b) {
		return max(a, min(b, t));
	}


protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	Player*				m_player;
	Box*				m_box;
	Ball*				m_ball;
	bool				m_collided;
};