#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofSetupOpenGL(1920,1440,OF_WINDOW);			// <-------- setup the GL context

	ofRunApp(new ofApp());
}