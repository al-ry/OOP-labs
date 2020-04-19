#include "stdafx.h"
#include "Calculator.h"

int main()
{
	CCalculator calc;


	calc.AssignValueToVariable("y", "100");
	calc.AssignValueToVariable("x", "100");


	calc.MakeFunction("SumXYFn", "y", Operator::ADDITION, "x");//200
	calc.MakeFunction("fnQ", "y", Operator::ADDITION, "SumXYFn");//300
	calc.AssignValueToVariable("y", "0");
	calc.MakeFunction("fnP", "SumXYFn", Operator::ADDITION, "SumXYFn");
	return 0;
}
