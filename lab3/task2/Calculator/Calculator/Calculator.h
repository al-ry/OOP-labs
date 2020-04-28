#pragma once


enum class Operator
{
	ADDITION,
	SUBTRACTION,
	DIVISION, 
	MULTIPLICATION
};

struct Function
{
	std::string firstOp;
	std::string secondOp;
	double val = NAN;
	Operator operatorType;
};
typedef std::map<std::string, double> VariablesMap;
typedef std::map<std::string, Function> FunctionsMap;
typedef std::vector<std::string> FunctionsOrder;

class CCalculator
{
public:
	CCalculator()
		: m_variables(), m_functions() {};
	bool DeclareVariable(const std::string& var);
	bool AssignValueToVariable(const std::string& lIdentidier, const std::string& rIdentifier);

	bool MakeFunction(const std::string& fn, const std::string& var);
	bool MakeFunction(const std::string& fn, const std::string& firstOp,
		Operator op, const std::string& secondOp);

	VariablesMap GetVariables() const;
	FunctionsMap GetFunctions() const; 
	double GetVarValue(const std::string& varName) const;
	double GetFnValue(const std::string& fnName) const;

private:
	bool DoesVarExist(const std::string& var) const;
	bool DoesFnExist(const std::string& var) const;
	bool IsCorrectIdentifierName(const std::string& varName) const;
	
	bool AssignValue(const std::string& lIdentifier, const std::string& rIdentifier);
	void RecalculateFunctionVals();
	void RecalculateFnValue(Function& fn);
	double CalculateTwoOpFnValue(Function& fn);

private:
	FunctionsMap m_functions;
	VariablesMap m_variables;
	FunctionsOrder m_functionsOrder;
};
