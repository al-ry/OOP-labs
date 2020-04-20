#include "stdafx.h"
#include "../Calculator/Calculator.h"

struct CalculatorFixture
{
	CCalculator calculator;
};

BOOST_FIXTURE_TEST_SUITE(Calculator_, CalculatorFixture)

	BOOST_AUTO_TEST_SUITE(Test_DeclareVriable_method)	

		BOOST_AUTO_TEST_CASE(can_declare_var_with_empty_val)
		{
			bool res = calculator.DeclareVariable("x");

			BOOST_CHECK_EQUAL(res, true);
		}

		BOOST_AUTO_TEST_CASE(cannot_declare_similar_vars)
		{
			calculator.DeclareVariable("x");
			bool res = calculator.DeclareVariable("x");

			BOOST_CHECK_EQUAL(res, false);
		}
		BOOST_AUTO_TEST_CASE(cannot_declare_with_empty_name)
		{
			bool res = calculator.DeclareVariable("");
		
			BOOST_CHECK_EQUAL(res, false);
		}

		BOOST_AUTO_TEST_CASE(cannot_declare_var_starts_with_digit)
		{
			bool res = calculator.DeclareVariable("123variable");

			BOOST_CHECK_EQUAL(res, false);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Test_GetVariables_method)	

		BOOST_AUTO_TEST_CASE(can_get_empty_variable_list)
		{
			BOOST_CHECK(calculator.GetVariables().empty());
		};

		BOOST_AUTO_TEST_CASE(can_get_variable_list_with_3_vars)
		{
			calculator.DeclareVariable("x");
			calculator.DeclareVariable("var_1");
			calculator.DeclareVariable("_var");

			auto res = calculator.GetVariables();
			BOOST_CHECK_EQUAL(res.size(), 3);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Test_AssignValueToVariable_method)	
		BOOST_AUTO_TEST_CASE(can_declare_var_through_this_method)
		{
			BOOST_CHECK(calculator.AssignValueToVariable("x", "5"));
			auto varList = calculator.GetVariables();
			BOOST_CHECK(varList.find("x") != varList.end());
		};
		BOOST_AUTO_TEST_CASE(check_that_right_identifier_cannot_be_empty)
		{
			BOOST_CHECK(!calculator.AssignValueToVariable("x", ""));
		}
		BOOST_AUTO_TEST_CASE(can_assign_value_to_var)
		{
			calculator.AssignValueToVariable("x", "55.55");
			auto varList = calculator.GetVariables();
			BOOST_CHECK_EQUAL(varList.at("x"), 55.55);
		};
		BOOST_AUTO_TEST_CASE(cant_assign_value_to_var_when_right_id_arent_either_number_or_another_var)
		{
			calculator.AssignValueToVariable("x", "hg5hello");
			calculator.DeclareVariable("f");
			auto varList = calculator.GetVariables();
			BOOST_CHECK(std::isnan(varList.at("f")));
		};
		BOOST_AUTO_TEST_CASE(can_assign_value_to_var_via_other_var)
		{
			calculator.AssignValueToVariable("x", "55.55");
			calculator.DeclareVariable("y");
			calculator.AssignValueToVariable("y", "x");
			auto varList = calculator.GetVariables();
			BOOST_CHECK_EQUAL(varList.at("y"), 55.55);
		};

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Test_GetVariableValue_method)
		BOOST_AUTO_TEST_CASE(can_get_empty_value_from_declared_var)
		{
			calculator.DeclareVariable("var_1");
			calculator.GetVarValue("var_1");
			BOOST_CHECK(std::isnan(calculator.GetVarValue("var_1")));
		};
		BOOST_AUTO_TEST_CASE(can_get_var_value)
		{
			calculator.AssignValueToVariable("var", "550");
			BOOST_CHECK_EQUAL(calculator.GetVarValue("var"), 550);
		};

	BOOST_AUTO_TEST_SUITE_END()

	struct when_there_are_declared_vars_ : CalculatorFixture
	{
		when_there_are_declared_vars_()
		{
			calculator.AssignValueToVariable("y", "50");
			calculator.AssignValueToVariable("x", "30");
		}
	};

	BOOST_FIXTURE_TEST_SUITE(when_there_are_declared_vars, when_there_are_declared_vars_)

		BOOST_AUTO_TEST_SUITE(Test_MakeFunction_method)

			BOOST_AUTO_TEST_CASE(can_make_function_with_var_value)
			{		
				calculator.MakeFunction("fnX", "x");
				auto fnList = calculator.GetFunctions();
				BOOST_CHECK(fnList.find("fnX") != fnList.end());
			};
			BOOST_AUTO_TEST_CASE(cannot_make_function_with_name_of_variable)
			{
				BOOST_CHECK(!calculator.MakeFunction("x", "y"));
			};

			BOOST_AUTO_TEST_CASE(cannot_make_function_with_undefined_var_value)
			{
				BOOST_CHECK(!calculator.MakeFunction("fnX", "undefined_var"));
			};
			BOOST_AUTO_TEST_CASE(cannot_make_functions_with_similar_names)
			{
				calculator.MakeFunction("fnX", "x");
				BOOST_CHECK(!calculator.MakeFunction("fnX", "y"));
			};
			BOOST_AUTO_TEST_CASE(can_get_function_value)
			{
				calculator.MakeFunction("fnX", "x");
				BOOST_CHECK_EQUAL(calculator.GetFnValue("fnX"), 30);
			};
			BOOST_AUTO_TEST_CASE(should_change_fn_val_after_setting_other_val_to_var)
			{
				calculator.MakeFunction("fnR", "y");
				calculator.AssignValueToVariable("y", "x");
				BOOST_CHECK_EQUAL(calculator.GetFnValue("fnR"), 30);
			};
			BOOST_AUTO_TEST_CASE(can_make_function_with_two_operands)
			{
				BOOST_CHECK(calculator.MakeFunction("SumXYFn", "y", Operator::ADDITION, "x"));
			};
			BOOST_AUTO_TEST_CASE(cannot_make_function_with_undefined_vars)
			{
				BOOST_CHECK(!calculator.MakeFunction("SumXYFn", "undefined", Operator::ADDITION, "x"));
				BOOST_CHECK(!calculator.MakeFunction("SumXYFn", "undefined", Operator::ADDITION, "qwe"));
				BOOST_CHECK(!calculator.MakeFunction("SumXYFn", "x", Operator::ADDITION, "qwe"));
			};
			BOOST_AUTO_TEST_CASE(can_make_function_with_function_operand)
			{
				BOOST_CHECK(calculator.MakeFunction("FnX+Y", "y", Operator::ADDITION, "x"));
				BOOST_CHECK(calculator.MakeFunction("FnX+SumXY", "x", Operator::ADDITION, "FnX+Y"));
				BOOST_CHECK(calculator.MakeFunction("FnSumXY+SumXY", "FnX+Y", Operator::ADDITION, "FnX+Y"));
			};
			BOOST_AUTO_TEST_CASE(can_get_function_value_after_making)
			{
				calculator.MakeFunction("SumXYFn", "y", Operator::ADDITION, "x");
				BOOST_CHECK_EQUAL(calculator.GetFnValue("SumXYFn"), 80);
			};
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

	struct when_there_are_functions_ : when_there_are_declared_vars_
	{
		when_there_are_functions_()
		{
			calculator.MakeFunction("XVal", "x");
			calculator.MakeFunction("Sum(x+y)", "x", Operator::ADDITION, "y");
		}
	};

	BOOST_FIXTURE_TEST_SUITE(when_there_are_functions, when_there_are_functions_)
		BOOST_AUTO_TEST_SUITE(Test_MakeFunction)
			BOOST_AUTO_TEST_CASE(can_get_fn_value)
			{
				BOOST_CHECK_EQUAL(calculator.GetFnValue("Sum(x+y)"), 80);
			};
			
			BOOST_AUTO_TEST_CASE(can_get_fn_value_when_one_operand_is_fn)
			{
				calculator.MakeFunction("Sum(x+y)-y", "Sum(x+y)", Operator::SUBTRACTION, "y");
				double res = calculator.GetVarValue("x");
				BOOST_CHECK_EQUAL(calculator.GetFnValue("Sum(x+y)-y"), res);
			};
			BOOST_AUTO_TEST_CASE(should_change_fn_value_when_changes_member_of_fn)
			{
				calculator.AssignValueToVariable("x", "100");
				BOOST_CHECK_EQUAL(calculator.GetFnValue("XVal"), 100);
			};
			BOOST_AUTO_TEST_CASE(after_changing_vars_value_should_changes_fn_value)
			{
				calculator.AssignValueToVariable("x", "100");
				calculator.AssignValueToVariable("y", "100");
				BOOST_CHECK_EQUAL(calculator.GetFnValue("Sum(x+y)"), 200);
			};
			BOOST_AUTO_TEST_CASE(after_changing_vars_and_substract_two_fn_which_contains_these_vars_should_change_both_fns_val)
			{
				calculator.AssignValueToVariable("x", "100");
				calculator.AssignValueToVariable("y", "100");
				calculator.MakeFunction("Sum(x+y)-XVal", "Sum(x+y)", Operator::SUBTRACTION, "XVal");
				BOOST_CHECK_EQUAL(calculator.GetFnValue("Sum(x+y)-XVal"), 100);
			};

		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()


	

	struct when_there_is_Fibonacci_sequence_ : CalculatorFixture
	{
		when_there_is_Fibonacci_sequence_()
		{
			calculator.AssignValueToVariable("v0", "0");
			calculator.AssignValueToVariable("v1", "1");
			calculator.MakeFunction("fib0", "v0");
			calculator.MakeFunction("fib1", "v1");
			calculator.MakeFunction("fib2", "fib1", Operator::ADDITION, "fib0");
			calculator.MakeFunction("fib3", "fib1", Operator::ADDITION, "fib2");
			calculator.MakeFunction("fib4", "fib3", Operator::ADDITION, "fib2");
			calculator.MakeFunction("fib5", "fib3", Operator::ADDITION, "fib4");
			calculator.MakeFunction("fib6", "fib5", Operator::ADDITION, "fib4");
		}
	};

	BOOST_FIXTURE_TEST_SUITE(Test_Fibonacci_sequence, when_there_is_Fibonacci_sequence_)
		BOOST_AUTO_TEST_CASE(check_Fibonacci_sequence)
		{
			BOOST_CHECK_EQUAL(calculator.GetFnValue("fib0"), 0);
			BOOST_CHECK_EQUAL(calculator.GetFnValue("fib1"), 1);
			BOOST_CHECK_EQUAL(calculator.GetFnValue("fib2"), 1);
			BOOST_CHECK_EQUAL(calculator.GetFnValue("fib3"), 2);
			BOOST_CHECK_EQUAL(calculator.GetFnValue("fib4"), 3);
			BOOST_CHECK_EQUAL(calculator.GetFnValue("fib5"), 5);
			BOOST_CHECK_EQUAL(calculator.GetFnValue("fib6"), 8);
		}
    BOOST_AUTO_TEST_SUITE_END()

	struct after_changing_two_first_values_ : when_there_is_Fibonacci_sequence_
	{
		after_changing_two_first_values_()
		{
			calculator.AssignValueToVariable("v0", "1");
			calculator.AssignValueToVariable("v1", "1");
		}
	};
	BOOST_FIXTURE_TEST_SUITE(Test_Fibonacci_sequence_after_changing_, after_changing_two_first_values_)
		BOOST_AUTO_TEST_CASE(check_Fibonacci_sequence)
		{
			BOOST_CHECK_EQUAL(calculator.GetFnValue("fib0"), 1);
			BOOST_CHECK_EQUAL(calculator.GetFnValue("fib1"), 1);
			BOOST_CHECK_EQUAL(calculator.GetFnValue("fib2"), 2);
			BOOST_CHECK_EQUAL(calculator.GetFnValue("fib3"), 3);
			BOOST_CHECK_EQUAL(calculator.GetFnValue("fib4"), 5);
			BOOST_CHECK_EQUAL(calculator.GetFnValue("fib5"), 8);
			BOOST_CHECK_EQUAL(calculator.GetFnValue("fib6"), 13);
		}
	BOOST_AUTO_TEST_SUITE_END()
		
BOOST_AUTO_TEST_SUITE_END()
