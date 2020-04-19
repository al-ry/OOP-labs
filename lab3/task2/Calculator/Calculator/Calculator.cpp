#include "stdafx.h"
#include "Calculator.h"

bool CCalculator::IsCorrectIdentifierName(const std::string& varName) const
{
	if (varName.empty() || std::isdigit(*(varName.begin())))
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
	if (*pEnd == '\0')
	{
		m_variables.at(lIdentifier) = atof(rIdentifier.c_str());
	}


	for (auto &fn: m_functions)
	{
		if (fn.second.firstOp == lIdentifier || fn.second.secondOp == lIdentifier)
		{
			RecalculateFnValue(fn.second);
		}
	}


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
	fun.val = GetVariableValue(var);
	m_functions.emplace(fn, fun);	
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
		fVal = GetVariableValue(fn.firstOp);
	}
	if (IsFnExist(fn.secondOp))
	{
		sVal = GetFnValue(fn.secondOp);
	}
	else
	{
		sVal = GetVariableValue(fn.secondOp);
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
		fn.val = GetVariableValue(fn.firstOp);
	}
	else
	{
		CalculateTwoOpFnValue(fn);
	}
}