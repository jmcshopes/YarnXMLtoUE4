// XMLTranslator.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>
#include <vector>
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
	
	//std::string xmlstring("Sentence time boys! [[Go to the next node|NextNode]] [[No thanks|NoThanks]] node node node");
	


	std::string NPCDialogue = ParserInstance.DialogueParser(XMLReturn);
	std::cout << "Oleya: " << NPCDialogue << "\n";

	TMap<int, std::pair<std::string, std::string>> OptionsReturned = ParserInstance.OptionsParser(XMLReturn);
	TMap<int, std::pair<std::string, std::string>>::iterator it = OptionsReturned.begin();
	while (it != OptionsReturned.end())
	{
		std::pair<std::string, std::string> StringPair = it->second;

		std::cout << it->first + 1 << ". " << StringPair.first << std::endl;
		it++;
	}
	int PlayerChoice;
	std::cin >> PlayerChoice;
	std::pair<std::string, std::string> PlayerChoicePair = OptionsReturned[PlayerChoice - 1];
	std::string Node = PlayerChoicePair.second;
	std::cout << "\n\n";
	return Node;
}

std::string OptionCrafter(std::string node) // TODO EXPORT This will be the method for acquiring strings from Yarn
{
	std::string NPCName = "Oleya";
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