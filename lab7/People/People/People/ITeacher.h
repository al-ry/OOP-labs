#pragma once
#include "IPerson.h"

class ITeacher: public IPerson
{
public:

	virtual std::string GetSubject() const = 0;
	virtual void SetSubject(const std::string &subject)  = 0;

};