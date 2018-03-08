#pragma once

#include <string>         // std::string
#include <map>  
#include <vector>
#define TMap std::map

struct playeroptiontype {
	int index;
	std::string option;
	std::string optioncode;
	std::string node;
};

class Parser {

public:
	TMap<int, std::pair<std::string,std::string>> OptionsParser(std::string);
	std::string DialogueParser(std::string);
	std::vector<playeroptiontype> ParseOptions(std::string);

private:
	std::string strneedlestart = "[[";
	std::string strneedlediv = "|";
	std::string strneedleend = "]]";
	std::string codeneedlestart = "{";
	std::string codeneedleend = "}";

};
