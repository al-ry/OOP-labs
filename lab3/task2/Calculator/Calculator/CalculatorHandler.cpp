#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorHandler.h"


using namespace std;
using namespace std::placeholders;

const std::map<char, Operator> OPERATORS_MAP{
	{ '+', Operator::ADDITION },
	{ '-', Operator::SUBTRACTION },
	{ '/', Operator::DIVISION },
	{ '*', Operator::MULTIPLICATION }
};
namespace
{
struct AssignmentOperands
{
	string firstOp;
	string secondOp;
};
struct Operation
{
	string firstOp;
	Operator op;
	string secondOp;
};
optional<AssignmentOperands> ParseAssignmentOperands(const string& op)
{
	auto separatorPos = op.find('=');
	if (separatorPos == string::npos || separatorPos + 1 == op.size())
	{
		return nullopt;
	}
	AssignmentOperands operands;
	operands.firstOp = op.substr(0, separatorPos);
	operands.secondOp = op.substr(separatorPos + 1, op.size());
	return operands;
}

optional<Operation> ParseOperation(const string& str)
{
	Operation op;
	size_t separatorPos = string::npos;
	for (auto& operators : OPERATORS_MAP)
	{
		if (str.find(operators.first) != string::npos)
		{
			separatorPos = str.find(operators.first);
			op.op = operators.second;
			break;
		}
	}
	if (separatorPos == string::npos)
	{
		op.firstOp = str.substr(0, separatorPos);
	}
	else
	{
		op.firstOp = str.substr(0, separatorPos);
		op.secondOp = str.substr(separatorPos + 1, str.size());
		if (op.firstOp.empty() || op.secondOp.empty())
		{
			return nullopt;
		}
	}
	return op;
}
}



CCalculatorHandler::CCalculatorHandler(CCalculator& calc, std::istream& input, std::ostream& output)
	: m_calculator(calc)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ { "var", bind(&CCalculatorHandler::DeclareVar, this, std::placeholders::_1) },
					{ "let", bind(&CCalculatorHandler::LetVar, this, std::placeholders::_1) },
					{ "fn", bind(&CCalculatorHandler::MakeFn, this, std::placeholders::_1) },
					{ "print", bind(&CCalculatorHandler::PrintValue, this, std::placeholders::_1) },
					{ "printvars", bind(&CCalculatorHandler::PrintVars, this, std::placeholders::_1) },
					{ "printfns", bind(&CCalculatorHandler::PrintFns, this, std::placeholders::_1) }
		})
{
}

bool CCalculatorHandler::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool CCalculatorHandler::DeclareVar(std::istream& args)
{
	string varName;
	args >> varName;
	if (!m_calculator.DeclareVariable(varName))
	{
		m_output << "Invalid name of variable or variable already exist\n";
	}
	return true;
}

bool CCalculatorHandler::LetVar(std::istream& args)
{
	string str;
	args >> str;
	auto operands = ParseAssignmentOperands(str);
	if (!operands)
	{
		m_output << "Incorrect syntax of let command\n";
		return true;
	}
	if (!m_calculator.AssignValueToVariable(operands->firstOp, operands->secondOp))
	{
		m_output << "Cannot assign value to variable\n";
		return true;
	}
	return true;
}

bool CCalculatorHandler::MakeFn(std::istream& args)
{
	string str;
	args >> str;
	auto operands = ParseAssignmentOperands(str);
	auto operation = ParseOperation(operands->secondOp);
	if ((!operands || !m_calculator.MakeFunction(operands->firstOp, operands->secondOp))
		&& (!operation || !m_calculator.MakeFunction(operands->firstOp, operation->firstOp, operation->op, operation->secondOp)))
	{
		m_output << "Cannot make function\n";
		return true;
	}
	return true;
}

bool CCalculatorHandler::PrintValue(std::istream& args)
{
	string name;
	args >> name;
	double varValue = m_calculator.GetVarValue(name);
	double fnValue = m_calculator.GetFnValue(name);
	if (!isnan(varValue))
	{
		m_output << std::fixed << std::setprecision(2);
		m_output << varValue << "\n";
	}
	else if (!isnan(fnValue))
	{
		m_output << std::fixed << std::setprecision(2);
		m_output << fnValue << "\n";
	}
	else
	{
		m_output << NAN << "\n";
	}
	return true;
}

bool CCalculatorHandler::PrintVars(std::istream& args)
{
	auto varList = m_calculator.GetVariables();
	if (varList.empty())
	{
		m_output << "There are no variables\n";
		return true;
	}
	for (auto& var : varList)
	{
		m_output << std::fixed << std::setprecision(2);
		m_output << var.first << ": " << var.second << "\n";
	}
	return true;
}

bool CCalculatorHandler::PrintFns(std::istream& args)
{
	auto fnList = m_calculator.GetFunctions();
	if (fnList.empty())
	{
		m_output << "There are no functions\n";
		return true;
	}
	for (auto& fn: fnList)
	{
		m_output << std::fixed << std::setprecision(2);
		m_output << fn.first << ": " << m_calculator.GetFnValue(fn.first) << "\n";
	}
	return true;
}
