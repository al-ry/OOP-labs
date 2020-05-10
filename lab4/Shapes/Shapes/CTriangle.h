#pragma once
#include "CSolidShape.h"
#include "CLineSegment.h"

class CTriangle : public CSolidShape
{
public:
	CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3
		, uint32_t outlineColor, uint32_t fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;

	CPoint GetVertex1() const;
	CPoint GetVertex2() const; 
	CPoint GetVertex3() const;

	void Draw(ICanvas& canvas) const;
protected:
	void AppendProperties(std::ostream& strm) const override;

private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
	CLineSegment m_line1;
	CLineSegment m_line2;
	CLineSegment m_line3;
};
