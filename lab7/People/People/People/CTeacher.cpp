#include "CTeacher.h"



CTeacher::CTeacher(const std::string& name,
	const std::string& surname,
	const std::string& patronymic,
	const std::string& address,
	const std::string& subject)
	: CPersonImpl(name, surname, patronymic, address)
	, m_subject(subject)
{} 

std::string CTeacher::GetSubject() const
{
	return m_subject;
}

void CTeacher::SetSubject(const std::string& subject)
{
	m_subject = subject;
}
