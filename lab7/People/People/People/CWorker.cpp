#include "CWorker.h"

CWorker::CWorker(const std::string& name, const std::string& surname,
	const std::string& patronymic, const std::string& address,
	const std::string& specialization)
	: CPersonImpl(name, surname, patronymic, address)
	, m_specialization(specialization)
{
}

void CWorker::SetSpecialization(const std::string& specialization)
{
	m_specialization = specialization; 
}

std::string CWorker::GetSpecialization() const
{
	return m_specialization;
}
