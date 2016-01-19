#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//consoleListener.setup(this);
	ofHideCursor();
	shader.load("shaderExample2");

	imgTest.load("images/bikers.jpg");
	
	fbo.allocate(ofGetWidth(), ofGetHeight());
	fbo.begin();
		ofClear(0, 0, 0, 0);
		imgTest.draw(0, 0, ofGetWidth(), ofGetHeight());
	fbo.end();

	fbo2.allocate(ofGetWidth(), ofGetHeight());
	fbo2.begin();
		ofClear(0, 0, 0, 0);
	fbo2.end();

}

//--------------------------------------------------------------
void ofApp::update(){
    //
	fbo.begin();
		ofClear(0, 0, 0, 0);
		shader.begin();
//			shader.setUniformTexture("tex0", omxPlayer.getTextureReference(), omxPlayer.getTextureID());
			shader.setUniformTexture("tex0", imgTest.getTexture(),1);
			shader.setUniformTexture("backbuffer", imgTest.getTexture(),2);
			shader.setUniform1f("time", ofGetElapsedTimef());
			shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
			imgTest.draw(0, 0, ofGetWidth(), ofGetHeight());
		shader.end();
	fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    /*ofSetColor(255);
    
    shader.begin();
    
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    
    shader.end();*/

fbo.draw(0, 0);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
