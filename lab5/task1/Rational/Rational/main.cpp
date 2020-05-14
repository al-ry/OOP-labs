#include "stdafx.h"
#include "CRational.h"

int main(void)
{
	CRational rational(0, 3);
	auto test = rational.ToCompoundFraction();
	return 0;
}