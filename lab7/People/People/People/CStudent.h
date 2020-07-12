#pragma once
#include "IStudent.h"
#include "CStudentImpl.h"

class CStudent : public CStudentImpl<IStudent>
{
public:
	CStudent() = default;
	CStudent(const std::string& name,
		const std::string& surname,
		const std::string& patronymic,
		const std::string& address, const std::string& universityName,
		const std::string& studentCardNumber);
};
