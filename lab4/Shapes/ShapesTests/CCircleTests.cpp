#include "stdafx.h"
#include "../Shapes/CCircle.h"

struct Circle_
{
	uint32_t expectedOutlineColor = 0xffffff;
	uint32_t expectedFillColor = 0x0ff0ff;
	double expectedRadius = 10;
	double expectedArea = M_PI * expectedRadius * expectedRadius;
	double expectedPerimeter = 2 * M_PI * expectedRadius;
	CPoint expectedCenterPosition = { 20, 20 };
	CCircle circle;

	Circle_()
		: circle(expectedCenterPosition, expectedRadius, expectedOutlineColor, expectedFillColor)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Circle, Circle_)
	BOOST_AUTO_TEST_CASE(is_a_solid_shape)
	{
		BOOST_CHECK(static_cast<const CSolidShape*>(&circle));
	}
	BOOST_AUTO_TEST_CASE(is_a_shape)
	{
		BOOST_CHECK(static_cast<const CShape*>(&circle));
	}
	BOOST_AUTO_TEST_CASE(has_a_outline_color)
	{
		BOOST_CHECK(static_cast<const CShape&>(circle).GetOutlineColor() == expectedOutlineColor);
	}
	BOOST_AUTO_TEST_CASE(has_a_fill_color)
	{
		BOOST_CHECK(static_cast<const CSolidShape&>(circle).GetFillColor() == expectedFillColor);
	}
	BOOST_AUTO_TEST_CASE(has_a_radius)
	{
		BOOST_CHECK(circle.GetRadius() == expectedRadius);
	}
	BOOST_AUTO_TEST_CASE(has_a_center_position)
	{
		BOOST_CHECK(circle.GetCenter() == expectedCenterPosition);
	}
	BOOST_AUTO_TEST_CASE(has_an_area)
	{
		BOOST_CHECK_CLOSE_FRACTION(circle.GetArea(), expectedArea, 1e-7);
	}
	BOOST_AUTO_TEST_CASE(has_a_perimeter)
	{
		BOOST_CHECK_CLOSE_FRACTION(circle.GetPerimeter(), expectedPerimeter, 1e-7);
	}
	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		const std::string expectedString = R"(Circle:
	Area = 314.1592654
	Perimeter = 62.83185307
	Outline color = ffffff
	Fill color = 0ff0ff
	Radius = 10
	Center = (20.000, 20.000)
)";
		BOOST_CHECK_EQUAL(static_cast<const CShape&>(circle).ToString(), expectedString);
	}

BOOST_AUTO_TEST_SUITE_END()