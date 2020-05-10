#include "stdafx.h"
#include "../Shapes/ShapesHandler.h"
#include "../Shapes/CLineSegment.h"
#include "../Shapes/CShape.h"

using namespace std;

struct HandlerDependencies
{
	stringstream input;
	stringstream output;
};

struct ShapesHandlerFixture : HandlerDependencies
{
	ShapesHandler shapesHandler;

	ShapesHandlerFixture()
		: shapesHandler(input, output)
	{
	}

	void VerifyCommand(const std::string& command = "", const string& expectedOutput = "")
	{
		output = stringstream();
		input = stringstream();
		BOOST_CHECK(input << command);
		BOOST_CHECK(shapesHandler.HandleCommand());
		BOOST_CHECK(input.eof());
		output << shapesHandler.GetShapes()[0]->ToString();
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};

BOOST_FIXTURE_TEST_SUITE(ShapesHandler_, ShapesHandlerFixture)
	BOOST_AUTO_TEST_SUITE(Test_HandleCommand)
		BOOST_AUTO_TEST_CASE(should_make_line_segment)
		{
			const std::string expectedStr = R"(Line segment:
	Area = 0
	Perimeter = 4
	Outline color = 0000ff
	Start point = (0.000, 1.500)
	End point = (0.000, 5.500)
)";
			VerifyCommand("line 0 1.5 0 5.5 0000ff", expectedStr);
		}
		BOOST_AUTO_TEST_CASE(should_make_circle)
		{
			const std::string expectedStr = R"(Circle:
	Area = 314.1592654
	Perimeter = 62.83185307
	Outline color = 0ff0ff
	Fill color = 0000ff
	Radius = 10
	Center = (0.000, 10.000)
)";
			VerifyCommand("circle 0 10 10 0ff0ff 0000ff", expectedStr);
		}
		BOOST_AUTO_TEST_CASE(should_make_rectangle)
		{
			const std::string expectedStr = R"(Rectangle:
	Area = 1240.28
	Perimeter = 142.2
	Outline color = ff0000
	Fill color = 00ff00
	Height = 40.4
	Width = 30.7
	Left top position = (10.300, 20.150)
	Right bottom position = (41.000, -20.250)
)";
			VerifyCommand("rectangle 10.3 20.15 30.7 40.4 ff0000 00ff00", expectedStr);
		}

		BOOST_AUTO_TEST_CASE(should_make_triangle)
		{
			const std::string expectedStr = R"(Triangle:
	Area = 6
	Perimeter = 12
	Outline color = ff0000
	Fill color = 00ff00
	Vertex 1 = (-1.000, 0.000)
	Vertex 2 = (3.000, 0.000)
	Vertex 3 = (3.000, 3.000)
)";

			VerifyCommand("triangle -1 0 3 0 3 3 ff0000 00ff00", expectedStr);
		}

		BOOST_AUTO_TEST_CASE(should_return_empty_shape_list)
		{
			BOOST_CHECK(shapesHandler.GetShapes().empty());
		}
		BOOST_AUTO_TEST_CASE(cannot_handle_unknown_command)
		{
			input = stringstream();
			input << "Sphere";
			BOOST_CHECK(!shapesHandler.HandleCommand());
		}
	BOOST_AUTO_TEST_SUITE_END()
	struct when_there_are_shapes : ShapesHandlerFixture
	{
		when_there_are_shapes()
		{
			input << "triangle 175 385 150 400 150 370 0000ff ff0000";
			shapesHandler.HandleCommand();
			input = stringstream();
			input << "circle 450 500 55 ffcc00 ffff00";
			shapesHandler.HandleCommand();
			input = stringstream();
			input << "rectangle 100 300 150 20 0000ff ff00ff";
			shapesHandler.HandleCommand();
			input = stringstream();
			input << "line 0 1.5 0 5.5 0000ff";
			shapesHandler.HandleCommand();
			input = stringstream();
		}
	};
	BOOST_FIXTURE_TEST_SUITE(ShapesHandler_, when_there_are_shapes)
		BOOST_AUTO_TEST_SUITE(Test_Shape_with_max_area)
			BOOST_AUTO_TEST_CASE(should_find_shape_with_max_area)
			{
				const std::string expectedOut = R"(Circle:
	Area = 9503.317777
	Perimeter = 345.5751919
	Outline color = ffcc00
	Fill color = ffff00
	Radius = 55
	Center = (450.000, 500.000)
)";
			BOOST_CHECK_EQUAL(shapesHandler.FindMaxArea()->ToString(), expectedOut);
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(Test_Shape_with_min_perimeter)
			BOOST_AUTO_TEST_CASE(should_find_shape_with_max_area)
			{
				const std::string expectedOut = R"(Line segment:
	Area = 0
	Perimeter = 4
	Outline color = 0000ff
	Start point = (0.000, 1.500)
	End point = (0.000, 5.500)
)";
				BOOST_CHECK_EQUAL(shapesHandler.FindMinPerimeter()->ToString(), expectedOut);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()