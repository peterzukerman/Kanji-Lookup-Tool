#include "reading_meaning_processor.h"
#include "conversion_utils.h"
#include "xml_utils.h"

using namespace std;
using namespace tinyxml2;

//Get the things we are interested in from the character xml
//XML hierarchy: character -> reading_meaning -> rmgroup -> reading elements
ReadingMeaning getReadingMeaningFromCharacterElement(XMLElement* characterElem) {
	ReadingMeaning rmData;
	XMLElement* rmElem = characterElem->FirstChildElement("reading_meaning");
	if (rmElem) {
		XMLElement* rmGroup = rmElem->FirstChildElement("rmgroup");
		if (rmGroup) {
			const char* readingJaOn = getTextFromChildElemWithAttribute(rmGroup, "reading", "r_type", "ja_on");
			if (readingJaOn) {
				rmData.readingJaOn = toCodepoint(readingJaOn);
			}

			const char* readingJaKun = getTextFromChildElemWithAttribute(rmGroup, "reading", "r_type", "ja_kun");
			if (readingJaKun) {
				rmData.readingJaKun = toCodepoint(readingJaKun);
			}

			vector<string> meanings;
			XMLElement* meaningElem = rmGroup->FirstChildElement("meaning");
			while (meaningElem) {
				if (meaningElem->FirstAttribute() == NULL) { //Only want meanings with no attribute
					meanings.push_back(meaningElem->GetText());
				}
				meaningElem = meaningElem->NextSiblingElement("meaning");
			}

			rmData.meanings = meanings;
		}
	}

	return rmData;
}

map<int, ReadingMeaning> extractReadingMeaningFromXmlFile(const char* fileName) {
	XMLDocument doc;
	doc.LoadFile(fileName);

	XMLElement* root = doc.FirstChildElement("kanjidic2");
	XMLElement* characterElem = root->FirstChildElement("character");

	map<int, ReadingMeaning> symbolsReadingMeaning;

	//for each character in the xml, get its code point and reading/meaning params and add to the map:
	while (characterElem) { 
		XMLElement* codePointElem = characterElem->FirstChildElement("codepoint");
		const char* codePoint = getTextFromChildElemWithAttribute(codePointElem, "cp_value", "cp_type", "ucs");
		if (codePoint) {			
			if (isKanji(codePoint)) {
				ReadingMeaning rm = getReadingMeaningFromCharacterElement(characterElem);
				if (rm.meanings.size() > 0) {
					int codePointAsInt = hexToInt(codePoint);
					symbolsReadingMeaning[codePointAsInt] = rm;
				}
			}
		}

		//Move to the next character element:
		characterElem = characterElem->NextSiblingElement("character");
	}

	return symbolsReadingMeaning;
}