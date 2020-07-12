#include "CPupil.h"
#include "CPersonImpl.h"

CPupil::CPupil(const std::string& name, const std::string& surname,
	const std::string& patronymic, const std::string& address,
	const std::string& schoolName, const std::string& grade)
	: CPersonImpl<IPupil>(name, surname, patronymic, address)
	, m_schoolName(schoolName)
	, m_grade(grade)
{
}

std::string CPupil::GetSchoolName() const
{
	return m_schoolName;
}

std::string CPupil::GetGrade() const
{
	return m_grade;
}

void CPupil::SetSchoolName(const std::string& schoolName)
{
	m_schoolName = schoolName;
}

void CPupil::SetGrade(const std::string& grade)
{
	m_grade = grade;
}
