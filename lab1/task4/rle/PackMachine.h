#pragma once

struct RLEPacket
{
	uint8_t byteCounter;
	uint8_t dataByte;
};

void FlushPacket(RLEPacket& packet, std::ostream& outputFile);
void PackByte(RLEPacket& packet, char byte, uint8_t& prevByte, std::ostream& outputFile);
void PackData(std::istream& inputFile, std::ostream& outputFile);
void WritePacket(std::ostream& outputFile, uint8_t byteAmount, uint8_t byte);
bool PackFile(const std::string& inputFileName, const std::string& outputFileName);


