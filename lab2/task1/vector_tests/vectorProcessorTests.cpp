#include "stdafx.h"
#include "vectorProcessor.h"

using namespace std;

bool VectorsAreEqual(vector<double> const& x, vector<double> const& y)
{
	return x == y;
}

// Функция ProcessVector
BOOST_AUTO_TEST_SUITE(ProcessVector_function)

	// Создает пустой вектор из пустого вектора
	BOOST_AUTO_TEST_CASE(makes_empty_vector_from_empty_vector)
	{
		vector<double> emptyVector;
		ProcessVector(emptyVector);
		BOOST_CHECK(emptyVector.empty());
	}



	BOOST_AUTO_TEST_SUITE(when_processing_a_vector_with_one_positive_number)

		BOOST_AUTO_TEST_CASE(should_multiply_this_number_by_itself)
		{
			vector<double> numbers = { 2 };
			vector<double> expectedOut = { (2 * 2) };
			ProcessVector(numbers);
			BOOST_CHECK(VectorsAreEqual(numbers, expectedOut));
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(when_processing_a_vector_with_several_elements)
		BOOST_AUTO_TEST_CASE(should_multiply_min_number_on_each_element)
		{
			const double minNumber = -1.2;

			vector<double> numbers = { -1.2, 10.2, 2.33, 3.2 };
			vector<double> expectedNumbers = { (-1.2 * minNumber), (10.2 * minNumber), (2.33 * minNumber), (3.2 * minNumber) };

			ProcessVector(numbers);

			BOOST_CHECK(VectorsAreEqual(numbers, expectedNumbers));
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_AUTO_TEST_SUITE(when_processing_a_vector_with_zero_elements)
		BOOST_AUTO_TEST_CASE(should_multiply_zero_on_each_element)
		{
			const double minNumber = 0;

			vector<double> numbers = { 0, 0, 0, 0 };
			vector<double> expectedNumbers = { (0 * minNumber), (0 * minNumber), (0 * minNumber), (0 * minNumber) };

			ProcessVector(numbers);

			BOOST_CHECK(VectorsAreEqual(numbers, expectedNumbers));
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(when_processing_a_vector_with_one_zero_elements)
		BOOST_AUTO_TEST_CASE(should_multiply_zero_on_each_element)
		{
			const double minNumber = 0;

			vector<double> numbers = { 34.2, 22.1, 0, 10 };
			vector<double> expectedNumbers = { (34.2 * minNumber), (22.1 * minNumber), (0 * minNumber), (10 * minNumber) };

			ProcessVector(numbers);

			BOOST_CHECK(VectorsAreEqual(numbers, expectedNumbers));
		}
	BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE_END()
