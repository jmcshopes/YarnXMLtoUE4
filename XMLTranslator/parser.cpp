
#include "parser.h"
#include <iostream>       // TODO Remove this when not dependent on std::cout
#include <vector>
#include <string>         // std::string

TMap<int, std::pair<std::string, std::string>> Parser::OptionsParser(std::string strhaystack)
{
	//std::cout << "Haystack sentence is: " << strhaystack << "\n";
	//std::cout << "Needle phrase is: " << strneedlestart << " and end is " << strneedleend << "and Div is " << strneedlediv << " \n";
	TMap<int, std::pair<std::string, std::string>> OptionMap;

	std::size_t found = 0;
	int i = 0;

	while (found != std::string::npos) {
		found = strhaystack.find(strneedlestart, found + 1);
		if (found != std::string::npos) {
			//std::cout << "Entry " << i << " start   '" << strneedlestart << "' at: " << found << '\n';
			std::size_t start = found;
			found = strhaystack.find(strneedlediv, found + 1);
			//std::cout << "Entry " << i << " divider '" << strneedlediv << "' at: " << found << '\n';
			std::size_t div = found;
			found = strhaystack.find(strneedleend, found + 1);
			//std::cout << "Entry " << i << " end     '" << strneedleend << "' at: " << found << '\n';
			std::size_t end = found;
			std::string option = strhaystack.substr(start + 2, div - start - 2);
			std::string node = strhaystack.substr(div + 1, end-div - 1);
			//std::cout << "Node " << i << " is       " << node << '\n';
			std::pair <std::string, std::string> pairstrings (option, node);
			OptionMap.insert(std::pair<int, std::pair<std::string,std::string>>(i, pairstrings));
			//std::cout << "Option Segment: '" << option << "'\n";
		}

		i++;
	}

	return OptionMap;
}

std::string Parser::DialogueParser(std::string strhaystack)
{
	
	std::size_t DialogueEnd = strhaystack.find(strneedlestart,0);
	std::string DialogueString = strhaystack.substr(0, DialogueEnd);
	return DialogueString;
}

std::vector<playeroptiontype> Parser::ParseOptions(std::string strhaystack)
{
	std::vector<playeroptiontype> OptionsVector;
	playeroptiontype WorkingOption;

	std::size_t found = 0;
	std::size_t codefound = 0;
	int i = 0;

	while (found != std::string::npos) {
		found = strhaystack.find(strneedlestart, found + 1);
		if (found != std::string::npos) {
			std::size_t start = found;
			found = strhaystack.find(strneedlediv, found + 1);
			std::size_t div = found;
			found = strhaystack.find(strneedleend, found + 1);
			std::size_t end = found;
			
			std::string OptionPlain = strhaystack.substr(start + 2, div - start - 2);
			codefound = OptionPlain.find(codeneedlestart, codefound);
			if (codefound != std::string::npos) {
				std::size_t codestart = codefound;
				codefound = OptionPlain.find(codeneedleend, codefound + 1);
				std::size_t codeend = codefound;
				WorkingOption.optioncode = OptionPlain.substr(codestart + 1, codeend - 1);
				WorkingOption.option = OptionPlain.substr(codeend + 1, std::string::npos);
			}
			else {
				WorkingOption.option = OptionPlain;
			}
			WorkingOption.index = i;
			WorkingOption.node = strhaystack.substr(div + 1, end - div - 1);
			OptionsVector.push_back(WorkingOption);
			
		}

		i++;
	}

	return OptionsVector;
}
