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
	vector<bool> isPrime = GetSieve(upperBound);
	set<int> primeNumbersSet;
	for (int i = MIN_BOUND; i <= upperBound; i++)
	{
		if (isPrime[i])
		{
			primeNumbersSet.insert(i);
		}
	}
	return primeNumbersSet;
}

vector<bool> GetSieve(int upperBound)
{
	vector<bool> isPrime(upperBound + 1, true);
	for (int i = MIN_BOUND; i * i <= upperBound; i++)
	{
		if (isPrime[i])
		{
			for (int k = i * i; k <= upperBound; k += i)
			{
				isPrime[k] = false;
			}
		}
	}
	return isPrime;
}

void PrintPrimeNumbersSet(const std::set<int>& sieve)
{
	copy(sieve.begin(), sieve.end(), ostream_iterator<double>(cout, " "));
	cout << endl;
}
