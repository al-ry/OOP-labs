#pragma once

class CRational
{
public:
	CRational(int numerator = 0, int denominator = 1);
	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;
	std::pair<int, CRational> ToCompoundFraction() const;


	const CRational operator+() const;
	const CRational operator-() const;

	CRational& operator+=(const CRational& operand);
	CRational& operator-=(const CRational& operand);
	CRational& operator/=(const CRational& operand);
	CRational& operator*=(const CRational& operand);

private:
	void NormalizeFraction();
	int FindNOD(int first, int second) const;

private:
	int m_numerator;
	int m_denominator;
};

CRational const operator+(const CRational& firstOp, const CRational& secondOperand);
CRational const operator-(const CRational& firstOp, const CRational& secondOperand);
CRational const operator/(const CRational& firstOp, const CRational& secondOperand);
CRational const operator*(const CRational& firstOp, const CRational& secondOperand);

bool operator==(const CRational& firstOp, const CRational& secondOp);
bool operator!=(const CRational& firstOp, const CRational& secondOp);
bool operator<=(const CRational& firstOp, const CRational& secondOp);
bool operator<(const CRational& firstOp, const CRational& secondOp);
bool operator>=(const CRational& firstOp, const CRational& secondOp);
bool operator>(const CRational& firstOp, const CRational& secondOp);

std::ostream& operator<<(std::ostream& output, const CRational& number);
std::istream& operator>>(std::istream& input, CRational& number);
