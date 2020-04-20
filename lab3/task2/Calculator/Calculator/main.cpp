#include "stdafx.h"
#include "Calculator.h"

int main()
{
	CCalculator calc;

    calc.AssignValueToVariable("x", "55.55");
	calc.AssignValueToVariable("y", "-100");
	calc.AssignValueToVariable("x", "y");
    calc.AssignValueToVariable("x", "hg5hello");
	return 0;
}
