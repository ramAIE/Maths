#pragma once

#include "Application.h"
#include "Renderer2D.h"

class Player;

class Maths_TestApp : public aie::Application {
public:

	Maths_TestApp();
	virtual ~Maths_TestApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	Player*				m_player;
};