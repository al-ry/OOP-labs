#include "stdafx.h"
#include "Calculator.h"

namespace
{
bool IsCharCorrect(char ch)
{
	if (isascii(ch))
	{
		return std::isdigit(ch) || std::isalpha(ch) || ch == '_';
	}
	return false;
}
bool IsFirstSymbolNumber(char ch)
{
	if (isascii(ch))
	{
		return std::isdigit(ch);
	}
	return false;
}
} // namespace

bool CCalculator::IsCorrectIdentifierName(const std::string& varName) const
{
	if (varName.empty() || IsFirstSymbolNumber(*varName.begin())
		|| !std::all_of(varName.begin(), varName.end(), IsCharCorrect))
	{
		return false;
	}
	return true;
}

bool CCalculator::DeclareVariable(const std::string& var)
{
	if (DoesVarExist(var) || DoesFnExist(var) || !IsCorrectIdentifierName(var))
	{
		return false;
	}
	m_variables.emplace(var, NAN);
	return true;
}

bool CCalculator::DoesVarExist(const std::string& var) const
{
	return m_variables.find(var) != m_variables.end();
}

bool CCalculator::DoesFnExist(const std::string& fn) const
{
	return m_functions.find(fn) != m_functions.end();
}

VariablesMap CCalculator::GetVariables() const
{
	return m_variables;
}

FunctionsMap CCalculator::GetFunctions() const
{
	return m_functions;
}

void CCalculator::RecalculateFunctionVals()
{
	for (auto& fnName : m_functionsOrder)
	{
		Function& fn = m_functions.at(fnName);
		RecalculateFnValue(fn);
	}
}

bool CCalculator::AssignValue(const std::string& lIdentifier, const std::string& rIdentifier)
{
	double varVal = GetVarValue(rIdentifier);
	double fnVal = GetFnValue(rIdentifier);
	if (!std::isnan(varVal))
	{
		m_variables.at(lIdentifier) = GetVarValue(rIdentifier);
	}
	else if (!std::isnan(fnVal))
	{
		m_variables.at(lIdentifier) = GetFnValue(rIdentifier);
	}
	else
	{
		m_variables.at(lIdentifier) = NAN;
	}

	char* pEnd = nullptr;
	strtod(rIdentifier.c_str(), &pEnd);
	if (!DoesVarExist(rIdentifier) && !DoesFnExist(rIdentifier))
	{
		if (*pEnd == '\0')
		{
			m_variables.at(lIdentifier) = atof(rIdentifier.c_str());
		}
		else
		{
			m_variables.erase(lIdentifier);
			return false;
		}
	}
	return true;
}

bool CCalculator::AssignValueToVariable(const std::string& lIdentifier, const std::string& rIdentifier)
{
	if (rIdentifier.empty())
	{
		return false;
	}
	if (!DoesVarExist(lIdentifier))
	{
		if (!DeclareVariable(lIdentifier))
		{
			return false;
		}
	}

	if (!AssignValue(lIdentifier, rIdentifier))
	{
		return false;
	}

	RecalculateFunctionVals();

	return true;
}

double CCalculator::GetVarValue(const std::string& varName) const
{
	if (DoesVarExist(varName))
	{
		return m_variables.at(varName);
	}
	return NAN;
}

double CCalculator::GetFnValue(const std::string& fnName) const
{
	if (DoesFnExist(fnName))
	{
		return m_functions.at(fnName).val;
	}
	return NAN;
}

bool CCalculator::MakeFunction(const std::string& fn, const std::string& var)
{
	if (DoesFnExist(fn) || !IsCorrectIdentifierName(fn) || !DoesVarExist(var) || DoesVarExist(fn))
	{
		return false;
	}

	Function fun;
	fun.firstOp = var;
	fun.val = GetVarValue(var);
	m_functions.emplace(fn, fun);
	m_functionsOrder.emplace_back(fn);
	return true;
}

bool CCalculator::MakeFunction(const std::string& fn, const std::string& firstOp,
	Operator op, const std::string& secondOp)
{
	if (DoesVarExist(fn)
		|| DoesFnExist(fn)
		|| !(DoesVarExist(firstOp) || DoesFnExist(firstOp))
		|| !(DoesVarExist(secondOp) || DoesFnExist(secondOp))
		|| !IsCorrectIdentifierName(fn))

	{
		return false;
	}

	Function fun;
	fun.firstOp = firstOp;
	fun.secondOp = secondOp;
	fun.operatorType = op;
	fun.val = CalculateTwoOpFnValue(fun);
	m_functions.emplace(fn, fun);
	m_functionsOrder.emplace_back(fn);
	return true;
}

double CCalculator::CalculateTwoOpFnValue(Function& fn)
{
	double fVal;
	double sVal;
	if (DoesFnExist(fn.firstOp))
	{
		fVal = GetFnValue(fn.firstOp);
	}
	else
	{
		fVal = GetVarValue(fn.firstOp);
	}
	if (DoesFnExist(fn.secondOp))
	{
		sVal = GetFnValue(fn.secondOp);
	}
	else
	{
		sVal = GetVarValue(fn.secondOp);
	}
	switch (fn.operatorType)
	{
	case Operator::ADDITION:
		fn.val = fVal + sVal;
		break;
	case Operator::SUBTRACTION:
		fn.val = fVal - sVal;
		break;
	case Operator::DIVISION:
		fn.val = fVal / sVal;
		break;
	case Operator::MULTIPLICATION:
		fn.val = fVal * sVal;
		break;
	}
	return fn.val;
}

void CCalculator::RecalculateFnValue(Function& fn)
{
	if (fn.secondOp.empty())
	{
		fn.val = GetVarValue(fn.firstOp);
	}
	else
	{
		CalculateTwoOpFnValue(fn);
	}
}
