#pragma once

#include <map>
#include <string>

typedef std::map<std::string, double> VariableMap;

class CCalculator
{
public:
	CCalculator()
		: m_variables(){};
	bool DeclareVariable(const std::string& var);


	VariableMap GetVariables() const;


private:
	bool IsVarAlreadyExist(const std::string& var) const;
	bool IsCorrectVarName(const std::string& varName) const;

private:
	VariableMap m_variables;

};
