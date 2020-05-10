#pragma once

#include "ICanvas.h"
#include "CPoint.h"
#include "GLFW/glfw3.h"

struct RGB
{
	double red;
	double green;
	double blue;
};
class CCanvas: public ICanvas
{
public:

	CCanvas(GLFWwindow* window);

	void DrawLine(const CPoint& from, const CPoint& to, uint32_t lineColor);
	void FillPolygon(std::vector<CPoint> vertices, uint32_t fillColor);
	void DrawCircle(const CPoint& center, double radius, uint32_t outlineColor);
	void FillCircle(const CPoint& center, double radius, uint32_t fillColor);

private:
	RGB calculateRGBColor(uint32_t hexColor);
private:
	GLFWwindow* m_window;
};