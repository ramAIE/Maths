#include "Player.h"
#include <Texture.h>
#include <Renderer2D.h>
#include <Input.h>
#include <Vector3.h>
#include <GenLib.h>
#include <math.h>
#include <Application.h>
Player::Player()
{
	m_texture = new aie::Texture("../bin/textures/ship.png");
	m_position = Vector2(100, 200);
	m_local = m_local.createTranslation(m_position.m_x, m_position.m_y, 1);
	m_rotationSpeed = DegtoRad(90.0f);
	m_speed = 50.0f;
	m_velocity = Vector2(0, 0);
	m_acceleration = Vector2(0, 0);
	m_rotation = 0.0f;
}

void Player::update(float deltaTime, aie::Input * input)
{
	Vector2 rotation(cosf(m_rotation), sinf(m_rotation));
	Vector2 force = Vector2((0 * rotation.m_x) - (m_position.m_y * rotation.m_y),
							(0 * rotation.m_y) + (m_position.m_y * rotation.m_x));

	if (input->isKeyDown(aie::INPUT_KEY_W))
	{
		MoveForward(m_speed * deltaTime);
		//m_acceleration = Vector2(0, 0);
		AddForce(force);
	}
	if (input->isKeyDown(aie::INPUT_KEY_A))
	{
		TurnLeft(m_rotationSpeed * deltaTime);
	}
	if (input->isKeyDown(aie::INPUT_KEY_S))
	{
		MoveBackward(m_speed * deltaTime);
	}
	if (input->isKeyDown(aie::INPUT_KEY_D))
	{
		TurnRight(m_rotationSpeed * deltaTime);
	}
	AddForce(m_velocity * -1.00f);
	m_velocity = m_velocity + m_acceleration * deltaTime;
	m_position = m_position + m_velocity * deltaTime;
	m_acceleration = Vector2(0, 0);
	Matrix3 mTrans = Matrix3::createTranslation(m_position.m_x, m_position.m_y, 1);
	Matrix3 mRot = Matrix3::createRotation(m_rotation);
	Matrix3 mScale = Matrix3::createScale(1, 1);
	m_local = mTrans * mRot * mScale;

	m_world = m_local;
	CalcAABB();
}

void Player::draw(aie::Renderer2D * renderer, aie::Application* app)
{	
	//float t = fmod(app->getTime(), 3.0f);
	//float f = linearEase(t, 0.0f, 1.0f, 1.0f);

	//renderer->setRenderColour(f, 0, f);
	renderer->drawSpriteTransformed3x3(m_texture, (float*)m_world);
	renderer->drawLine(m_AABB.min.m_x, m_AABB.min.m_y, m_AABB.min.m_x, m_AABB.max.m_y);
	renderer->drawLine(m_AABB.min.m_x, m_AABB.max.m_y, m_AABB.max.m_x, m_AABB.max.m_y);
	renderer->drawLine(m_AABB.max.m_x, m_AABB.max.m_y, m_AABB.max.m_x, m_AABB.min.m_y);
	renderer->drawLine(m_AABB.max.m_x, m_AABB.min.m_y, m_AABB.min.m_x, m_AABB.min.m_y);

}

void Player::AddForce(Vector2 a_force)
{
	m_acceleration = m_acceleration + a_force;
}

void Player::MoveForward(float a_amount)
{
	Vector3 forward = Vector3(0, a_amount, 1);
	Vector3 pos = m_local * forward;
	m_position = Vector2(pos.m_x, pos.m_y);
}

void Player::TurnLeft(float a_rot)
{
	m_rotation += a_rot;
}

void Player::TurnRight(float a_rot)
{
	m_rotation -= a_rot;
}

void Player::MoveBackward(float a_amount)
{
	Vector3 backward = Vector3(0, -a_amount, 1);
	Vector3 pos = m_local * backward;
	m_position = Vector2(pos.m_x, pos.m_y);
}

float Player::linearEase(float t, float b, float c, float d)
{
	return b + c * (t / d);
}


void Player::CalcAABB()
{
	Matrix3 m = m_local;
	int w = m_texture->getWidth();
	int h = m_texture->getHeight();

	Vector3 v[4] = { Vector3((-w / 2), -(h / 2), 1),
					Vector3((-w / 2), (h / 2), 1),
					Vector3((w / 2), (h / 2), 1),
					Vector3((w / 2), -(h / 2), 1) };

	m_AABB.min = Vector2(INT16_MAX, INT16_MAX);
	m_AABB.max = Vector2(INT16_MIN, INT16_MIN);

	for (int i = 0; i < 4; ++i)
	{
		v[i] = m * v[i];
		if (v[i].m_x < m_AABB.min.m_x)
			m_AABB.min.m_x = v[i].m_x;
		if (v[i].m_y < m_AABB.min.m_y)
			m_AABB.min.m_y = v[i].m_y;

		if (v[i].m_x > m_AABB.max.m_x)
			m_AABB.max.m_x = v[i].m_x;
		if (v[i].m_y > m_AABB.max.m_y)
			m_AABB.max.m_y = v[i].m_y;
	}

}


Player::~Player()
{
	delete m_texture;
}
