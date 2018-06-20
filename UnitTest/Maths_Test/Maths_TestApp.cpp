#include "Maths_TestApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Player.h"
#include "Box.h"
#include "Ball.h"

Maths_TestApp::Maths_TestApp() {

}

Maths_TestApp::~Maths_TestApp() {

}

bool Maths_TestApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	m_player = new Player();
	m_box = new Box();
	m_ball = new Ball();
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);
	m_collided = false;

	return true;
}

void Maths_TestApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	delete m_player;
}

void Maths_TestApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	m_player->update(deltaTime, input);
	m_box->update(deltaTime, input);
	m_ball->update(deltaTime, input);

	if (CollisionCheck(m_box->GetAABBMin(), m_box->GetAABBMax(), m_ball->GetSphereCenter(), m_ball->GetSphereRadius()) && !m_collided)
	{
		m_collided = true;
		//Vector2 n = m_box->GetAABBMax() - m_box->GetAABBMin();
		//n.normalise();
		//Vector2 normal = Vector2(0, 0);
		//normal.m_x = n.m_x;
		//normal.m_y = -n.m_y;
		//Vector2 newVelocity = m_ball->GetVelocity() - 2 * m_ball->GetVelocity().dot(normal) * normal;
		//m_ball->SetVelocity(newVelocity);
	}
	//if (m_collided)
	//{
	//	Vector2 n = m_box->point4 - m_box->point3;
	//	n.normalise();
	//	Vector2 normal = Vector2(0, 0);
	//	normal.m_x = n.m_x;
	//	normal.m_y = -n.m_y;
	//	Vector2 newVelocity = m_ball->GetVelocity() - 2 * m_ball->GetVelocity().dot(normal) * normal;
	//	m_ball->SetVelocity(newVelocity);
	//	m_collided = false;
	//}

	if (m_ball->m_position.m_y <= 0)
	{
		Vector2 n = Vector2(getWindowWidth(), 0) - Vector2(0, 0);
		n.normalise();
		Vector2 normal = Vector2(0, 0);
		normal.m_x = n.m_y;
		normal.m_y = -n.m_x;
		Vector2 newVelocity = m_ball->GetVelocity() - (2 * m_ball->GetVelocity().dot(normal) * normal);
		m_ball->SetVelocity(newVelocity);
	}
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Maths_TestApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	m_player->draw(m_2dRenderer, this);
	m_box->draw(m_2dRenderer);
	m_ball->draw(m_2dRenderer);
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}

bool Maths_TestApp::CollisionCheck(Vector2 AABBmin, Vector2 AABBmax, Vector2 sphereCenter, double sphereRad)
{
	Vector2 closesPoint = clamp(sphereCenter, AABBmin, AABBmax);
	Vector2 diff = sphereCenter - closesPoint;
	return diff.dot(diff) <= (sphereRad * sphereRad);
}

