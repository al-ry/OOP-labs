#pragma once
#include "CStudentImpl.h"
#include "IAdvancedStudent.h"

class CAdvancedStudent: public CStudentImpl<IAdvancedStudent>
{
public:
	CAdvancedStudent() = default;
	CAdvancedStudent(const std::string& name,
    const std::string& surname,
    const std::string& patronymic,
    const std::string& address,
    const std::string& universityName,
	const std::string& studentCardNumber,
	const std::string& dissertationTopic);
	std::string GetDissertationTopic() const override;
	void SetDissertationTopic(const std::string& dissertationTopic) override;

private:
	std::string m_dissertationTopic;
};