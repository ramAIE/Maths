#include "BeizerCurvesApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

BeizerCurvesApp::BeizerCurvesApp() {

}

BeizerCurvesApp::~BeizerCurvesApp() {

}

bool BeizerCurvesApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_circRadius = 5.0f;
	m_lineThickness = 2.0f;
	m_scale = 0.0f;
	m_bScaleUp = true;
	m_scaleSpeed = 0.1f;
	m_bSelectedGUI = false;

	return true;
}

void BeizerCurvesApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void BeizerCurvesApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();
	Vector2 mousPos;
	mousPos.m_x = (float)input->getMouseX();
	mousPos.m_y = (float)input->getMouseY();

	// Adding points
	if (input->wasMouseButtonPressed(0) && !m_bSelectedGUI)
	{
		m_controlPoints.push_back(mousPos);
		m_curvePoints.clear();
	}

	if (m_bScaleUp)
	{
		m_scale += deltaTime * m_scaleSpeed;
		if (m_scale > 1.0f)
		{
			m_scale = 1.0f;
			m_bScaleUp = false;
			m_curvePoints.clear();
		}
	}
	else
	{
		m_scale -= deltaTime * m_scaleSpeed;
		if (m_scale <= 0)
		{
			m_scale = 0.0f;
			m_bScaleUp = true;
			m_curvePoints.clear();
		}
	}


	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void BeizerCurvesApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	for (auto p : m_controlPoints)
	{
		m_2dRenderer->setRenderColour(1.0f, 0.0f, 0.0f);
		m_2dRenderer->drawCircle(p.m_x, p.m_y, m_circRadius);
	}


	std::vector<Vector2> lerpPoints;
	// lerping through the points
	if (m_controlPoints.size() >= 3)
	{
		lerpPoints = m_controlPoints;
		std::vector<Vector2> newLerpPoints;
		for (int i = 0; i < m_controlPoints.size() - 1; ++i)
		{
			for (int i = 0; i < lerpPoints.size() - 1; ++i)
			{
				Vector2 newPos = lerp(lerpPoints[i], lerpPoints[i + 1], m_scale);
				newLerpPoints.push_back(newPos);
				m_2dRenderer->setRenderColour(0.0f, 1.0f, 0.5f);
				m_2dRenderer->drawLine(lerpPoints[i].m_x, lerpPoints[i].m_y, lerpPoints[i + 1].m_x, lerpPoints[i + 1].m_y, m_lineThickness);
			}
			lerpPoints = newLerpPoints;
			newLerpPoints.clear();
		}
	}

	if (m_controlPoints.size() >= 3)
	{
		m_curvePoints.push_back(lerpPoints[0]);
		for (int i = 0; i < m_curvePoints.size() - 1; ++i)
		{
			m_2dRenderer->setRenderColour(1.0f, 0.5f, 0.0f);
			m_2dRenderer->drawLine(m_curvePoints[i].m_x, m_curvePoints[i].m_y, m_curvePoints[i + 1].m_x, m_curvePoints[i + 1].m_y, m_lineThickness);
		}
	}

	m_2dRenderer->setRenderColour(1.0f, 1.0f, 1.0f);
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	
	ImGui::GetStyle();

	ImGui::Begin(" ", false, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	ImGui::PushItemWidth(200);
	if (ImGui::IsItemHovered())
	{
		m_bSelectedGUI = true;
	}
	else
	{
		m_bSelectedGUI = false;
	}
	ImGui::SliderFloat("Scale Speed", &m_scaleSpeed, 0.1f, 2.0f, "%.3f", 0.5f);
	ImGui::End();

	// done drawing sprites
	m_2dRenderer->end();
}

Vector2 BeizerCurvesApp::lerp(Vector2 a, Vector2 b, float t)
{
	return a * (1 - t) + b * t;
}
