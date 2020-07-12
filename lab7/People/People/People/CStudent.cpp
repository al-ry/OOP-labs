#include "CStudent.h"
#include "CStudentImpl.h"

CStudent::CStudent(const std::string& name,
    const std::string& surname,
    const std::string& patronymic,
    const std::string& address,
    const std::string& universityName,
	const std::string& studentCardNumber)
	: CStudentImpl(name, surname, patronymic, address, universityName, studentCardNumber)
{
}
