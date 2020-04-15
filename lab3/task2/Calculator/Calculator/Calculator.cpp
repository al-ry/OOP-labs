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
	if (IsVarExist(var) || !IsCorrectVarName(var))
	{
		return false;
	}
	m_variables.emplace(var, NAN);
	return true;
}

bool CCalculator::IsVarExist(const std::string& var) const
{
	return m_variables.find(var) != m_variables.end();
}

VariableMap CCalculator::GetVariables() const
{
	return m_variables;
}

bool CCalculator::AssignValueToVariable(const std::string& lIdentifier, const std::string& rIdentifier)
{
	if (rIdentifier.empty())
	{
		return false;
	}
	if (!IsVarExist(lIdentifier))
	{
		if (!DeclareVariable(lIdentifier))
		{
			return false;
		}
	}

	m_variables.at(lIdentifier) = GetVariableValue(rIdentifier);
	char* pEnd = nullptr; 
	strtod(rIdentifier.c_str(), &pEnd);
	if (!*pEnd == '\0')
	{
		return false;
	}
	m_variables.at(lIdentifier) = atof(rIdentifier.c_str());


	return true;
}

double CCalculator::GetVariableValue(const std::string& varName) const
{
	if (IsVarExist(varName))
	{
		return m_variables.at(varName);
	}
	return NAN;
}