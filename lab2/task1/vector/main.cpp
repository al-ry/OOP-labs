#include "stdafx.h"
#include "vectorProcessor.h"

using namespace std;

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