#pragma once

#include "CPoint.h"
#include <cstdint>
#include <vector>
class ICanvas
{
public:

	virtual void DrawLine(const CPoint& from,const CPoint& to, uint32_t lineColor) = 0;
	virtual void FillPolygon(std::vector<CPoint> vertices, uint32_t fillColor) = 0;
	virtual void DrawCircle(const CPoint& center, double radius, uint32_t outlineColor) = 0;
	virtual void FillCircle(const CPoint& center, double radius, uint32_t fillColor) = 0;
};