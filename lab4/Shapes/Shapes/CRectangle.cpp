#include "stdafx.h"
#include "CPoint.h"
#include "CRectangle.h"

CRectangle::CRectangle(const CPoint& leftTopPos, double width, double height, uint32_t outlineColor, uint32_t fillColor)
	: CSolidShape("Rectangle", outlineColor, fillColor)
	, m_width(width)
	, m_height(height)
	, m_leftTop(leftTopPos)

{
}

double CRectangle::GetArea() const
{
	return (m_height * m_width);
}

double CRectangle::GetPerimeter() const
{
	return ((m_height + m_width) * 2);
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
	return CPoint(m_width + m_leftTop.x, m_leftTop.y - m_height);
}

void CRectangle::Draw(ICanvas& canvas) const
{
	CPoint rightTop = { GetLeftTop().x + GetWidth(), GetLeftTop().y};
	CPoint leftBottom = { GetLeftTop().x, GetLeftTop().y - m_height };
	std::vector<CPoint> vertices = {
		GetLeftTop(),
		rightTop,
		GetRightBottom(),
		leftBottom,
	};
	canvas.DrawLine(GetLeftTop(), rightTop, GetOutlineColor());
	canvas.DrawLine(rightTop, GetRightBottom(), GetOutlineColor());
	canvas.DrawLine(GetRightBottom(), leftBottom, GetOutlineColor());
	canvas.DrawLine(leftBottom, GetLeftTop(), GetOutlineColor());
	canvas.FillPolygon(vertices, GetFillColor());
}

void CRectangle::AppendProperties(std::ostream& strm) const
{
	strm << "\tFill color = " << std::hex << std::setw(6) << std::setfill('0') << GetFillColor() << std::endl
		 << "\tHeight = " << GetHeight() << std::endl
		 << "\tWidth = " << GetWidth() << std::endl
		 << "\tLeft top position = " << GetLeftTop().ToString() << std::endl
		 << "\tRight bottom position = " << GetRightBottom().ToString() << std::endl;
}
