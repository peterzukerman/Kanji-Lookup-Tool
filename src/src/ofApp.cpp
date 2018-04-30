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
void ofApp::setup()
{
	ofSetWindowShape(1920, 1080);
	ofSetWindowPosition(ofGetScreenWidth() / 2 - ofGetWidth() / 2, 0);

	const char* xmlFile = "C:\\Users\\pzuke\\source\\repos\\jpnFinalProject\\bin\\data\\kanjidic2.xml";
	map<int, ReadingMeaning> rm = extractReadingMeaningFromXmlFile(xmlFile);

	string fileName = "C:\\Users\\pzuke\\source\\repos\\jpnFinalProject\\bin\\data\\sentences.csv";
	char delimiter = ',';

	map<int, vector<SentencePair*>> m = buildCharacterToSampleSentencesMap(fileName, delimiter);

	input = new ofxDatGuiTextInput("File input", "Type the name of the file containing the characters.");
	input->onTextInputEvent(this, &ofApp::onTextInputEvent);
	input->setWidth(800, .2);
	input->setPosition(ofGetWidth() / 2 - input->getWidth() / 2, 240);
	font.load("ofxbraitsch/fonts/Verdana.ttf", 24);
	numClicks = 0;
	ofSetWindowPosition(0, 0);

	// instantiate a basic button and a toggle button //
	button = new ofxDatGuiButton("Load File");

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
	string str = "Filename " + input->getText();
	ofRectangle bounds = font.getStringBoundingBox(str, ofGetWidth() / 2, ofGetHeight() / 2);
	ofSetColor(ofColor::black);
	font.drawString(str, bounds.x - bounds.width / 2, bounds.y - bounds.height / 2);
}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
	// we have a couple ways to figure out which button was clicked //

	// we can compare our button pointer to the target of the event //
	if (e.target == button) {
		button->setLabel("Loaded");

		// or we can check against the label of the event target //
	}

}

void ofApp::positionButtons()
{
	button->setPosition(ofGetWidth() / 2 + input->getWidth() / 2, 240);
}


