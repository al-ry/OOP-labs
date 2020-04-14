#include "stdafx.h"
#include "Calculator.h"


VariableMap CCalculator::DeclareVariable(const std::string& var)
{
	m_variables.emplace(var, NAN);
	return m_variables;
}