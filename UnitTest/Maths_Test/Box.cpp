#include "Box.h"
#include <Renderer2D.h>
#include <Input.h>
#include <Texture.h>


Box::Box()
{
	m_texture = new aie::Texture("../bin/textures/barrelBeige1.png");
	m_rotation = 3.14f/2.0f;
	m_position = Vector2(100, 200);
}

void Box::update(float deltaTime, aie::Input * input)
{
	if (input->isKeyDown(aie::INPUT_KEY_UP))
	{
		m_position.m_y += 100.0f * deltaTime;
	}
	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
	{
		m_position.m_y -= 100.0f * deltaTime;
	}
	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	{
		m_position.m_x -= 100.0f * deltaTime;
	}
	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
	{
		m_position.m_x += 100.0f * deltaTime;
	}
	CalcAABB();
}

void Box::draw(aie::Renderer2D * renderer)
{
	renderer->drawSprite(m_texture, m_position.m_x, m_position.m_y);
	renderer->drawLine(m_AABB.min.m_x, m_AABB.min.m_y, m_AABB.min.m_x, m_AABB.max.m_y);
	renderer->drawLine(m_AABB.min.m_x, m_AABB.max.m_y, m_AABB.max.m_x, m_AABB.max.m_y);
	renderer->drawLine(m_AABB.max.m_x, m_AABB.max.m_y, m_AABB.max.m_x, m_AABB.min.m_y);
	renderer->drawLine(m_AABB.max.m_x, m_AABB.min.m_y, m_AABB.min.m_x, m_AABB.min.m_y);
}

void Box::CalcAABB()
{
	int w = m_texture->getWidth();
	int h = m_texture->getHeight();

	Vector2 v[4] = { Vector2((-w / 2), -(h / 2)),
		Vector2((-w / 2), (h / 2)),
		Vector2((w / 2), (h / 2)),
		Vector2((w / 2), -(h / 2)) };

	point1 = v[0];
	point2 = v[1];
	point3 = v[2];
	point4 = v[3];

	m_AABB.min = Vector2(INT16_MAX, INT16_MAX);
	m_AABB.max = Vector2(INT16_MIN, INT16_MIN);

	for (int i = 0; i < 4; ++i)
	{
		v[i] = m_position + v[i];
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

Vector2 Box::GetAABBMax()
{
	return m_AABB.max;
}

Vector2 Box::GetAABBMin()
{
	return m_AABB.min;
}


Box::~Box()
{
}
