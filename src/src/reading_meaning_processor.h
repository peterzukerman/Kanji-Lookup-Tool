#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct ReadingMeaning {
	string readingJaOn; 
	string readingJaKun;
	vector<string> meanings;
};

map<int, ReadingMeaning> extractReadingMeaningFromXmlFile(const char*);