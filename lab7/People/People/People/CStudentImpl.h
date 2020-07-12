#pragma once

#include "CPersonImpl.h"

template <typename Base>
class CStudentImpl : public CPersonImpl<Base>
{
public:
	CStudentImpl() = default;
	CStudentImpl(const std::string& name,
		const std::string& surname,
		const std::string& patronymic,
		const std::string& address,
		const std::string& universityName,
		const std::string& studentCardNumber)
		: CPersonImpl<Base>(name, surname, patronymic, address)
		, m_cardNumber(studentCardNumber)
		, m_universityName(universityName)
	{
	}
	std::string GetUniversityName() const override
	{
		return m_universityName;
	}
	std::string GetStudentCardNumber() const override
	{
		return m_cardNumber;
	}
	void SetStudentCardNumber(const std::string cardNumber) override
	{
		m_cardNumber = cardNumber;
	}
	void SetUniversityName(const std::string universityName) override
	{
		m_universityName = universityName;
	}

private:
	std::string m_cardNumber;
	std::string m_universityName;
};