#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//consoleListener.setup(this);
	//ofHideCursor();
	shader.load("grayScott");
	shaderTest.load("shaderExample");
	
	imgTest.load("images/bikers.jpg");
	
	fboTextureReference.allocate(ofGetWidth(), ofGetHeight());
	fboTextureReference.begin();
		ofClear(0, 0, 0, 0);
		//imgTest.draw(0, 0, ofGetWidth(), ofGetHeight());
	fboTextureReference.end();


	fbo.allocate(ofGetWidth(), ofGetHeight());
	fbo.begin();
		ofClear(0, 0, 0, 0);
		imgTest.draw(0, 0, ofGetWidth(), ofGetHeight());
	fbo.end();

	int 	internalFormat = GL_RGBA;
	 pingPong.allocate( ofGetWidth(), ofGetHeight(), internalFormat);
}

//--------------------------------------------------------------
void ofApp::update(){
    //
	//f+=0.00001f;
//	k+=0.00001f;
	updatePingPong();

		fbo.begin();
		ofClear(0, 0, 0, 0);
		shaderTest.begin();
//			shaderTest.setUniformTexture("tex0", omxPlayer.getTextureReference(), omxPlayer.getTextureID());
			shaderTest.setUniformTexture("tex0", imgTest.getTexture(),1);
			shaderTest.setUniformTexture("backbuffer", imgTest.getTexture(),2);
			shaderTest.setUniform1f("time", ofGetElapsedTimef());
			shaderTest.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
			imgTest.draw(0, 0, ofGetWidth(), ofGetHeight());
		shaderTest.end();
	fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
   

fbo.draw(0, 0,ofGetWidth()/2,ofGetHeight()/2);

 ofPushStyle();
    ofEnableAlphaBlending();
    pingPong.dst->draw(ofGetWidth()/2,ofGetHeight()/2,ofGetWidth()/2,ofGetHeight()/2);
    ofPopStyle();

   ofDrawBitmapString("GrayScott Reaction Diffusion", 15,15);
    ofDrawBitmapString("K ( mouseX ): " + ofToString(k) , 15,35);
    ofDrawBitmapString("F ( mouseY ): " + ofToString(f) , 15,55);
}

/* copied from ofxFX */

void ofApp::updatePingPong(){
    ofPushStyle();
    ofSetColor(255,255);
	int passes = 1;
    // This process is going to be repeated as many times passes variable specifies
    for(int pass = 0; pass < passes; pass++) {
        
        // All the processing is done on the pingPong ofxSwapBuffer (basicaly two ofFbo that have a swap() funtion)
        pingPong.dst->begin();
        
        ofClear(0,0,0,255);
        ofDisableAlphaBlending(); // Defer alpha blending until .draw() to keep transparencies clean.
        shader.begin();

        shader.setUniformTexture("tex0", imgTest.getTexture(),1);
	//shader.setUniformTexture("tex0", fboTextureReference.getTexture(),1);
	shader.setUniformTexture("backbuffer", pingPong.src->getTextureReference(), 2);
	
        shader.setUniform1f( "diffU", (float)diffU);
        shader.setUniform1f( "diffV", (float)diffV);
        shader.setUniform1f( "f", (float)f );
        shader.setUniform1f( "k", (float)k );

	imgTest.draw(0, 0, ofGetWidth(), ofGetHeight());        
	//ofRect(0, 0, ofGetWidth(), ofGetHeight());
	shader.end();
        
        pingPong.dst->end();
        
        // Swap the ofFbos. Now dst is src and src is dst. Each iteration writes to
        // dst and uses src as a backbuffer, where the previous frame is kept.
        pingPong.swap();
    }
    
    pingPong.swap(); // After the loop the finished render will be at the src ofFbo of the ofxSwapBuffer
                     // this extra swap() call will put it on the dst one. Which sounds more reasonable...
    
    ofPopStyle();
    
  //  bUpdate = false;
};


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
 
    f = ofMap(mouseX,0, ofGetWidth(),0.005,0.095,true);
    k = ofMap(mouseY,0,ofGetHeight(),0.01,0.028,true);

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
