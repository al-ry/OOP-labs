#pragma once
#include "ISolidShape.h"

class CSolidShape : public ISolidShape, public CShape
{
public:
	CSolidShape(const std::string& type, uint32_t outlineColor, uint32_t fillColor);

	uint32_t GetFillColor() const override;

private:
	uint32_t m_fillColor;
};