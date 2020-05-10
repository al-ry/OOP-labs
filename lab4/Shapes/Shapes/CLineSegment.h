#pragma once

#include "CShape.h"

class CLineSegment final : public CShape
{
public:
	CLineSegment(const CPoint& start, const CPoint& end, uint32_t color);
	double GetArea() const override;
	double GetPerimeter() const override;

	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
	void Draw(ICanvas& canvas) const;
protected:
	void AppendProperties(std::ostream& strm) const override;

private:
	CPoint m_startPoint;
	CPoint m_endPoint;
};