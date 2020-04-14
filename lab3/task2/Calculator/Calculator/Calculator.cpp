#include "stdafx.h"
#include "Calculator.h"

bool CCalculator::IsCorrectVarName(const std::string& varName) const
{
	if (varName.empty() || std::isdigit(*(varName.begin())))
	{
		return false;
	}
	return true;
}

bool CCalculator::DeclareVariable(const std::string& var)
{
	if (IsVarAlreadyExist(var) || !IsCorrectVarName(var))
	{
		return false;
	}
	m_variables.emplace(var, NAN);
	return true;
}

bool CCalculator::IsVarAlreadyExist(const std::string& var) const
{
	return m_variables.find(var) != m_variables.end();
}

VariableMap CCalculator::GetVariables() const
{
	return m_variables;
}