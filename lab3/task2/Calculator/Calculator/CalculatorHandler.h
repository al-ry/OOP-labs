#pragma once

#include <boost/noncopyable.hpp>


class CCalculator;

class CCalculatorHandler : boost::noncopyable
{
public:
	CCalculatorHandler(CCalculator& calc, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	bool DeclareVar(std::istream& args);
	bool LetVar(std::istream& args);
	bool MakeFn(std::istream& args);
	bool PrintValue(std::istream& args);
	bool PrintVars(std::istream& args);
	bool PrintFns(std::istream& args);
private:
	using Handler = std::function<bool(std::istream& args)>;

	using ActionMap = std::map<std::string, Handler>;

	CCalculator& m_calculator;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};
