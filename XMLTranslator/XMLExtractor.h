#pragma once
#include <iostream>
#include <string>
#include "tinyxml2.h"
#include <map>

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

class FXMLExtractor {

public:

	std::string ReadBody(tinyxml2::XMLDocument*, std::string);
	std::string FolderPath = "C:\\Users\\Jack\\Documents\\Yarn\\";

};