#pragma once
#include "CPersonImpl.h"
#include "IPupil.h"


class CPupil : public CPersonImpl<IPupil>
{
public:
	CPupil() = default;
	CPupil(const std::string& name, const std::string& surname,
		const std::string& patronymic, const std::string& address,
		const std::string& schoolName, const std::string& grade);

	std::string GetSchoolName() const override;
	std::string GetGrade() const override;

	void SetSchoolName(const std::string& schoolName) override;
	void SetGrade(const std::string& grade) override;

private:
	std::string m_schoolName;
	std::string m_grade;
};