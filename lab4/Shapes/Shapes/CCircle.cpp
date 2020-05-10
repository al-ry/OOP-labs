#include "stdafx.h"
#include "CPoint.h"
#include "CCircle.h"

CCircle::CCircle(const CPoint& center, double radius, uint32_t outlineColor, uint32_t fillColor)
	: CSolidShape("Circle", outlineColor, fillColor)
	, m_center(center)
	, m_radius(radius){};

double CCircle::GetArea() const
{
	return (M_PI * pow(m_radius, 2));
}

double CCircle::GetPerimeter() const
{
	return (2 * M_PI * m_radius);
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

void CCircle::Draw(ICanvas& canvas) const
{
	canvas.DrawCircle(GetCenter(), GetRadius(), GetOutlineColor());
	canvas.FillCircle(GetCenter(), GetRadius(), GetFillColor());
}

void CCircle::AppendProperties(std::ostream& strm) const
{
	strm << "\tFill color = " << std::hex << std::setw(6) << std::setfill('0') << GetFillColor() << std::endl
		 << "\tRadius = " << GetRadius() << std::endl
		 << "\tCenter = " << GetCenter().ToString() << std::endl;
}
