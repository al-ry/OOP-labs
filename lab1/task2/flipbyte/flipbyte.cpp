#include <iostream>
#include <string>
#include <optional>


using namespace std;
const int LENGHT_OF_BYTE = 8;
const int MAX_VALUE_OF_ONE_BYTE = 255;
const int ARGUMENTS_COUNT = 2;


unsigned int ReverseByte(unsigned int decimalNumber)
{
	char byte[LENGHT_OF_BYTE] = "";
	int resultOfShifting;
	for (int i = 0; i < LENGHT_OF_BYTE; i++)
	{
		resultOfShifting = decimalNumber >> i & 1;
		byte[i] = resultOfShifting + '0';
	}
	decimalNumber = stoi(byte, 0, 2);
	return decimalNumber;
}
bool ParseArguments(int argc, char* argv[], string &arg)
{
	if (argc != ARGUMENTS_COUNT)
	{
		cout << "Numbers arguments is wrong" << endl;
		cout << "Usage: flipbyte.exe <Decimal number>" << endl;
		return false;
	}
	arg = argv[1];
	return true;
}
bool CheckIsNumber(const string& arg)
{
	try
	{
		stoi(arg);
	}
	catch (invalid_argument)
	{
		cout << "Incorrect Input" << endl;
		cout << "Enter a decimal number" << endl;
		return false;
	}
	catch (out_of_range)
	{
		cout << "Incorrect Input" << endl;
		cout << "Out of range" << endl;
		return false;
	}
	for (size_t i = 0; i < arg.length(); i++)
	{
		if (arg[0] == '-' && i == 0)
		{
			continue;
		}
		if (!isdigit(arg[i])) 
		{
			cout << "Incorrect Input" << endl;
			cout << "Enter a decimal number" << endl;
			return false;
		}
	}
	return true;
}
int main(int argc, char* argv[])
{
	string arg;
	bool isParsed = ParseArguments(argc, argv, arg);

	if (!isParsed)
	{
		return 1;
	}


	unsigned int decimalNumber;
	bool isNumber = CheckIsNumber(arg);


	if (!isNumber)
	{
		return 1;
	}
	decimalNumber = stoi(arg);
	

	if (decimalNumber < 0 || decimalNumber > MAX_VALUE_OF_ONE_BYTE)
	{
		cout << "Incorrect Input" << endl;
		cout << "Enter a number in range of one byte [0-255]" << endl;
		return 1;
	}

	decimalNumber = ReverseByte(decimalNumber);
	cout << decimalNumber << endl;
	return 0;
}
