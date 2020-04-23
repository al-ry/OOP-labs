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
		if(isascii(ch))
		{
			return std::isdigit(ch);
		}
		return false;
	}
}

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
	if (IsVarExist(var) || IsFnExist(var) || !IsCorrectIdentifierName(var))
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

bool CCalculator::IsFnExist(const std::string& fn) const
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

void CCalculator::UpdateFunctionsVals()
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
	if (!IsVarExist(rIdentifier) && !IsFnExist(rIdentifier))
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
	if (!IsVarExist(lIdentifier))
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

	UpdateFunctionsVals();

	return true;
}

double CCalculator::GetVarValue(const std::string& varName) const
{
	if (IsVarExist(varName))
	{
		return m_variables.at(varName);
	}
	return NAN;
}

double CCalculator::GetFnValue(const std::string& fnName) const
{
	if (IsFnExist(fnName))
	{
		return m_functions.at(fnName).val;						
	}
	return NAN;
}		


bool CCalculator::MakeFunction(const std::string& fn, const std::string& var)
{
	if (IsFnExist(fn) || !IsCorrectIdentifierName(fn) || !IsVarExist(var) || IsVarExist(fn))
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
	if (IsVarExist(fn) 
		|| IsFnExist(fn) 
		|| !(IsVarExist(firstOp) || IsFnExist(firstOp)) 
		|| !(IsVarExist(secondOp) || IsFnExist(secondOp))
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
	if (IsFnExist(fn.firstOp))
	{
		fVal = GetFnValue(fn.firstOp);
	}
	else
	{
		fVal = GetVarValue(fn.firstOp);
	}
	if (IsFnExist(fn.secondOp))
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

void CCalculator::RecalculateFnValue(Function &fn)
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