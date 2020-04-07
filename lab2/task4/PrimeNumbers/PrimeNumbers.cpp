#include "stdafx.h"
#include "PrimeNumbers.h"

using namespace std;

bool CheckRange(int upperBound)
{
	if (upperBound < MIN_BOUND || upperBound > MAX_BOUND)
	{
		return false;
	}
	return true;
}

set<int> GeneratePrimeNumbersSet(int upperBound)
{
	vector<bool> sieve = GetSieve(upperBound);
	set<int> primeNumbersSet;
	for (int i = MIN_BOUND; i <= upperBound; i++)
	{
		if (sieve[i])
		{
			primeNumbersSet.insert(i);
		}
	}
	return primeNumbersSet;
}

vector<bool> GetSieve(int upperBound)
{
	vector<bool> sieve(upperBound + 1, true);
	for (int i = MIN_BOUND; i * i <= upperBound; i++)
	{
		if (sieve[i])
		{
			for (int k = i * i; k <= upperBound; k += i)
			{
				sieve[k] = false;
			}
		}
	}
	return sieve;
}

void PrintPrimeNumbersSet(const std::set<int> sieve)
{
	copy(sieve.begin(), sieve.end(), ostream_iterator<double>(cout, " "));
	cout << endl;
}
