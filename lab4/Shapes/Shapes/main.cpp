#include "stdafx.h"
#include <cstdint>
#include <iostream>
#include "CLineSegment.h"
#include "CCircle.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "ShapesHandler.h"


void PrintPrompt()
{
	std::cout << "To make line segment: line <start x> <start y> <end x> <end y> <hex outline color>\n";
	std::cout << "To make circle: circle <center x> <center y> <redius> <hex outline color> <hex fill color>\n";
	std::cout << "To make triangle: triangle <vertex1 x> <vertex1 y> <vertex2 x> <vertex2 y> <vertex3 x> <vertex3 y> <hex outline color> <hex fill color>\n";
	std::cout << "To make rectangle: rectangle <left top x> <left top y> <width> <height> <hex outline color> <hex fill color>\n\n";
}

int main()
{ 
	PrintPrompt();
	ShapesHandler shapesHandler(std::cin, std::cout);
	
	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!shapesHandler.HandleCommand())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}
	if (!shapesHandler.GetShapes().empty())
	{
		std::cout << "Max area: \n"
				  << shapesHandler.FindMaxArea()->ToString();
		std::cout << "Min perimeter: \n"
				  << shapesHandler.FindMinPerimeter()->ToString();
		shapesHandler.DrawShapes();
	}
	else
	{
		std::cout << "There are no shapes";
		return 1;
	}
	return 0;
}