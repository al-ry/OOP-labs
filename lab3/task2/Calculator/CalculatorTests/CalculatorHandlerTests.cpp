#include "stdafx.h"
#include "../Calculator/Calculator.h"
#include "../Calculator/CalculatorHandler.h"
#include <boost/optional.hpp>

using namespace std;
using boost::none;
using boost::optional;

struct CalculatorHandlerDependencies
{
	CCalculator calculator;
	stringstream input;
	stringstream output;
};

struct CalculatorHandlerFixture : CalculatorHandlerDependencies
{
	CCalculatorHandler calculatorHandler;

	CalculatorHandlerFixture()
		: calculatorHandler(calculator, input, output)
	{
	}

	void ClearStream()
	{
		output = stringstream();
		input = stringstream();
	}

	void VerifyVarCommand(const std::string& command, const string& expectedOutput = "")
	{
		ClearStream();
		BOOST_CHECK(input << command);
		BOOST_CHECK(calculatorHandler.HandleCommand());	
 		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}

	void GetCommand(const string& command)
	{
		output = stringstream();
		input = stringstream();
		input << command;
	}
};


BOOST_FIXTURE_TEST_SUITE(Calculator_handler, CalculatorHandlerFixture)
	BOOST_AUTO_TEST_SUITE(Test_HandleCommand)
		BOOST_AUTO_TEST_CASE(cannot_verify_undefined_command)
		{
			GetCommand("get");
			BOOST_CHECK_EQUAL(calculatorHandler.HandleCommand(), false);
		}
		BOOST_AUTO_TEST_CASE(Verify_var_command)
		{
			GetCommand("var");
			BOOST_CHECK_EQUAL(calculatorHandler.HandleCommand(), true);
		}
		BOOST_AUTO_TEST_CASE(Verify_let_command)
		{
			GetCommand("let");
			BOOST_CHECK_EQUAL(calculatorHandler.HandleCommand(), true);
		}
		BOOST_AUTO_TEST_CASE(Verify_fn_command)
		{
			GetCommand("fn");
			BOOST_CHECK_EQUAL(calculatorHandler.HandleCommand(), true);
		}
		BOOST_AUTO_TEST_CASE(Verify_print_command)
		{
			GetCommand("print");
			BOOST_CHECK_EQUAL(calculatorHandler.HandleCommand(), true);
		}
		BOOST_AUTO_TEST_CASE(Verify_printvars_command)
		{
			GetCommand("printvars");
			BOOST_CHECK_EQUAL(calculatorHandler.HandleCommand(), true);
		}
		BOOST_AUTO_TEST_CASE(Verify_printfn_command)
		{
			GetCommand("printfns");
			BOOST_CHECK_EQUAL(calculatorHandler.HandleCommand(), true);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Test_var_command)
		BOOST_AUTO_TEST_CASE(can_declare_var)
		{
			VerifyVarCommand("var variable");
			auto varList = calculator.GetVariables();
			BOOST_CHECK(varList.find("variable") != varList.end());
		}
		BOOST_AUTO_TEST_CASE(cannot_declare_var)
		{
			VerifyVarCommand("var 8variable", "Invalid name of variable or variable already exist\n");
			auto varList = calculator.GetVariables();
			BOOST_CHECK(varList.find("8variable") == varList.end());
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Test_let_command)
		BOOST_AUTO_TEST_CASE(can_let_var)
		{
			VerifyVarCommand("let var=15.50");
			auto varList = calculator.GetVariables();
			BOOST_CHECK(varList.find("var") != varList.end());
			BOOST_CHECK_EQUAL(calculator.GetVarValue("var"), 15.50);
		}
		BOOST_AUTO_TEST_CASE(cannot_assign_value_when_after_let_command_follows_incorrect_symbols)
		{
			VerifyVarCommand("let qwerty", "Incorrect syntax of let command\n");
		}
		BOOST_AUTO_TEST_CASE(when_let_command_has_incorrect_syntax)
		{
			VerifyVarCommand("let var=", "Incorrect syntax of let command\n");
			auto varList = calculator.GetVariables();
			BOOST_CHECK(varList.find("var") == varList.end());
		}
		BOOST_AUTO_TEST_CASE(when_let_command_cannot_assign_value)
		{
			VerifyVarCommand("let var=x", "Cannot assign value to variable\n");
			auto varList = calculator.GetVariables();
			BOOST_CHECK(varList.find("var") == varList.end());
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct when_there_are_vars_ : CalculatorHandlerFixture
	{
		when_there_are_vars_()
		{
			calculator.AssignValueToVariable("x", "11");
			calculator.AssignValueToVariable("y", "12");
			calculator.MakeFunction("yMINUSx", "y", Operator::SUBTRACTION, "x");
		}
	};

	BOOST_FIXTURE_TEST_SUITE(Calculator_handler, when_there_are_vars_)
		BOOST_AUTO_TEST_SUITE(Test_fn_command)
			BOOST_AUTO_TEST_CASE(can_make_fn)
			{
				VerifyVarCommand("fn sumXY=x+y");
				BOOST_CHECK_EQUAL(calculator.GetFnValue("sumXY"), 23);
			}
			BOOST_AUTO_TEST_CASE(can_make_one_operand_fn)
			{
				VerifyVarCommand("fn fnX=x");
				BOOST_CHECK_EQUAL(calculator.GetFnValue("fnX"), 11);
			}
			BOOST_AUTO_TEST_CASE(cannot_make_function_when_inccorect_input_format_or_variables)
			{
				VerifyVarCommand("fn someFn=+", "Cannot make function\n");
				VerifyVarCommand("fn someFn=x+z", "Cannot make function\n");	
				VerifyVarCommand("fn someFn=x+", "Cannot make function\n");	
				VerifyVarCommand("fn someFn=+x", "Cannot make function\n");	
				VerifyVarCommand("fn someFn=p+z", "Cannot make function\n");	
				VerifyVarCommand("fn someFn=", "Cannot make function\n");	
				VerifyVarCommand("fn someFn", "Cannot make function\n");	
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(Test_printvars_command)
			BOOST_AUTO_TEST_CASE(should_print_vars_list)
			{
				VerifyVarCommand("printvars", "x: 11.00\ny: 12.00\n");
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(Test_printfn_command)
			BOOST_AUTO_TEST_CASE(should_print_fn_list)
			{
				VerifyVarCommand("printfns", "yMINUSx: 1.00\n");
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(Test_print_command)
			BOOST_AUTO_TEST_CASE(should_print_fn)
			{
				VerifyVarCommand("print yMINUSx", "1.00\n");
			}
			BOOST_AUTO_TEST_CASE(should_print_var)
			{
				VerifyVarCommand("print x", "11.00\n");
				VerifyVarCommand("print y", "12.00\n");
			}
		BOOST_AUTO_TEST_SUITE_END()


	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_CASE(should_print_empty__vars_list)
	{
		VerifyVarCommand("printvars", "There are no variables\n");
	}
	BOOST_AUTO_TEST_CASE(should_print_empty_fn_list)
	{
		VerifyVarCommand("printfns", "There are no functions\n");
	}
BOOST_AUTO_TEST_SUITE_END()