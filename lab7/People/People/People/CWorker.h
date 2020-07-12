#pragma once
#include "CPersonImpl.h"
#include "IWorker.h"

class CWorker : public CPersonImpl<IWorker>
{
public:
	CWorker() = default;
	CWorker(const std::string& name, const std::string& surname,
		const std::string& patronymic, const std::string& address,
		const std::string& specialization);

	std::string GetSpecialization() const override;
	void SetSpecialization(const std::string& specialization) override;

private:
	std::string m_specialization;
};