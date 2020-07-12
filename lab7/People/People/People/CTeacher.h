#pragma once
#include "ITeacher.h"
#include "CPersonImpl.h"

class CTeacher : public CPersonImpl<ITeacher>
{
public:
	CTeacher() = default;
	CTeacher(const std::string& name, const std::string& surname,
		const std::string& patronymic, const std::string& address,
		const std::string& subject);

	std::string GetSubject() const override;
	void SetSubject(const std::string& subject) override;
private:
	std::string m_subject;
};