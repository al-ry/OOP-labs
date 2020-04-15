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
	bool AssignValueToVariable(const std::string& lIdentidier, const std::string& rIdentifier);

	VariableMap GetVariables() const;
	double GetVariableValue(const std::string& varName) const;


private:
	bool IsVarExist(const std::string& var) const;
	bool IsCorrectVarName(const std::string& varName) const;

private:
	VariableMap m_variables;

};
