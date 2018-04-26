#pragma once
#include <string>
#include <sstream>

using namespace std;

const int KANJI_FIRST = 0x4E00;
const int KANJI_LAST = 0x9FBF;

int toCodepoint(const std::string &u);
std::string toCodepointHex(const std::string &u);
int hexToInt(const std::string &u);
bool isKanji(const string codePoint);
bool isKanji(int codePoint);
