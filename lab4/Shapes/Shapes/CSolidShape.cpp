#include "stdafx.h"
#include "CSolidShape.h"

CSolidShape::CSolidShape(const std::string& type, uint32_t outlineColor, uint32_t fillColor)
	: CShape(type, outlineColor)
	, m_fillColor(fillColor)
{
}


uint32_t CSolidShape::GetFillColor() const
{
	return m_fillColor;
};
