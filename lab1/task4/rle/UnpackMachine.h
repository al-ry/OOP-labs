#pragma once

bool UnpackFile(const std::string& inputFileName, const std::string& outputFileName);
bool IsEvenFileSize(std::istream& inputFile);
void UnpackData(std::istream& inputFile, std::ostream& outputFile);

