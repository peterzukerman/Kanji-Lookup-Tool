#include "sentences_processor.h"
#include "conversion_utils.h"

using namespace std;

//Building a map connecting each Jap symbol (codePoint) to the list (vector) of all sentence pairs for that symbol:	
map<int, vector<SentencePair*>> buildCharacterToSampleSentencesMap(string sentencesFileName, char fieldDelimiter) {

	ifstream ip(sentencesFileName);
	if (!ip.is_open()) {
		throw new exception("Unable to open the sentences file");
	}

	map<int, vector<SentencePair*>> characterToExampleMap;

	int recordCount = 0;
	string id1, id2, jpnSentence, engSentence, jpnReading;

	while (ip.good()) {
		getline(ip, id1, fieldDelimiter);
		getline(ip, id2, fieldDelimiter);
		getline(ip, jpnSentence, fieldDelimiter);
		getline(ip, engSentence, fieldDelimiter);
		getline(ip, jpnReading, '\n');

		//The sentence pair in this row:
		SentencePair* sp = new SentencePair(jpnSentence, engSentence);

		/*For each UTF8 symbol in the jap sentence, use that symbol's code point
		as the map key and add the sentence pair (pointer) to the map's value.
		That pointer will be the same for all the symbols in the sentence, so we use very litle memory.

		We use the UTF8-CPP library (utf8::next) to traverse the sentence.
		*/

		char* start = (char*)jpnSentence.c_str();
		char* end = start + jpnSentence.size() + 1; 

		do {
			//utf8::next() gets the code of the next utf-8 symbol and moves the start pointer
			int codePoint = utf8::next(start, end); 
			if (isKanji(codePoint)) {
				//We have a legitimate code point, use it to set the map entry:
				if (characterToExampleMap.count(codePoint) == 0) { //no entry yet, make one
					vector<SentencePair*> v;                       //with an empty vector
					characterToExampleMap[codePoint] = v;
				}

				//Add the sentence pair to other SPs for this character:
				characterToExampleMap[codePoint].push_back(sp);
			}
		} while (start < end);

		recordCount++;
		if (recordCount % 5000 == 0) {
			cout << "Processed " << recordCount << " records" << endl;
		}
	}

	ip.close();

	return characterToExampleMap;
}

