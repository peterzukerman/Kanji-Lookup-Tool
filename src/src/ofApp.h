#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "ofxTrueTypeFontUC.h"
#include "reading_meaning_processor.h"
#include "sentences_processor.h"
#include "ofxMultiLineText.h"

class ofApp : public ofBaseApp {
	map<int, ReadingMeaning> readingMeaningMap;
	map<int, vector<SentencePair*>> exampleSentenceMap;

	//make configurable in future
	const char* READING_MEANING_FILE = "C:\\Users\\pzuke\\source\\repos\\jpnFinalProject\\bin\\data\\kanjidic2.xml";
	string EXAMPLE_SENTENCE_FILE = "C:\\Users\\pzuke\\source\\repos\\jpnFinalProject\\bin\\data\\sentences.csv";
	char EXAMPLE_SENTENCE_FILE_DELIMITER = ',';
	string meaning = "";
	string readingOn = "";
	string readingKun = "";
	string exampleSentences = "";
	int inputKanjiAsUnicode = 0;

public:
	void setup();
	void update();
	void draw();
	void drawText();
	void initializeMaps();
	

	ofxDatGuiTextInput* input;

	ofxMultiLineText characterReadingMeaningOutput;
	ofxDatGuiButton* button;
	void onButtonEvent(ofxDatGuiButtonEvent e);

	void clearDataVariables();

	ofxTrueTypeFontUC mainFont, kanjiFont, titleFont;

};

class ofxDatGuiThemeCustom : public ofxDatGuiTheme {
public:
	ofxDatGuiThemeCustom()
	{
		font.file = "ofxbraitsch/fonts/sazanami-gothic.ttf";
		font.size = 64;
		layout.height = 72;
		init();
	}
};