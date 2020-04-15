#include "stdafx.h"
#include "Calculator.h"

int main()
{
	CCalculator calc;
	calc.DeclareVariable("var");
	calc.DeclareVariable("va");
	calc.AssignValueToVariable("va", "var");
	

	return 0;
}
