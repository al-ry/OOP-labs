#pragma once
#include "IPerson.h"

class IWorker : public IPerson
{
public:
	virtual void SetSpecialization(const std::string& specialization) = 0;
	virtual std::string GetSpecialization() const = 0;
};