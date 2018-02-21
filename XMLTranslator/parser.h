#pragma once

#include <string>         // std::string
#include <map>  
#define TMap std::map

struct playeroptiontype {
	int index;
	std::string option;
	std::string node;
};

class Parser {

public:
	TMap<int, std::pair<std::string,std::string>> OptionsParser(std::string);
	std::string DialogueParser(std::string);
	//playeroptiontype OptionStruct();

private:
	std::string strneedlestart = "[["; // These aren't getting picked up at all
	std::string strneedlediv = "|";
	std::string strneedleend = "]]";

};
