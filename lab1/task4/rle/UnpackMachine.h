#pragma once
#include "stdafx.h"

bool UnpackFile(const string& inputFileName, const string& outputFileName);
bool IsEvenFileSize(ifstream& inputFile);
void UnpackData(ifstream& inputFile, ofstream& outputFile);

