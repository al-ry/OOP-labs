#pragma once

#include <map>
#include <string>

typedef std::map<std::string, double> VariableMap;

class CCalculator
{
public:
	CCalculator()
		: m_variables(){};
	VariableMap DeclareVariable(const std::string& var);


	
	//VariableMap GetVariables() const;


private:
	//bool IsVarAlreadyExist(const std::string& var);


private:
	VariableMap m_variables;

};
