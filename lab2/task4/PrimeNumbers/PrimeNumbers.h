#pragma once

const int MAX_BOUND = 100000000;
const int MIN_BOUND = 2;

std::set<int> GeneratePrimeNumbersSet(int upperBound);
std::vector<bool> GetSieve(int upperBound);
bool CheckRange(int upperBound);
void PrintPrimeNumbersSet(const std::set<int> sieve);