#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorHandler.h"

using namespace std;

int main()
{
	CCalculator calc;
	CCalculatorHandler calculatorHandler(calc, cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!calculatorHandler.HandleCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}

	return 0;
}
