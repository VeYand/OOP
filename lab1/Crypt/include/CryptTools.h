#include <string>

#ifndef CRYPT_INCLUDE_CRYPTTOOLS_H
#define CRYPT_INCLUDE_CRYPTTOOLS_H

void Crypt(const std::string& inputFilePath, const std::string& outputFilePath, int key);
void Decrypt(const std::string& inputFilePath, const std::string& outputFilePath, int key);

#endif // CRYPT_INCLUDE_CRYPTTOOLS_H
