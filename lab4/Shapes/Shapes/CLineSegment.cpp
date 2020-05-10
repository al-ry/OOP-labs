#include "stdafx.h"
#include "CPoint.h"
#include "CLineSegment.h"

CLineSegment::CLineSegment(const CPoint& start, const CPoint& end, uint32_t color)
	: CShape("Line segment", color)
	, m_startPoint(start)
	, m_endPoint(end)
{
}
double CLineSegment::GetArea() const
{
	return 0.0;
}
double CLineSegment::GetPerimeter() const
{
	return sqrt(pow((m_endPoint.x - m_startPoint.x), 2) + pow((m_endPoint.y - m_startPoint.y), 2));
}
CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}
CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}
void CLineSegment::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(GetStartPoint(), GetEndPoint(), GetOutlineColor());
}
void CLineSegment::AppendProperties(std::ostream& strm) const 
{
	strm << "\tStart point = " << GetStartPoint().ToString() << std::endl
		 << "\tEnd point = " << GetEndPoint().ToString() << std::endl;
}




