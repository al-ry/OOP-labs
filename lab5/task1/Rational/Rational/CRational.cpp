#include "stdafx.h"
#include "CRational.h"

CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (denominator == 0)
	{
		m_numerator = 0;
		m_denominator = 1;
	}
	if (denominator < 0)
	{
		m_numerator = -m_numerator;
		m_denominator = -m_denominator;
	}
	NormalizeFraction();
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return (double(m_numerator)/double(m_denominator));
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	int integerPart = m_numerator / m_denominator;
	int newNumerator = m_numerator % m_denominator;
	return std::make_pair(integerPart, CRational(newNumerator, m_denominator));
}

const CRational CRational::operator+() const
{
	return *this;
}

const CRational CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}

CRational& CRational::operator+=(const CRational& operand)
{
	*this = *this + operand;
	return *this;
}

CRational& CRational::operator-=(const CRational& operand)
{
	*this = *this - operand;
	return *this;
}

CRational& CRational::operator/=(const CRational& operand)
{
	*this = *this / operand;
	return *this;
}

CRational& CRational::operator*=(const CRational& operand)
{
	*this = *this * operand;
	return *this;
}

void CRational::NormalizeFraction()
{
	int nod = FindNOD(abs(m_numerator), m_denominator);
	m_numerator /= nod;
	m_denominator /= nod;
}

int CRational::FindNOD(int first, int second) const
{
	while (second != 0)
	{
		std::swap(first, second);
		second = second % first;
	}
	return (first != 0) ? first : 0;
}

CRational const operator+(const CRational& firstOp, const CRational& secondOperand)
{
	int numerator = firstOp.GetNumerator() * secondOperand.GetDenominator() + firstOp.GetDenominator() * secondOperand.GetNumerator();
	int denominator = firstOp.GetDenominator() * secondOperand.GetDenominator();
	return CRational(numerator, denominator);
}

CRational const operator-(const CRational& firstOp, const CRational& secondOperand)
{
	return firstOp + -secondOperand;
}

CRational const operator*(const CRational& firstOp, const CRational& secondOperand)
{
	int numerator = firstOp.GetNumerator() * secondOperand.GetNumerator();
	int denominator = firstOp.GetDenominator() * secondOperand.GetDenominator();
	return CRational(numerator, denominator);
}

bool operator==(const CRational& firstOp, const CRational& secondOp)
{
	return firstOp.GetNumerator()== secondOp.GetNumerator() && firstOp.GetDenominator() == secondOp.GetDenominator();
}

bool operator!=(const CRational& firstOp, const CRational& secondOp)
{
	return !(firstOp == secondOp);
}

bool operator<(const CRational& firstOp, const CRational& secondOp)
{
	return firstOp.GetNumerator() *secondOp.GetDenominator() < firstOp.GetDenominator() * secondOp.GetNumerator();
}

bool operator<=(const CRational& firstOp, const CRational& secondOp)
{
	return firstOp == secondOp || firstOp < secondOp;
}

bool operator>(const CRational& firstOp, const CRational& secondOp)
{
	return !(firstOp <= secondOp);
}

std::ostream& operator<<(std::ostream& output, const CRational& number)
{
	output << number.GetNumerator() << "/" << number.GetDenominator();
	return output;
}

std::istream& operator>>(std::istream& input, CRational& number)
{
	int numerator;
	int denominator;
	if ((input >> numerator) && (input.get() == '/') && (input >> denominator))
	{
		number = CRational(numerator, denominator);
	}
	else
	{
		input.setstate(std::ios_base::failbit || input.rdstate());
	}
	return input;
}

bool operator>=(const CRational& firstOp, const CRational& secondOp)
{
	return !(firstOp < secondOp);
}

CRational const operator/(const CRational& firstOp, const CRational& secondOperand)
{
	return CRational(firstOp * CRational(secondOperand.GetDenominator(), secondOperand.GetNumerator()));
}

