#pragma once
#include "IShape.h"

typedef std::vector<std::string> ShapeInfo;

class ShapesHandler
{
public:
	ShapesHandler(std::istream& input, std::ostream& output);
	bool HandleCommand();
	std::vector<std::shared_ptr<IShape>> GetShapes() const;
	std::shared_ptr<IShape> FindMaxArea() const;
	std::shared_ptr<IShape> FindMinPerimeter() const;
	void DrawShapes() const;

private:
	bool MakeLineSegment(std::istream& args);
	bool MakeCircle(std::istream& args);
	bool MakeRectangle(std::istream& args);
	bool MakeTriangle(std::istream& args); 

private:
	using Handler = std::function<bool(std::istream& args)>;

	using ActionMap = std::map<std::string, Handler>;

	std::istream& m_input;
	std::ostream& m_output;

	std::vector<std::shared_ptr<IShape>> m_shapesList;
	const ActionMap m_actionMap;
};