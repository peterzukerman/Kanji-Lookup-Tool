#include "ofApp.h"
#include "reading_meaning_processor.h"
#include "sentences_processor.h"
#include "conversion_utils.h"
#include "tinyxml2.h"

/*
Simple example to demonstrate the Text Input Component.
Type something into the component and see it displayed in the center of the screen
https://github.com/braitsch/ofxDatGui @braitsch
*/
using namespace std;

void ofApp::initializeMaps() {
	cout << "Loading reading and meaning definition, please wait...  \n";
	readingMeaningMap = extractReadingMeaningFromXmlFile(READING_MEANING_FILE);

	cout << "Loading example sentences, please wait...";
	exampleSentenceMap = buildCharacterToSampleSentencesMap(EXAMPLE_SENTENCE_FILE, EXAMPLE_SENTENCE_FILE_DELIMITER);
}

void ofApp::setup()
{
	ofSetWindowShape(1920, 1080);
	ofSetWindowPosition(ofGetScreenWidth() / 2 - ofGetWidth() / 2, 0);
	initializeMaps();
	
	ofxDatGuiThemeCustom* theme = new ofxDatGuiThemeCustom();
	input = new ofxDatGuiTextInput("Input:", "");
	input->setTheme(theme);
	input->setWidth(900, 0.3);
	input->setPosition(ofGetWidth() / 2 - input->getWidth() / 2, 240);

	mainFont.load("ofxbraitsch/fonts/sazanami-gothic.ttf", 22, true, true, false, 0.3f);
	kanjiFont.load("ofxbraitsch/fonts/sazanami-gothic.ttf", 240, true, true, false, 0.3f);
	titleFont.load("ofxbraitsch/fonts/sazanami-gothic.ttf", 40, true, true, false, 0.3f);
	ofSetWindowPosition(0, 0);

	// instantiate a basic button //
	button = new ofxDatGuiButton("Go");
	button->setTheme(theme);
	button->setWidth(150);
	button->setBackgroundColor(ofColor::grey);

	// position the button to the right of the text box //
	button->setPosition(ofGetWidth() / 2 + input->getWidth() / 2, 240);

	// and register to listen for events //
	button->onButtonEvent(this, &ofApp::onButtonEvent);
}


void ofApp::update()
{
	input->update();
	button->update();
}

void ofApp::draw()
{
	input->draw();
	button->draw();
	drawText();
	
}

void ofApp::drawText()
{
	ofSetColor(ofColor::chocolate);
	titleFont.drawString("Kanji Character Lookup", ofGetWidth() / 2 - input->getWidth() / 2 + 200, 130);
	string output = "";
	if (meaning.length() > 0) {
		output = "Meaning: \n" + meaning + "\n" + "Readings: \n Kunyomi: " +
			readingKun + "\n Onyomi: " + readingOn + "\n" + "\n" + "Examples: \n" + exampleSentences;
	}
	else {
		output = "This character has no entries";
	}

	if (inputKanjiAsUnicode > 0 )
	{
		ofSetColor(ofColor::black);
		mainFont.drawString(output, 50, 350);
		string utf8Char = utf8chr(inputKanjiAsUnicode);
		ofSetColor(ofColor::darkRed);
		kanjiFont.drawString(utf8Char, 1200, 600);
	}
}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{


	// we can compare our button pointer to the target of the event //
	if (e.target == button) {

		clearDataVariables();

		string inputtedCharacter = "0x" + input->getText();

		//add check to make sure input actually is in hex
		inputKanjiAsUnicode = hexToInt(inputtedCharacter);
		vector<SentencePair*> v = exampleSentenceMap[inputKanjiAsUnicode];
		int sentencesAdded = 0;
		
		for each (SentencePair* sp in v) {
			if (sentencesAdded > 3) {
				break;
			}
			exampleSentences += sp->EnglishSentence + "\n" + sp->JapaneseSentence.substr(0, 150) + "\n" + "\n";
			sentencesAdded++;
		}

		
		ReadingMeaning charRM = readingMeaningMap[inputKanjiAsUnicode];
		for each (string s in charRM.meanings){
			meaning += "\t" + s + "\n";
		}           // utf8chr(charRM.readingJaOn);
		readingOn = charRM.readingJaOn;
		readingKun = charRM.readingJaKun;
		this->update();


	}

}

void ofApp::clearDataVariables()
{
	meaning = "";
	readingOn = "";
	readingKun = "";
	exampleSentences = "";
	inputKanjiAsUnicode = 0;
}



