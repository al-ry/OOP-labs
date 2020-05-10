#include "stdafx.h"
#include "../Shapes/CLineSegment.h"
#include "../Shapes/CTriangle.h"

struct Triangle_
{
	uint32_t expectedOutlineColor = 0x0000ff;
	uint32_t expectedFillColor = 0x00ff00;
	CPoint vertex1 = { -1, 0 };
	CPoint vertex2 = { 3, 0 };
	CPoint vertex3 = { 3, 3 };
	CLineSegment line1;
	CLineSegment line2;
	CLineSegment line3;
	CTriangle triangle;
	Triangle_()
		: triangle(vertex1, vertex2, vertex3, expectedOutlineColor, expectedFillColor)
		, line1(vertex1, vertex2, expectedOutlineColor)
		, line2(vertex2, vertex3, expectedOutlineColor)
		, line3(vertex3, vertex1, expectedOutlineColor)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(Triangle, Triangle_)
	BOOST_AUTO_TEST_CASE(is_a_solid_shape)
	{
		BOOST_CHECK(static_cast<const CSolidShape*>(&triangle));
	}
	BOOST_AUTO_TEST_CASE(is_a_shape)
	{
		BOOST_CHECK(static_cast<const CShape*>(&triangle));
	}
	BOOST_AUTO_TEST_CASE(has_a_outline_color)
	{
		BOOST_CHECK(static_cast<const CShape&>(triangle).GetOutlineColor() == 0x0000ff);
	}
	BOOST_AUTO_TEST_CASE(has_a_fill_color)
	{
		BOOST_CHECK(static_cast<const CSolidShape&>(triangle).GetFillColor() == 0x00ff00);
	}
	BOOST_AUTO_TEST_CASE(can_get_vertex1)
	{
		BOOST_CHECK(triangle.GetVertex1() == vertex1);
	}
	BOOST_AUTO_TEST_CASE(can_get_vertex2)
	{
		BOOST_CHECK(triangle.GetVertex2() == vertex2);
	}
	BOOST_AUTO_TEST_CASE(can_get_vertex3)
	{
		BOOST_CHECK(triangle.GetVertex3() == vertex3);
	}
	BOOST_AUTO_TEST_CASE(has_perimeter)
	{
		double expectedPerimeter = line1.GetPerimeter() + line2.GetPerimeter() + line3.GetPerimeter();
		BOOST_CHECK(triangle.GetPerimeter() == expectedPerimeter);
	}
	BOOST_AUTO_TEST_CASE(has_area)
	{
		double semiPerimeter = (line1.GetPerimeter() + line2.GetPerimeter() + line3.GetPerimeter()) / 2;
		double expectedArea = sqrt(semiPerimeter * (semiPerimeter - line1.GetPerimeter()) * (semiPerimeter - line2.GetPerimeter()) * (semiPerimeter - line3.GetPerimeter()));
		BOOST_CHECK(triangle.GetArea() == expectedArea);
	}
	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		std::string expectedString = R"(Triangle:
	Area = 6
	Perimeter = 12
	Outline color = 0000ff
	Fill color = 00ff00
	Vertex 1 = (-1.000, 0.000)
	Vertex 2 = (3.000, 0.000)
	Vertex 3 = (3.000, 3.000)
)";
		BOOST_CHECK_EQUAL(triangle.ToString(), expectedString);
	}
BOOST_AUTO_TEST_SUITE_END()