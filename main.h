#pragma once
#include "package.h"
#include <src\sarge.cpp>
#include <stdio.h>
#include "texture.h"
#include <boost\algorithm\string.hpp>

std::string pkgID = "";
std::string packagesPath = "";
std::string hash = "";
unsigned char* data = nullptr;

int getFile(bool prebl);