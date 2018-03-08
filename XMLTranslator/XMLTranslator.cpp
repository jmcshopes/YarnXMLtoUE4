// XMLTranslator.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include "tinyxml2.h"
#include "parser.h"
#include "XMLExtractor.h"

std::string GetPlayerChoice(std::string);
std::string OptionCrafter(std::string);

Parser ParserInstance;
FXMLExtractor XMLRun;

int main()
{
	std::string node = "Start";
	std::string EndNodeString = "node title invalid";

	std::string XMLStringForParsing = OptionCrafter(node);
	while (XMLStringForParsing != EndNodeString) {
		node = GetPlayerChoice(XMLStringForParsing);
		XMLStringForParsing = OptionCrafter(node);
	}
	return 0;
}

std::string GetPlayerChoice(std::string XMLReturn)
{
	std::vector<playeroptiontype> OptionsVector = ParserInstance.ParseOptions(XMLReturn);
	std::string NPCDialogue = ParserInstance.DialogueParser(XMLReturn);
	std::cout << "Oleya: " << NPCDialogue << "\n"; // TODO Extract this
	TMap<int, std::string> NodeMap;
	for (playeroptiontype iter : OptionsVector) {
		std::cout << iter.index + 1 << ". " << iter.option << "\n";
		NodeMap.insert(std::pair<int, std::string>(iter.index + 1, iter.node));
	}
	int PlayerChoice;
	std::cin >> PlayerChoice;
	auto NodeSearch = NodeMap.find(PlayerChoice);
	std::string node = NodeSearch->second;
	return node;
}

std::string OptionCrafter(std::string node)
{
	std::string NPCName = "Oleya"; // TODO abstract this
	std::string Folderbit = XMLRun.FolderPath;
	std::string FilePath = Folderbit+NPCName+".xml";
	//std::cout << FilePath << "\n\n";
	

	tinyxml2::XMLDocument xmlDocToPass;
	tinyxml2::XMLError eResult = xmlDocToPass.LoadFile(FilePath.c_str());
	tinyxml2::XMLDocument *xmlDocToPassPointer;
	xmlDocToPassPointer = &xmlDocToPass;

	std::string fragment = XMLRun.ReadBody(xmlDocToPassPointer, node);
	//std::cout << "The final result is: " << fragment << "\n";
	return fragment;
}
