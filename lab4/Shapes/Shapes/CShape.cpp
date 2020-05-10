#include "stdafx.h"
#include "IShape.h"
#include "CShape.h"


CShape::CShape(const std::string& type, uint32_t outlineColor)
	: m_shapeType(type)
	, m_outlineColor(outlineColor)
{
}

std::string CShape::ToString() const
{
	std::ostringstream strm;
	strm << m_shapeType << ":" << std::endl
		 << std::setprecision(10)
		 << "\tArea = " << GetArea() << std::endl
		 << "\tPerimeter = " << GetPerimeter() << std::endl
		 << "\tOutline color = " << std::hex << std::setw(6) << std::setfill('0') << GetOutlineColor() <<
	std::endl;
	AppendProperties(strm);
	return strm.str();
}

std::uint32_t CShape::GetOutlineColor() const
{
	return m_outlineColor;
}


