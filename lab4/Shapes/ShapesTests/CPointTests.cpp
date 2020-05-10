#include "stdafx.h"
#include "../Shapes/CPoint.h"

struct Point_
{
	CPoint point = { 5, 10 };
};

BOOST_FIXTURE_TEST_SUITE(Point, Point_)
	BOOST_AUTO_TEST_CASE(check_x_pos)
	{
		BOOST_CHECK_EQUAL(point.x, 5);
	}
	BOOST_AUTO_TEST_CASE(check_y_pos)
	{
		BOOST_CHECK_EQUAL(point.y, 10);
	}
	BOOST_AUTO_TEST_CASE(can_be_compared)
	{
		CPoint expPoint = { 5, 10 };
		BOOST_CHECK(point == expPoint);
		expPoint.x = 200;
		BOOST_CHECK(point != expPoint);
	}
	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		const std::string expectedStr = "(5.000, 10.000)";
		BOOST_CHECK_EQUAL(point.ToString(), expectedStr);
	}
BOOST_AUTO_TEST_SUITE_END()