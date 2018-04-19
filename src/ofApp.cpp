#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
/*	gui.setup();
	gui.add(intSlider.setup("int slider", 0, 0, 300));
	gui.add(toggle.setup("toggle", false));
	gui.add(button.setup("button"));
	*/
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
//	gui.draw();
	ofDrawBitmapString("Press spacebar to open a csv file, \"s\" to save the processed output", 300, 300);


	for (unsigned int i = 0; i<loadedImages.size(); i++) {
		loadedImages[i].draw(0, 20);
	}

	for (unsigned int i = 0; i<processedImages.size(); i++) {
		processedImages[i].draw(processedImages[i].getWidth(), 20);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == ' ') {

		//Open the Open File Dialog
		ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a CSV");

		//Check if the user opened a file
		if (openFileResult.bSuccess) {

			ofLogVerbose("User selected a file");

			//We have a file, check it and process it
			processOpenFileSelection(openFileResult);

		}
		else {
			ofLogVerbose("User hit cancel");
		}
	}

	if (key == 's') {

		if (processedImages.size() == 0) {
			//User is trying to save without anything to output - bail
			return;
		}

		//
		ofFileDialogResult saveFileResult = ofSystemSaveDialog(ofGetTimestampString() + "." + ofToLower(originalFileExtension), "Save your file");
		if (saveFileResult.bSuccess) {
			processedImages[0].save(saveFileResult.filePath);
		}
	}
}

bool sortColorFunction(ofColor i, ofColor j) {
	return (i.getBrightness()<j.getBrightness());
}


void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult) {

	ofLogVerbose("getName(): " + openFileResult.getName());
	ofLogVerbose("getPath(): " + openFileResult.getPath());

	ofFile file(openFileResult.getPath());

	if (file.exists()) {
		//Limiting this example to one image so we delete previous ones
		processedImages.clear();
		loadedImages.clear();

		ofLogVerbose("The file exists - now checking the type via file extension");
		string fileExtension = ofToUpper(file.getExtension());

		//We only want csv
		if (fileExtension == "CSV") {

			//Save the file extension to use when we save out
			originalFileExtension = fileExtension;

			//Load the selected image
			ofFile file;
			file.read(openFileResult.getPath());
			loadedImages.push_back(file);

			processedImages.push_back(file);
		}
	}

}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
