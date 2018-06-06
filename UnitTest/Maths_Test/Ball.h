#pragma once
#include <Vector2.h>
namespace aie
{
	class Renderer2D;
	class Texture;
	class Input;
}
class Ball
{
	struct Sphere
	{
		Vector2 center;
		float radius;
	};
public:
	Ball();
	void update(float deltaTime, aie::Input* input);
	void draw(aie::Renderer2D* renderer);
	void CalcSphere();
	void SetVelocity(Vector2 velocity);
	Vector2 GetVelocity();
	Vector2 GetSphereCenter();
	float GetSphereRadius();
	~Ball();

	Vector2 m_position;
private:
	Sphere m_sphere;
	Vector2 m_velocity;
	aie::Texture* m_texture;
};

