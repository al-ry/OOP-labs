#include <iostream>
#include <string>


using namespace std;
const int LENGHT_OF_BYTE = 8;
const int MAX_VALUE_OF_ONE_BYTE = 255;
const int ARGUMENTS_COUNT = 2;


unsigned int ReverseByte(unsigned int byte)
{
	byte = (byte & 0x55) << 1 | (byte & 0xAA) >> 1;
	byte = (byte & 0x33) << 2 | (byte & 0xCC) >> 2;
	byte = (byte & 0x0F) << 4 | (byte & 0xF0) >> 4;
	return byte;
}
bool ParseArguments(int argc, char* argv[], unsigned int &byte)
{
	if (argc != ARGUMENTS_COUNT)
	{
		cout << "Numbers arguments is wrong" << endl;
		cout << "Usage: flipbyte.exe <Decimal number>" << endl;
		return false;
	}
	size_t *notNumber = new size_t;
	try
	{
		byte = stoi(argv[1], notNumber, 10);
	}
	catch (exception const &error)
	{
		cout << "Incorrect Input" << endl;
		cout << "Error " << error.what() << endl;
		return false;
	}

	if (argv[1][*notNumber] != '\0')
	{
		cout << "Incorrect Input" << endl;
		cout << "Enter a number" << endl;
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	unsigned int byte;
	if (!ParseArguments(argc, argv, byte))
	{
		return 1;
	}

	if (byte < 0 || byte > MAX_VALUE_OF_ONE_BYTE)
	{
		cout << "Incorrect Input" << endl;
		cout << "Enter a number in range of one byte [0-255]" << endl;
		return 1;
	}

	unsigned int reversedByte = ReverseByte(byte);
	cout << reversedByte << endl;
	return 0;
}
