#include "stdafx.h"
#include "..\PrimeNumbers\PrimeNumbers.h"


using namespace std;

BOOST_AUTO_TEST_SUITE(CheckRange_function)

	BOOST_AUTO_TEST_CASE(check_number_in_range)
	{
		int number = 50000;
		BOOST_CHECK_EQUAL(CheckRange(number), true);
	}
	BOOST_AUTO_TEST_CASE(check_number_out_of_range)
	{
		int number = 10000000000000;
		BOOST_CHECK_EQUAL(CheckRange(number), false);
	}
	BOOST_AUTO_TEST_CASE(check_min_bound_number)
	{
		int number = 2;
		BOOST_CHECK_EQUAL(CheckRange(number), true);
	}
	BOOST_AUTO_TEST_CASE(check_max_bound_number)
	{
		int number = 100000000;
		BOOST_CHECK_EQUAL(CheckRange(number), true);
	}
	BOOST_AUTO_TEST_CASE(check_that_0_is_not_prime_number)
	{
		int number = 0;
		BOOST_CHECK_EQUAL(CheckRange(number),false);
	}
	BOOST_AUTO_TEST_CASE(check_that_1_is_not_prime_number)
	{
		int number = 1;
		BOOST_CHECK_EQUAL(CheckRange(number), false);
	}
BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(GeneratePrimeNumbersSet_function)

	/*BOOST_AUTO_TEST_CASE(amount_prime_numbers_in_max_bound)
	{
		int number = 100000000;
		set<int> primeNumbers;
		primeNumbers = GeneratePrimeNumbersSet(number);
		int res = primeNumbers.size();

		BOOST_CHECK_EQUAL(res, 5761455);
	}*/

	BOOST_AUTO_TEST_CASE(amount_prime_numbers_in_20_bound)
	{
		int number = 20;
		set<int> primeNumbers;
		set<int> expectedSet = { 2, 3, 5, 7, 11, 13, 17, 19 };
		primeNumbers = GeneratePrimeNumbersSet(number);
		BOOST_CHECK(primeNumbers == expectedSet);
	}

BOOST_AUTO_TEST_SUITE_END()