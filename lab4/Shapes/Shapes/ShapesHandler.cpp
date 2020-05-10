#include "stdafx.h"
#include "CPoint.h"
#include "ICanvas.h"
#include "IShape.h"
#include "ShapesHandler.h"
#include "CLineSegment.h"
#include "CCircle.h"
#include "CRectangle.h"
#include "CTriangle.h"

#include "CCanvas.h"
#include "GLFW/glfw3.h"

ShapesHandler::ShapesHandler(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({ { "line", bind(&ShapesHandler::MakeLineSegment, this, std::placeholders::_1) },
		  { "circle", bind(&ShapesHandler::MakeCircle, this, std::placeholders::_1) },
		  { "rectangle", bind(&ShapesHandler::MakeRectangle, this, std::placeholders::_1) },
		  { "triangle", bind(&ShapesHandler::MakeTriangle, this, std::placeholders::_1) } })
{
}

bool ShapesHandler::HandleCommand()
{
	std::string commandLine;
	getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}
	return false;
}

bool ShapesHandler::MakeLineSegment(std::istream& args)
{
	CPoint start;
	CPoint end;
	args >> start.x;
	args >> start.y;

	args >> end.x;
	args >> end.y;

	uint32_t color;
	args >>  std::hex >> std::setw(6) >> std::setfill('0') >> color;

	m_shapesList.push_back(std::make_shared<CLineSegment>(start, end, color));
	return true;
}

bool ShapesHandler::MakeCircle(std::istream& args)
{
	CPoint center;
	args >> center.x;
	args >> center.y;

	double radius;
	args >> radius;

	uint32_t outlineColor;
	args >> std::hex >> std::setw(6) >> std::setfill('0') >> outlineColor;

	uint32_t fillColor;
	args >> std::hex >> std::setw(6) >> std::setfill('0') >> fillColor;

	m_shapesList.push_back(std::make_shared<CCircle>(center, radius, outlineColor, fillColor));
	return true;
}

bool ShapesHandler::MakeRectangle(std::istream& args)
{
	CPoint leftTop;
	args >> leftTop.x;
	args >> leftTop.y;

	double width;
	args >> width;

	double height;
	args >> height;

	uint32_t outlineColor;
	args >> std::hex >> std::setw(6) >> std::setfill('0') >> outlineColor;

	uint32_t fillColor;
	args >> std::hex >> std::setw(6) >> std::setfill('0') >> fillColor;

	m_shapesList.push_back(std::make_shared<CRectangle>(leftTop, width, height, outlineColor, fillColor));
	return true;
}

bool ShapesHandler::MakeTriangle(std::istream& args)
{
	CPoint vertex1;
	CPoint vertex2;
	CPoint vertex3;

	args >> vertex1.x;
	args >> vertex1.y;

	args >> vertex2.x;
	args >> vertex2.y;

	args >> vertex3.x;
	args >> vertex3.y;

	uint32_t outlineColor;
	args >> std::hex >> std::setw(6) >> std::setfill('0') >> outlineColor;

	uint32_t fillColor;
	args >> std::hex >> std::setw(6) >> std::setfill('0') >> fillColor;

	m_shapesList.push_back(std::make_shared<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor));
	return true;
}

std::vector<std::shared_ptr<IShape>> ShapesHandler::GetShapes() const
{
	return m_shapesList;
}

std::shared_ptr<IShape> ShapesHandler::FindMaxArea() const
{
	auto maxElement = std::max_element(m_shapesList.begin(), m_shapesList.end()
		, [](std::shared_ptr<IShape> shape1, std::shared_ptr<IShape> shape2) {
		return shape1->GetArea() < shape2->GetArea();
	});
	return *maxElement;
}

std::shared_ptr<IShape> ShapesHandler::FindMinPerimeter() const
{
	auto minElement = std::min_element(m_shapesList.begin(), m_shapesList.end(), [](std::shared_ptr<IShape> shape1, std::shared_ptr<IShape> shape2) {
		return shape1->GetPerimeter() < shape2->GetPerimeter();
	});
	return *minElement;
}

void ShapesHandler::DrawShapes() const
{
	GLFWwindow* window{};
	CCanvas canvas(window);
	if (!glfwInit())
		return;

	window = glfwCreateWindow(640, 640, "Shapes", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window))
	{

		glClear(GL_COLOR_BUFFER_BIT);

		for (auto& shape : m_shapesList)
		{
			shape->Draw(canvas);
		}
		glfwSwapBuffers(window);

		glfwPollEvents();	
	}

	glfwTerminate();
}

