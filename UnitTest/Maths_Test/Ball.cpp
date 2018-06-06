#include "Ball.h"
#include <Texture.h>
#include <Renderer2D.h>
#include <Input.h>


Ball::Ball()
{
	m_texture = new aie::Texture("../bin/textures/ball.png");
	m_position = Vector2(500, 500);
	m_velocity = Vector2(100.0f, -200.8f);
}

void Ball::update(float deltaTime, aie::Input * input)
{
	CalcSphere();
	m_position = m_position + m_velocity * deltaTime;
}

void Ball::draw(aie::Renderer2D * renderer)
{
	renderer->drawSprite(m_texture, m_position.m_x, m_position.m_y);
	//renderer->drawCircle(m_sphere.center.m_x, m_sphere.center.m_y, m_sphere.radius);
}

void Ball::CalcSphere()
{
	m_sphere.center.m_x = (float)m_texture->getWidth() / 2.0f;
	m_sphere.center.m_y = (float)m_texture->getHeight() / 2.0f;
	m_sphere.radius = 22.0f;
	m_sphere.center = m_position;
}

void Ball::SetVelocity(Vector2 velocity)
{
	m_velocity = velocity;
}

Vector2 Ball::GetVelocity()
{
	return m_velocity;
}

Vector2 Ball::GetSphereCenter()
{
	return m_sphere.center;
}

float Ball::GetSphereRadius()
{
	return m_sphere.radius;
}



Ball::~Ball()
{
}
