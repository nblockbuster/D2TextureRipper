# D2TextureRipper
Batch rips textures and images from Destiny 2 versions 1.0.0.1 -> 4.0.0.1

Requires [Sarge](https://github.com/MayaPosch/Sarge), [DestinyUnpackerCPP](https://github.com/MontagueM/DestinyUnpackerCPP), and [Boost](https://www.boost.org/) to build.

## Usage
Tool requires Windows 64-bit and a Destiny 2 installation from version 3.0.0.1 (Beyond Light) to 4.0.0.1 (The Witch Queen)  
You also need to copy "oo2core_8_win64.dll" from your Destiny 2/bin directory to where you put the exe.  

The tool is used via the command line:
D2TextureRipper.exe -p "D:/Backups/BL-Dec7/packages" -o "D:/Images/0311" -i 0311  

Required (and only) command line arguments are: -p, -o and -i.
- \-p \[packages path]: Packages path for Destiny 2 Beyond Light. An example would be: D:/Backups/BL-Dec7/packages"
- \-o \[output path]: Path where you want the images to go.
- \-i \[package id]: Package id that you want the images from. For the package "w64_investment_globals_0342_9", the package id would be 0342

I'm probably going to add support for Destiny 2 versions 1.0.0.1 -> 4.X.X.X soon.
