#pragma once
#include "stdafx.h"

const int MAX_PACK = 0xFF;
const int ARGUMENTS_COUNT = 4;
void PackData(ifstream& inputFile, ofstream& outputFile);
void WritePacket(ofstream& outputFile, uint8_t byteAmount, uint8_t byte);
bool PackFile(const string& inputFileName, const string& outputFileName);


