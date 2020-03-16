#include "stdafx.h"
#include "PackMachine.h"

using namespace std;

const int MAX_PACK = 0xFF;

void FlushPacket(RLEPacket& packet, ostream& outputFile)
{
	outputFile.put(packet.byteCounter);
	outputFile.put(packet.dataByte);
}

void PackByte(RLEPacket& packet, char byte, uint8_t& prevByte, ostream& outputFile)
{
	uint8_t dataByte;
	dataByte = byte;
	if (prevByte == dataByte && packet.byteCounter < MAX_PACK)
	{
		packet.byteCounter++;
	}
	else
	{
		FlushPacket(packet, outputFile);
		packet.byteCounter = 1;
		prevByte = byte;
		packet.dataByte = dataByte;
	}
}

void PackData(istream& inputFile, ostream& outputFile)
{
	uint8_t byte = 0, prevByte = 0;
	RLEPacket packet{1, 0};
	char ch;
	inputFile.read(&ch, sizeof(char));
	if (inputFile.eof())
	{
		return;
	}
	packet.dataByte = ch;
	prevByte = packet.dataByte;
	while (inputFile.read(&ch, sizeof(char)))
	{
		PackByte(packet, ch, prevByte, outputFile);
	}
	FlushPacket(packet, outputFile);
}
bool PackFile(const string& inputFileName, const string& outputFileName)
{
	ifstream inputFile;
	ofstream outputFile;
	inputFile.open(inputFileName, ios::binary);
	if (!inputFile.is_open())
	{
		cout << "Failed to open " << inputFileName << " for reading" << endl;
		return false;
	}
	outputFile.open(outputFileName, ios::binary);
	if (!outputFile.is_open())
	{
		cout << "Failed to open " << outputFileName << " for writing" << endl;
		return false;
	}

	PackData(inputFile, outputFile);

	if (inputFile.bad())
	{
		cout << "Failed to reading data from input stream" << endl;
		return false;
	}

	if (!outputFile.flush())
	{
		cout << "Failed to writing data in output stream" << endl;
		return false;
	}
	return true;
}
