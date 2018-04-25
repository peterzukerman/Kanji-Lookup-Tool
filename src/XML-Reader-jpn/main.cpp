#include "reading_meaning_processor.h"

using namespace std;

int main(int argc, char** argv) {
	const char* xmlFile = "C:\\Personal\\Petya\\JapProject\\kanjidic2.xml";
	int totalCount = 0, nonKanjiCount = 0;
	map<string, ReadingMeaning> rm = extractReadingMeaningFromXmlFile(xmlFile, totalCount, nonKanjiCount);
	
	cout << "Total records processed: " << totalCount << endl
		<< "Records saved: " << rm.size() << endl
		<< "Non-kanji records found: " << nonKanjiCount << endl;

	return 0;
}