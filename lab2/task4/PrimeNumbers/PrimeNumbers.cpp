﻿#include "stdafx.h"
#include "PrimeNumbers.h"

const int MAX_BOUND = 100000000;
const int MIN_BOUND = 2;

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
	for (size_t i = MIN_BOUND; i <= upperBound; i++)
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
	for (size_t i = MIN_BOUND; i * i <= upperBound; i++)
	{
		if (sieve[i])
		{
			for (size_t k = i * i; k <= upperBound; k += i)
			{
				sieve[k] = false;
			}
		}
	}
	return sieve;
}