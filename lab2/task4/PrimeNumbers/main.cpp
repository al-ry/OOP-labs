#include "stdafx.h"
#include "PrimeNumbers.h"
using namespace std;

optional<int> ParseArg(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Usage: PrimeNumbers.exe <upper bound>" << endl;
		cout << MIN_BOUND << " <= <upper bound> <= " << MAX_BOUND << endl;
		return nullopt;
	}
	int arg;
	try
	{
		arg = atoi(argv[1]);
	}
	catch (exception const& error)
	{
		cout << "Incorrect Input. Argument should be a number" << endl;
		cout << "Error: " << error.what() << endl;
		return nullopt;
	}
	if (!CheckRange(arg))
	{
		cout << "Number: " << arg << " is out of range";
		return 1;
	}
	return arg;
}

int main(int argc, char* argv[])
{
	auto arg = ParseArg(argc, argv);
	if (!arg)
	{
		return 1;
	}
	int upperBound = arg.value();
	set<int> primeNumbers = GeneratePrimeNumbersSet(upperBound);
	PrintPrimeNumbersSet(primeNumbers);
	return 0;
}