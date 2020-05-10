#pragma once
#include <string>

class CPoint final
{
public:
	CPoint(double x, double y);
	CPoint();
	std::string ToString() const;
	double x = 0;
	double y = 0;

	bool operator==(const CPoint& point)const;
	bool operator!=(const CPoint& point) const;
};
