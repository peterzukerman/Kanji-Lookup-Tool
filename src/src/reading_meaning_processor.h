#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct ReadingMeaning {
	int readingJaOn; //Unicode code points
	int readingJaKun;
	vector<string> meanings;
};

map<int, ReadingMeaning> extractReadingMeaningFromXmlFile(const char*);