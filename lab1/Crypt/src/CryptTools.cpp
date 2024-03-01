#include "../include/CryptTools.h"
#include <fstream>

const int MIN_CRYPT_KEY = 0;
const int MAX_CRYPT_KEY = 255;

unsigned char MixBits(unsigned char byte)
{
	unsigned char result = 0;

	result |= (byte & 0b00000111) << 2;
	result |= (byte & 0b00011000) << 3;
	result |= (byte & 0b01100000) >> 5;
	result |= (byte & 0b10000000) >> 2;

	return result;
}

unsigned char UnmixBits(unsigned char byte)
{
	unsigned char result = 0;

	result |= (byte & 0b00000011) << 5;
	result |= (byte & 0b00011100) >> 2;
	result |= (byte & 0b00100000) << 2;
	result |= (byte & 0b11000000) >> 3;

	return result;
}

void CryptFile(std::ifstream& inputFile, std::ofstream& outputFile, int key)
{
	char byte;
	while (inputFile.read(&byte, sizeof(byte)))
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
	while (inputFile.read(&byte, sizeof(byte)))
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
	if (key < MIN_CRYPT_KEY || key > MAX_CRYPT_KEY)
	{
		throw std::invalid_argument("Invalid crypt key");
	}
}

void Crypt(const std::string& inputFilePath, const std::string& outputFilePath, int key)
{
	ValidateCryptKey(key);
	std::ifstream inputFile(inputFilePath, std::ios::binary | std::ios::in);
	std::ofstream outputFile(outputFilePath, std::ios::binary | std::ios::out);

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
	std::ifstream inputFile(inputFilePath, std::ios::binary | std::ios::in);
	std::ofstream outputFile(outputFilePath, std::ios::binary | std::ios::out);

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