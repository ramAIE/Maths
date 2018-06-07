#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <Vector2.h>
#include <vector>
#include <imgui.h>

class BeizerCurvesApp : public aie::Application {
public:

	BeizerCurvesApp();
	virtual ~BeizerCurvesApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	Vector2 lerp(Vector2 a, Vector2 b, float t);

protected:

	aie::Renderer2D*		m_2dRenderer;
	aie::Font*				m_font;
	std::vector<Vector2>	m_controlPoints;
	std::vector<Vector2>	m_curvePoints;
	float					m_circRadius;
	float					m_lineThickness;
	float					m_scale;
	float					m_scaleSpeed;
	bool					m_bScaleUp;
	bool					m_bSelectedGUI;
};