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
	readingMeaningMap = extractReadingMeaningFromXmlFile(READING_MEANING_FILE);
	exampleSentenceMap = buildCharacterToSampleSentencesMap(EXAMPLE_SENTENCE_FILE, EXAMPLE_SENTENCE_FILE_DELIMITER);
}

void ofApp::setup()
{
	ofSetWindowShape(1920, 1080);
	ofSetWindowPosition(ofGetScreenWidth() / 2 - ofGetWidth() / 2, 0);
	initializeMaps();
	
	ofxDatGuiThemeCustom* theme = new ofxDatGuiThemeCustom();
	input = new ofxDatGuiTextInput("Character:", "");
	input->setTheme(theme);
	input->onTextInputEvent(this, &ofApp::onTextInputEvent);
	input->setWidth(1000, .2);
	input->setPosition(ofGetWidth() / 2 - input->getWidth() / 2, 240);

	//characterReadingMeaningOutput.load("ofxbraitsch/fonts/msmincho.ttf", 32, true, true, false, 0.3f);
	
	font.load("ofxbraitsch/fonts/sazanami-gothic.ttf", 22, true, true, false, 0.3f);
	ofSetWindowPosition(0, 0);

	// instantiate a basic button and a toggle button //
	button = new ofxDatGuiButton("Go");

	// position the components in the middle of the screen //
	positionButtons();

	// and register to listen for events //
	button->onButtonEvent(this, &ofApp::onButtonEvent);
}

void ofApp::onTextInputEvent(ofxDatGuiTextInputEvent e)
{
	// text input events carry the text of the input field //
	cout << "From Event Object: " << e.text << endl;
	// although you can also retrieve it from the event target //
	cout << "From Event Target: " << e.target->getText() << endl;
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
	//characterReadingMeaningOutput.drawString("Hajimemashite", 20, 20, ofxMultiLineText::Center);
	
}

void ofApp::drawText()
{
	//string str = "‚Í‚¶‚ß‚Ü‚µ‚Ä"; //input->getText(); 
	if (meaning.length() > 0) {
		string output = "Meaning: " + meaning + "\n" + "Readings: " +
			readingKun + "\n" + readingOn + "\n" + "Examples: " + exampleSentences;
		ofRectangle bounds = font.getStringBoundingBox(exampleSentences, ofGetWidth() / 2, ofGetHeight() / 2);
		ofSetColor(ofColor::black);
		font.drawString(output, 50, 300);
	}
}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
	// we have a couple ways to figure out which button was clicked //

	// we can compare our button pointer to the target of the event //
	if (e.target == button) {
		meaning = "";
		readingOn = "";
		readingKun = "";
		exampleSentences = "";

		string inputtedCharacter = input->getText();
		int charAsInt = hexToInt(inputtedCharacter);
		vector<SentencePair*> v = exampleSentenceMap[charAsInt];
		int sentencesAdded = 0;
		
		for each (SentencePair* sp in v) {
			if (sentencesAdded > 3) {
				break;
			}
			exampleSentences += sp->EnglishSentence + "\n" + sp->JapaneseSentence.substr(0, 50) + "\n" + "\n";
			sentencesAdded++;
		}

		
		ReadingMeaning charRM = readingMeaningMap[charAsInt];
		for each (string s in charRM.meanings){
			meaning += s + "\n";
		}           // utf8chr(charRM.readingJaOn);
		readingOn = charRM.readingJaOn;
		readingKun = charRM.readingJaKun;
		this->update();


	}

}

void ofApp::positionButtons()
{
	button->setPosition(ofGetWidth() / 2 + input->getWidth() / 2, 240);
}


