#pragma once
#include "IShape.h"

class CShape : public virtual IShape
{
public:
	CShape(const std::string& type, uint32_t outlineColor);
	std::string ToString() const override;
	std::uint32_t GetOutlineColor() const override;

protected:
	virtual void AppendProperties(std::ostream& strm) const = 0;

private:
	uint32_t m_outlineColor;
	std::string m_shapeType;
};
