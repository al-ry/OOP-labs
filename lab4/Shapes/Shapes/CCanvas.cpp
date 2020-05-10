#include "stdafx.h"
#include "CCanvas.h"

const double DEG2RAD = M_PI / 180;

CCanvas::CCanvas(GLFWwindow* window)
	: m_window(window)
{
}
void CCanvas::DrawLine(const CPoint& from, const CPoint& to, uint32_t lineColor)
{
	glLineWidth(2);
	RGB rgb = calculateRGBColor(lineColor);
	glColor3d(rgb.red, rgb.green, rgb.blue);

	glBegin(GL_LINES);
	glVertex2d(from.x, from.y);
	glVertex2d(to.x, to.y);
	glEnd();

	glEnable(GL_LINE_SMOOTH);
}

void CCanvas::FillPolygon(std::vector<CPoint> vertices, uint32_t fillColor)
{
	RGB rgb = calculateRGBColor(fillColor);
	glColor3d(rgb.red, rgb.green, rgb.blue);
	glBegin(GL_POLYGON);
	for (auto &vertex : vertices)
	{
		glVertex2d(vertex.x, vertex.y);
	}
	glEnd();
}

void CCanvas::DrawCircle(const CPoint& center, double radius, uint32_t outlineColor)
{
	RGB rgb = calculateRGBColor(outlineColor);
	glColor3d(rgb.red, rgb.green, rgb.blue);
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		double degInRad = i * DEG2RAD;
		glVertex2d((cos(degInRad) * radius) + center.x, (sin(degInRad) * radius) + center.y);
	}
	glEnd();
	glEnable(GL_LINE_SMOOTH);
}

void CCanvas::FillCircle(const CPoint& center, double radius, uint32_t fillColor)
{
	RGB rgb = calculateRGBColor(fillColor);
	glColor3d(rgb.red, rgb.green, rgb.blue);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		double degInRad = i * DEG2RAD;
		glVertex2d((cos(degInRad) * radius) + center.x, (sin(degInRad) * radius) + center.y);
	}
	glEnd();
}

RGB CCanvas::calculateRGBColor(uint32_t hexColor)
{
	RGB rgb;
	rgb.red = ((hexColor >> 16) & 0xff) / 255.0;
	rgb.green = ((hexColor >> 8) & 0xff) / 255.0;
	rgb.blue = ((hexColor) & 0xff) / 255.0;
	return rgb;
}
