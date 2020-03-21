#include "stdafx.h"
#include "PrimeNumbers.h"
using namespace std;

const int MAX_BOUND = 100000000;
const int MIN_BOUND = 2;

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
		cout << "Error " << error.what() << endl;
		return nullopt;
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
	if (!CheckRange(upperBound))
	{
		cout << "Number: " << upperBound << " is out of range";
		return 1;
	}
	set<int> primeNumbers = GeneratePrimeNumbersSet(upperBound);
	copy(primeNumbers.begin(), primeNumbers.end(), ostream_iterator<double>(cout, " "));
	return 0;
}