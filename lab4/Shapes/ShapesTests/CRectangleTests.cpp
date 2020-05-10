#include "stdafx.h"
#include "../Shapes/CRectangle.h"

struct Rectangle_
{
	uint32_t expectedOutlineColor = 0x00ff00;
	uint32_t expectedFillColor = 0xff0000;
	double expectedWidth = 20;
	double expectedHeight = 10;
	double expectedArea = expectedWidth * expectedHeight;
	double expectedPerimeter = (expectedWidth + expectedHeight) * 2;
	CPoint expectedLeftTopPos = { 5, 5 };
	CPoint expectedRightBottomPos = { 5 + expectedWidth, 5 - expectedHeight };
	CRectangle rectangle;

	Rectangle_()
		: rectangle(expectedLeftTopPos, expectedWidth, expectedHeight, expectedOutlineColor, expectedFillColor)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Rectangle, Rectangle_)
	BOOST_AUTO_TEST_CASE(is_a_shape)
	{
		BOOST_CHECK(static_cast<const CShape*>(&rectangle));
	}
	BOOST_AUTO_TEST_CASE(is_a_solid_shape)
	{
		BOOST_CHECK(static_cast<const CSolidShape*>(&rectangle));
	}
	BOOST_AUTO_TEST_CASE(has_a_outline_color)
	{
		BOOST_CHECK(static_cast<const CShape&>(rectangle).GetOutlineColor() == expectedOutlineColor);
	}
	BOOST_AUTO_TEST_CASE(has_a_fill_color)
	{
		BOOST_CHECK(static_cast<const CSolidShape&>(rectangle).GetFillColor() == expectedFillColor);
	}
	BOOST_AUTO_TEST_CASE(has_width)
	{
		BOOST_CHECK_EQUAL(rectangle.GetWidth(), 20);
	}
	BOOST_AUTO_TEST_CASE(has_height)
	{
		BOOST_CHECK_EQUAL(rectangle.GetHeight(), 10);
	}
	BOOST_AUTO_TEST_CASE(has_left_top_position)
	{
		BOOST_CHECK(rectangle.GetLeftTop() == expectedLeftTopPos);
	}
	BOOST_AUTO_TEST_CASE(can_calcualte_right_bottom_position)
	{
		BOOST_CHECK(rectangle.GetRightBottom() == expectedRightBottomPos);
	}
	BOOST_AUTO_TEST_CASE(has_perimeter)
	{
		BOOST_CHECK(rectangle.GetPerimeter() == expectedPerimeter);
	}
	BOOST_AUTO_TEST_CASE(has_area)
	{
		BOOST_CHECK(rectangle.GetArea() == expectedArea);
	}
	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		std::string expectedString = R"(Rectangle:
	Area = 200
	Perimeter = 60
	Outline color = 00ff00
	Fill color = ff0000
	Height = 10
	Width = 20
	Left top position = (5.000, 5.000)
	Right bottom position = (25.000, -5.000)
)";
		BOOST_CHECK_EQUAL(rectangle.ToString(), expectedString);
	}
BOOST_AUTO_TEST_SUITE_END()