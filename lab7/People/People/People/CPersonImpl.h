#pragma once
#include "IPerson.h"

template <typename Base>
class CPersonImpl : public Base
{
public:
	CPersonImpl() = default;
	CPersonImpl(const std::string& name,
	const std::string& surname,
	const std::string& patronymic,
	const std::string& address)
	: m_name(name)
	, m_surname(surname)
	, m_patronymic(patronymic)
	, m_address(address)
	{
	}
	std::string GetName() const override
	{
		return m_name;
	}
	std::string GetSurname() const override
	{
		return m_surname;
	}
	std::string GetPatronymic() const override
	{
		return m_patronymic;
	}
	std::string GetAddress() const override
	{
		return m_address;
	}

	void SetName(const std::string& name) override
	{
		m_name = name;
	}
	void SetSurname(const std::string& surname) override
	{
		m_surname = surname;
	}
	void SetPatronymic(const std::string& patronymic) override
	{
		m_patronymic = patronymic;
	}
	void SetAddress(const std::string& address) override
	{
		m_address = address;
	}

private:
	std::string m_name;
	std::string m_surname;
	std::string m_patronymic;
	std::string m_address;
};
