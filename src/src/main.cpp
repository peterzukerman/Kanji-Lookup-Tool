#include "reading_meaning_processor.h"
#include "sentences_processor.h"

using namespace std;

int main(int argc, char** argv) {
	
	cout << "Loading the XML file..." << endl;

	const char* xmlFile = "C:\\Users\\pzuke\\github\\kanji-helper\\bin\\data\\kanjidic2.xml";
	int totalCount = 0, nonKanjiCount = 0;
	map<int, ReadingMeaning> rm = extractReadingMeaningFromXmlFile(xmlFile);
	
	cout << "Done! Total records in the ReadingMeaning map: " << rm.size() << endl;		

	cout << endl << "Loading the Sentences file..." << endl;

	string fileName = "C:\\Users\\pzuke\\Desktop\\sentences.csv";
	char delimiter = ',';

	map<int, vector<SentencePair*>> m = buildCharacterToSampleSentencesMap(fileName, delimiter);
	
	cout << "Done! There are " << m.size() << " entries in the Sentences map" << endl;

	return 0;
}