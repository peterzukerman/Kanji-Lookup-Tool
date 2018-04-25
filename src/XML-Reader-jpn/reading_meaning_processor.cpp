#include "reading_meaning_processor.h"
#include "conversion_utils.h"
#include "xml_utils.h"

using namespace std;
using namespace tinyxml2;

const int KANJI_FIRST = 0x4E00;
const int KANJI_LAST = 0x9FBF;

//Get the things we are interested in from the character xml
ReadingMeaning getReadingMeaningFromCharacterElement(XMLElement* characterElem) {
	ReadingMeaning rmData;
	XMLElement* rmElem = characterElem->FirstChildElement("reading_meaning");
	if (!rmElem) {
		return rmData;
	}

	XMLElement* rmGroup = rmElem->FirstChildElement("rmgroup");
	if (!rmGroup) {
		return rmData;
	}

	const char* readingJaOn = getTextFromChildElemWithAttribute(rmGroup, "reading", "r_type", "ja_on");
	if (readingJaOn) {
		rmData.readingJaOn = toCodepointHex(readingJaOn);
	}

	const char* readingJaKun = getTextFromChildElemWithAttribute(rmGroup, "reading", "r_type", "ja_kun");
	if (readingJaKun) {
		rmData.readingJaKun = toCodepointHex(readingJaKun);
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

	return rmData;
}

bool isKanji(const string codePoint) {
	int cpValue = hexToInt(codePoint);
	return (cpValue >= KANJI_FIRST && cpValue <= KANJI_LAST);
}

map<string, ReadingMeaning> extractReadingMeaningFromXmlFile(const char* fileName, int& totalCount, int& nonKanjiCount) {
	XMLDocument doc;
	doc.LoadFile(fileName);

	XMLElement* root = doc.FirstChildElement("kanjidic2");
	XMLElement* characterElem = root->FirstChildElement("character");

	map<string, ReadingMeaning> symbolsReadingMeaning;

	//for each character in the xml, get its code point and reading/meaning params and add to the map:
	while (characterElem) { 
		XMLElement* codePointElem = characterElem->FirstChildElement("codepoint");
		const char* codePoint = getTextFromChildElemWithAttribute(codePointElem, "cp_value", "cp_type", "ucs");
		if (codePoint) {
			totalCount++;
			if (isKanji(codePoint)) {
				ReadingMeaning rm = getReadingMeaningFromCharacterElement(characterElem);
				if (rm.meanings.size() > 0) {
					symbolsReadingMeaning[codePoint] = rm;
				}
			}
			else {
				nonKanjiCount++;
			}
		}

		//Move to the next character element:
		characterElem = characterElem->NextSiblingElement("character");
	}

	return symbolsReadingMeaning;
}