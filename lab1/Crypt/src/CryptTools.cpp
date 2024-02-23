#include "../include/CryptTools.h"
#include <fstream>

unsigned char MixBits(unsigned char byte)
{
	unsigned char result = 0;

	result |= ((byte >> 5) & 0x01) << 7;
	result |= ((byte >> 1) & 0x01) << 6;
	result |= ((byte >> 0) & 0x01) << 5;
	result |= ((byte >> 7) & 0x01) << 4;
	result |= ((byte >> 6) & 0x01) << 3;
	result |= ((byte >> 4) & 0x01) << 2;
	result |= ((byte >> 3) & 0x01) << 1;
	result |= ((byte >> 2) & 0x01) << 0;

	return result;
}

unsigned char UnmixBits(unsigned char byte)
{
	unsigned char result = 0;

	result |= ((byte >> 7) & 0x01) << 5;
	result |= ((byte >> 6) & 0x01) << 1;
	result |= ((byte >> 5) & 0x01) << 0;
	result |= ((byte >> 4) & 0x01) << 7;
	result |= ((byte >> 3) & 0x01) << 6;
	result |= ((byte >> 2) & 0x01) << 4;
	result |= ((byte >> 1) & 0x01) << 3;
	result |= ((byte >> 0) & 0x01) << 2;

	return result;
}

void CryptFile(std::ifstream& inputFile, std::ofstream& outputFile, int key)
{
	char byte;
	while (inputFile.get(byte))
	{
		byte = static_cast<char>(byte ^ key);
		outputFile.put(static_cast<char>(MixBits(byte)));
	}

	if (!inputFile.eof())
	{
		throw std::runtime_error("Error reading input file");
	}
}

void DecryptFile(std::ifstream& inputFile, std::ofstream& outputFile, int key)
{
	char byte;
	while (inputFile.get(byte))
	{
		byte = static_cast<char>(UnmixBits(byte) ^ key);
		outputFile.put(byte);
	}

	if (!inputFile.eof())
	{
		throw std::runtime_error("Error reading input file");
	}
}

void ValidateCryptKey(int key)
{
	if (key < 0 || key > 255)
	{
		throw std::invalid_argument("Invalid crypt key");
	}
}

void Crypt(const std::string& inputFilePath, const std::string& outputFilePath, int key)
{
	ValidateCryptKey(key);
	std::ifstream inputFile(inputFilePath);
	std::ofstream outputFile(outputFilePath);

	if (!inputFile.is_open())
	{
		throw std::runtime_error("Failed to open " + inputFilePath + " for reading");
	}

	if (!outputFile.is_open())
	{
		throw std::runtime_error("Failed to open " + outputFilePath + " for writing");
	}

	CryptFile(inputFile, outputFile, key);

	if (!outputFile.flush())
	{
		throw std::runtime_error("Failed to save data on disk");
	}
}

void Decrypt(const std::string& inputFilePath, const std::string& outputFilePath, int key)
{
	ValidateCryptKey(key);
	std::ifstream inputFile(inputFilePath);
	std::ofstream outputFile(outputFilePath);

	if (!inputFile.is_open())
	{
		throw std::runtime_error("Failed to open " + inputFilePath + " for reading");
	}

	if (!outputFile.is_open())
	{
		throw std::runtime_error("Failed to open " + outputFilePath + " for writing");
	}

	DecryptFile(inputFile, outputFile, key);

	if (!outputFile.flush())
	{
		throw std::runtime_error("Failed to save data on disk");
	}
}