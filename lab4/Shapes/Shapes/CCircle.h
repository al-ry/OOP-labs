#pragma once
#include "CSolidShape.h"

class CCircle final : public CSolidShape
{
public:
	CCircle(const CPoint& center, double radius, uint32_t outlineColor, uint32_t fillColor);
	double GetArea() const override;
	double GetPerimeter() const override;

	CPoint GetCenter() const;
	double GetRadius() const;

	void Draw(ICanvas& canvas) const;

protected:
	void AppendProperties(std::ostream& strm) const override;

private:
	double m_radius;
	CPoint m_center;
};