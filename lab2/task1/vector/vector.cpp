#include "stdafx.h"

using namespace std;


vector<double> ReadStream()
{
	return vector<double>(istream_iterator<double>(cin), istream_iterator<double>());
}

bool ProcessVector(vector<double>& vector)
{
	if (!vector.empty())
	{
		const double minElement = *min_element(vector.begin(), vector.end());
		for (size_t i = 0; i < vector.size(); i++)
		{
			vector.at(i) = vector.at(i) * minElement;
		}
	}
	else
	{
		cout << "Enter a float numbers.";
		return false;
	}
	return true;
}

void PrintVector(const vector<double>& vector)
{
	cout << fixed << setprecision(3);
	copy(vector.begin(), vector.end(), ostream_iterator<double>(cout, " "));
	cout << endl;
}

int main()
{
	cout << "Enter a float numbers." << endl;
	vector<double> vector = ReadStream();
	if (!ProcessVector(vector))
	{
		return 1;
	}
	sort(vector.begin(), vector.end());
	PrintVector(vector);
	return 0;
}
