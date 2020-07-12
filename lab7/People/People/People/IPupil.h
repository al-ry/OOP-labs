#pragma once
#include "IPerson.h"
#include <string>

class IPupil: public IPerson
{
public:
	virtual std::string GetSchoolName() const = 0;
	virtual std::string GetGrade() const = 0;

	virtual void SetSchoolName(const std::string& schoolName) = 0;
	virtual void SetGrade(const std::string& grade) = 0;
};