#include "CAdvancedStudent.h"


CAdvancedStudent::CAdvancedStudent(const std::string& name,
    const std::string& surname,
    const std::string& patronymic,
    const std::string& address,
    const std::string& universityName,
	const std::string& studentCardNumber,
	const std::string& dissertationTopic)
	: CStudentImpl(name, surname, patronymic, address, universityName, studentCardNumber)
	, m_dissertationTopic(dissertationTopic)
{
}

std::string CAdvancedStudent::GetDissertationTopic() const
{
	return m_dissertationTopic;
}

void CAdvancedStudent::SetDissertationTopic(const std::string& dissertationTopic)
{
	m_dissertationTopic = dissertationTopic;
}
