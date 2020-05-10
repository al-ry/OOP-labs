#include "stdafx.h"
#include "CPoint.h"
#include "CTriangle.h"

CTriangle::CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3
	, uint32_t outlineColor, uint32_t fillColor)
	: CSolidShape("Triangle", outlineColor, fillColor)
	, m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, m_line1(vertex1, vertex2, 0)
	, m_line2(vertex2, vertex3, 0)
	, m_line3(vertex3, vertex1, 0)
{
}

double CTriangle::GetArea() const
{

	double semiPerimeter = (m_line1.GetPerimeter() + m_line2.GetPerimeter() + m_line3.GetPerimeter()) / 2;

	return sqrt(semiPerimeter * (semiPerimeter - m_line1.GetPerimeter()) * (semiPerimeter - m_line2.GetPerimeter()) * (semiPerimeter - m_line3.GetPerimeter()));
}

double CTriangle::GetPerimeter() const
{
	return (m_line1.GetPerimeter() + m_line2.GetPerimeter() + m_line3.GetPerimeter());
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

void CTriangle::Draw(ICanvas& canvas) const
{
	std::vector<CPoint> triangleVertices = {
		GetVertex1(),
		GetVertex2(),
		GetVertex3()
	};
	canvas.DrawLine(GetVertex1(), GetVertex2(), GetOutlineColor());
	canvas.DrawLine(GetVertex2(), GetVertex3(), GetOutlineColor());
	canvas.DrawLine(GetVertex3(), GetVertex1(), GetOutlineColor());
	canvas.FillPolygon(triangleVertices, GetFillColor());
}

void CTriangle::AppendProperties(std::ostream& strm) const
{
	strm << "\tFill color = " << std::hex << std::setw(6) << std::setfill('0') << GetFillColor() << std::endl
		 << "\tVertex 1 = " << GetVertex1().ToString() << std::endl
		 << "\tVertex 2 = " << GetVertex2().ToString() << std::endl
		 << "\tVertex 3 = " << GetVertex3().ToString() << std::endl;
}
