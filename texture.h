#pragma once
#include <stdint.h>
#include <array>
#include "dxgiformat.h"

//copied from https://github.com/MontagueM/MontevenDynamicExtractor/blob/main/texture.h#L16

struct DDSHeader
{
	uint32_t MagicNumber;
	uint32_t dwSize;
	uint32_t dwFlags;
	uint32_t dwHeight;
	uint32_t dwWidth;
	uint32_t dwPitchOrLinearSize;
	uint32_t dwDepth;
	uint32_t dwMipMapCount;
	std::array<uint32_t, 11> dwReserved1;
	uint32_t dwPFSize;
	uint32_t dwPFFlags;
	uint32_t dwPFFourCC;
	uint32_t dwPFRGBBitCount;
	uint32_t dwPFRBitMask;
	uint32_t dwPFGBitMask;
	uint32_t dwPFBBitMask;
	uint32_t dwPFABitMask;
	uint32_t dwCaps;
	uint32_t dwCaps2;
	uint32_t dwCaps3;
	uint32_t dwCaps4;
	uint32_t dwReserved2;
};

struct DXT10Header
{
	uint32_t dxgiFormat;
	uint32_t resourceDimension;
	uint32_t miscFlag;
	uint32_t arraySize;
	uint32_t miscFlags2;
};