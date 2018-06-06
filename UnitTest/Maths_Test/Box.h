#pragma once
#include <Vector2.h>
namespace aie
{
	class Renderer2D;
	class Texture;
	class Input;
}

class Box
{
	struct AABB
	{
		Vector2 min;
		Vector2 max;
	};

public:
	Box();
	void update(float deltaTime, aie::Input* input);
	void draw(aie::Renderer2D* renderer);
	void CalcAABB();
	Vector2 GetAABBMax();
	Vector2 GetAABBMin();
	~Box();

	Vector2 point1;
	Vector2 point2;
	Vector2 point3;
	Vector2 point4;

private:
	Vector2 m_position;
	aie::Texture* m_texture;
	float m_rotation;
	AABB m_AABB;
};

