#include "stdafx.h"
#include "../Calculator/Calculator.h"

struct CalculatorFixture
{
	CCalculator calculator;
};

BOOST_FIXTURE_TEST_SUITE(Calculator_, CalculatorFixture)

	BOOST_AUTO_TEST_CASE(can_declare_var)
	{
		auto vars = calculator.DeclareVariable("x");
		BOOST_CHECK(vars.find("x") != vars.end());
	}

BOOST_AUTO_TEST_SUITE_END()
