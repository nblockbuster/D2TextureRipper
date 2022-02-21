#include "main.h"

static void show_usage()
{
	std::cerr << "Usage: D2TextureRipper -p [packages path] -o [output path] -i [package id] -v [version]"
		<< std::endl;
	std::cerr << "-i extracts a package of textures\n";
	std::cerr << "-v changes the selected version. Valid types are: \"prebl\"\n";
}

int main(int argc, char** argv) {

	Sarge sarge;
	sarge.setArgument("p", "pkgspath", "packages path", true);
	sarge.setArgument("o", "outputpath", "output path", true);
	sarge.setArgument("i", "pkgid", "package id", true);
	sarge.setArgument("v", "version", "version changer", true);

	if (!sarge.parseArguments(argc, argv))
	{
		std::cerr << "Couldn't parse arguments..." << std::endl;
		show_usage();
		return 1;
	}

	std::string outputPath;
	std::string version;
	sarge.getFlag("pkgspath", packagesPath);
	sarge.getFlag("outputpath", outputPath);
	sarge.getFlag("pkgid", pkgID);
	sarge.getFlag("version", version);
	
	bool prebl;

	Package pkg(pkgID, packagesPath);
	
	if (version == "prebl" || version == "PREBL") {
		pkg.preBL = true;
		prebl = true;
	}

	pkg.readHeader();
	pkg.getEntryTable();

	for (int i = 0; i < pkg.entries.size(); i++) {
		Entry entry = pkg.entries[i];
		if (entry.numType == 32 && entry.numSubType == 1)
		{
			std::string datahash = entry.reference;
			int16_t textureFormat, width, height, arraySize;
			std::string largeHash;
			std::string headerHash = getReferenceFromHash(datahash, packagesPath, true);
			hash = headerHash;
			int fileSize;
			getFile(prebl);
			if (version == "prebl" || version == "PREBL") {
				memcpy((char*)&textureFormat, data + 4, 2);
				memcpy((char*)&width, data + 0xE, 2);
				memcpy((char*)&height, data + 0x10, 2);
				memcpy((char*)&arraySize, data + 0x14, 2);
				uint32_t val;
				memcpy((char*)&val, data + 0x24, 4);
				largeHash = uint32ToHexStr(val);
			}
			else {
				memcpy((char*)&textureFormat, data + 4, 2);
				memcpy((char*)&width, data + 0x22, 2);
				memcpy((char*)&height, data + 0x24, 2);
				memcpy((char*)&arraySize, data + 0x28, 2);
				uint32_t val;
				memcpy((char*)&val, data + 0x3C, 4);
				largeHash = uint32ToHexStr(val);
			}
			if (largeHash != "FFFFFFFF" && largeHash != "")
				hash = datahash;
			else
				hash = largeHash;
			delete[] data;

			fileSize = getFile(prebl);

			//p much just 100% copied from MDE/texture.cpp @ L64

			bool bCompressed = false;
			if (70 < textureFormat < 99) bCompressed = true;
			DDSHeader dds;
			DXT10Header dxt;
			dds.MagicNumber = 542327876;
			dds.dwSize = 124;
			dds.dwFlags = (0x1 + 0x2 + 0x4 + 0x1000) + 0x8;
			dds.dwHeight = height;
			dds.dwWidth = width;
			dds.dwPitchOrLinearSize = 0;
			dds.dwDepth = 0;
			dds.dwMipMapCount = 0;
			dds.dwReserved1 = std::array<uint32_t, 11>();
			dds.dwPFSize = 32;
			dds.dwPFRGBBitCount = 0;
			dds.dwPFRGBBitCount = 32;
			dds.dwPFRBitMask = 0xFF;
			dds.dwPFGBitMask = 0xFF00;
			dds.dwPFBBitMask = 0xFF0000;
			dds.dwPFABitMask = 0xFF000000;
			dds.dwCaps = 0x1000;
			dds.dwCaps2 = 0;
			dds.dwCaps3 = 0;
			dds.dwCaps4 = 0;
			dds.dwReserved2 = 0;
			if (bCompressed)
			{
				dds.dwPFFlags = 0x1 + 0x4;  // contains alpha data + contains compressed RGB data
				dds.dwPFFourCC = 808540228;
				dxt.dxgiFormat = textureFormat;
				dxt.resourceDimension = 3;  // DDS_DIMENSION_TEXTURE2D
				if (arraySize % 6 == 0)
				{
					// Compressed cubemap
					dxt.miscFlag = 4;
					dxt.arraySize = arraySize / 6;
				}
				else
				{
					// Compressed BCn
					dxt.miscFlag = 0;
					dxt.arraySize = 1;
				}
			}
			else
			{
				// Uncompressed
				dds.dwPFFlags = 0x1 + 0x40;  // contains alpha data + contains uncompressed RGB data
				dds.dwPFFourCC = 0;
				dxt.miscFlag = 0;
				dxt.arraySize = 1;
				dxt.miscFlags2 = 0x1;
			}
			if(!std::filesystem::exists(outputPath))
				std::filesystem::create_directories(outputPath);
			std::string fullDDSPath = outputPath + "/" + pkgID + "-" + boost::to_upper_copy(uint16ToHexStr(i)) + ".dds";
			FILE* outputFile;
			fopen_s(&outputFile, fullDDSPath.c_str(), "wb");
			if (outputFile != NULL) {
				fwrite(&dds, sizeof(struct DDSHeader), 1, outputFile);
				fwrite(&dxt, sizeof(struct DXT10Header), 1, outputFile);
				fwrite(data, fileSize, 1, outputFile);
				fclose(outputFile);
			}
			std::string dxgiFormat;
			std::string str;
			dxgiFormat = DXGI_FORMAT[textureFormat];
			if (dxgiFormat == "R8G8B8A8_UNORM") {
				dxgiFormat += "_SRGB";
				str = "texconv.exe \"" + fullDDSPath + "\" -y -nologo -srgb -ft PNG -f " + dxgiFormat;
			}
			else
				str = "texconv.exe \"" + fullDDSPath + "\" -y -nologo -ft PNG -f " + dxgiFormat;
			printf((str+"\n").c_str());
			system(str.c_str());
			std::filesystem::remove(fullDDSPath);
			delete[] data;
		}
	}
}

int getFile(bool prebl)
{
	if (pkgID == "")
		pkgID = getPkgID(hash);
	Package pkg(pkgID, packagesPath);
	if (prebl)
		pkg.preBL = true;
	int fileSize;
	data = pkg.getEntryData(hash, fileSize);
	if (data == nullptr || sizeof(data) == 0) return 0;
	return fileSize;
}