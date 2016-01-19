#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//consoleListener.setup(this);
	ofHideCursor();
	shader.load("shaderExample2");
	f+=0.0001f;
	k+=0.0001f;
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
	int 	internalFormat = GL_RGBA;
	 pingPong.allocate( ofGetWidth(), ofGetHeight(), internalFormat);
}

//--------------------------------------------------------------
void ofApp::update(){
    //
	updatePingPong();

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
        
        // The other ofFbo of the ofxSwapBuffer can be accessed by calling the unicode "backbuffer"
        // This is usually used to access "the previous pass", or the original frame for the first pass.
        //if (pass == 0){
        //    shader.setUniformTexture("backbuffer", imgTest.getTextureReference(), 0);
        //} else {
            shader.setUniformTexture("backbuffer", pingPong.src->getTextureReference(), 0);
        //}

        shader.setUniform1f( "diffU", (float)diffU);
            shader.setUniform1f( "diffV", (float)diffV);
            shader.setUniform1f( "f", (float)f );
            shader.setUniform1f( "k", (float)k );

 	pingPong.src->draw(0, 0, ofGetWidth(), ofGetHeight());        
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
     f = ofMap(mouseX,0,640,0.005,0.095,true);
        k = ofMap(mouseY,0,480,0.01,0.028,true);

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
