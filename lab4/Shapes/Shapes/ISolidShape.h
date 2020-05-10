#pragma once

#include "CShape.h"

class ISolidShape : public virtual IShape
{
public:
	virtual uint32_t GetFillColor() const = 0;

	virtual ~ISolidShape(){};
};