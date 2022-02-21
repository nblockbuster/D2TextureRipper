#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "package.h"

std::string uint16ToHexStr(uint16_t num);
std::string uint32ToHexStr(uint32_t num);
uint16_t swapUInt16Endianness(uint16_t x);
uint32_t swapUInt32Endianness(uint32_t x);
uint64_t swapUInt64Endianness(uint64_t x);
uint32_t hexStrToUint16(std::string hash);
uint32_t hexStrToUint32(std::string hash);
uint64_t hexStrToUint64(std::string hash);
std::string getHashFromFile(std::string file);
std::string getFileFromHash(std::string hsh);
std::string getReferenceFromHash(std::string hash, std::string pkgsPath, bool prebl);
std::string getPkgID(std::string hash);
uint16_t getPkgID(uint32_t hash);

