#pragma once
#include <Matrix3.h>
#include <Vector2.h>
namespace aie
{
	class Renderer2D;
	class Texture;
	class Input;
	class Application;
}
struct AABB
{
	Vector2 min;
	Vector2 max;
};
class Player
{
public:

	Player();
	void update(float deltaTime, aie::Input* input);
	void draw(aie::Renderer2D* renderer, aie::Application* app);
	void AddForce(Vector2 a_force);
	void MoveForward(float a_amount);
	void TurnLeft(float a_rot);
	void TurnRight(float a_rot);
	void MoveBackward(float a_amount);
	float linearEase(float t, float b, float c, float d);
	void CalcAABB();
	

	~Player();
private:
	aie::Texture*	m_texture;
	Vector2			m_position;
	Vector2			m_velocity;
	Vector2			m_acceleration;
	float			m_rotation;
	float			m_rotationSpeed;
	float			m_speed;
	Matrix3			m_local;
	Matrix3			m_world;
	AABB			m_AABB;
};

