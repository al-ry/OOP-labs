#pragma once
#include <string>

class IPerson
{
public:
	virtual std::string GetName() const = 0;
	virtual std::string GetSurname() const = 0;
	virtual std::string GetPatronymic() const = 0;
	virtual std::string GetAddress() const = 0;


	virtual void SetName(const std::string &name) = 0;
	virtual void SetSurname(const std::string& surname) = 0;
	virtual void SetPatronymic(const std::string& patronymic) = 0;
	virtual void SetAddress(const std::string& address) = 0;

	virtual ~IPerson(){};
};
