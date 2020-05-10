#include "stdafx.h"
#include "../Shapes/CLineSegment.h"

struct LineSegment_
{
	uint32_t expectedColor = 0xff0000;
	double expectedArea = 0;
	double expectedPerimeter = 3;
	CPoint expectedStartPosition;
	CPoint expectedEndPosition;
	CLineSegment lineSegment;

	LineSegment_()
		: expectedStartPosition(-1.0, 0.0)
		, expectedEndPosition(2.0, 0.0)
		, lineSegment(expectedStartPosition, expectedEndPosition, expectedColor)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(LineSegment, LineSegment_)

	BOOST_AUTO_TEST_CASE(is_a_shape)
	{
		BOOST_CHECK(static_cast<const CShape*>(&lineSegment));
	}
	BOOST_AUTO_TEST_CASE(has_a_color)
	{
		BOOST_CHECK(static_cast<const CShape&>(lineSegment).GetOutlineColor() == expectedColor);
	}
	BOOST_AUTO_TEST_CASE(has_zero_area)
	{
		BOOST_CHECK(lineSegment.GetArea() == expectedArea);
	}
	BOOST_AUTO_TEST_CASE(has_a_perimeter)
	{
		BOOST_CHECK(lineSegment.GetPerimeter() == expectedPerimeter);
	}
	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		const std::string expectedString = R"(Line segment:
	Area = 0
	Perimeter = 3
	Outline color = ff0000
	Start point = (-1.000, 0.000)
	End point = (2.000, 0.000)
)";
		BOOST_CHECK_EQUAL(static_cast<const CShape&>(lineSegment).ToString(), expectedString);
	}

BOOST_AUTO_TEST_SUITE_END()