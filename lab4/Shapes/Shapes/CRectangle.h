#pragma once
#include "CSolidShape.h"

class CRectangle final : public CSolidShape
{
public:
	CRectangle(const CPoint& leftTopPos, double width, double height, uint32_t outlineColor, uint32_t fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;

	double GetWidth() const;
	double GetHeight() const;
	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;

	void Draw(ICanvas& canvas) const;

protected:
	void AppendProperties(std::ostream& strm) const override;

private:
	double m_width;
	double m_height;
	CPoint m_leftTop;
};
