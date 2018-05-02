#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

#include "utf8.h"

#include "conversion_utils.h"

using namespace std;

struct SentencePair {
	string JapaneseSentence;
	string EnglishSentence;

	SentencePair(string jap, string eng) {
		this->JapaneseSentence = jap;
		this->EnglishSentence = eng;
	}
};

map<int, vector<SentencePair*>> buildCharacterToSampleSentencesMap(string, char);
