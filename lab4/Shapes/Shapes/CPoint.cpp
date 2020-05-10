#include "stdafx.h"
#include "CPoint.h"

CPoint::CPoint(double x, double y)
{
	this->x = x;
	this->y = y;
}
CPoint::CPoint()
{
	this->x = 0;
	this->y = 0;
}

std::string CPoint::ToString() const
{
	std::stringstream strs;
	strs << std::fixed << std::setprecision(3);
	strs << "(" << x << ", " << y << ")";
	return strs.str();
}

bool CPoint::operator==(const CPoint& point) const
{
	return ((x == point.x) && (y == point.y));
}

bool CPoint::operator!=(const CPoint& point) const
{
	return !(*this == point);
}
