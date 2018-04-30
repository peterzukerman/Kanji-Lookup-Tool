#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	ofxDatGuiTextInput* input;
	void onTextInputEvent(ofxDatGuiTextInputEvent e);
	int numClicks;
	ofxDatGuiButton* button;
	void positionButtons();
	void onButtonEvent(ofxDatGuiButtonEvent e);

	ofTrueTypeFont font;

};