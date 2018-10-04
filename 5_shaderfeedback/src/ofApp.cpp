#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    shader.load("myshader");
    centercircle.load("centercircle");
    noise.load("shaderPnoise");
    blurx.load("shaderBlurX");
    blury.load("shaderBlurY");

    fbo1.allocate(ofGetWidth(),ofGetHeight());
    fbo1.begin();
    ofClear(0);
    noise.begin();
    ofSetColor(255,255);
    noise.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    noise.setUniform1f("scale", 5.);
    noise.setUniform1f("rgbcorel", 0.1);
    noise.setUniform1f("time", ofGetElapsedTimef());
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    
    noise.end();
    fbo1.end();
    fbo2.allocate(ofGetWidth(),ofGetHeight());
    fbo2.begin();
    ofClear(0);
    fbo2.end();

    
}

//--------------------------------------------------------------
void ofApp::update(){
    fbo1.begin();
    blurx.begin();
    blurx.setUniform1f("blurAmnt",5.0*(float)mouseY/ofGetHeight() );
    fbo1.draw(0,0);
    blurx.end();
    
    blury.begin();
    blury.setUniform1f("blurAmnt", 5.0*(float)mouseY/ofGetHeight());
    fbo1.draw(0,0);
    blury.end();
    shader.begin();
    shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
//    shader.setUniform1f("scale",5.0*(float)mouseX/ofGetWidth());
    myscale = -cos(time*1.)*2.+2.;
    myscale = std::fmax(myscale-0.2,0);
    shader.setUniform1f("scale",myscale);

    shader.setUniform1f("time", time);
    fbo1.draw(0,0);
    shader.end();

    fbo1.end();
//    fbo2.begin();
//    fbo1.draw(0,0);
//
//    fbo2.end();
    time+=1/60.;
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo1.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key==' '){
    fbo1.begin();
    ofClear(0);
    noise.begin();
    ofSetColor(255,255);
    noise.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    noise.setUniform1f("scale", 5.);
    noise.setUniform1f("rgbcorel", 0.01);
    noise.setUniform1f("time", ofGetElapsedTimef());
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    
    noise.end();
        fbo1.end();
        
    }
    if(key=='r'){
        time= (int)ofRandom(10000) *TWO_PI;
        cout <<time<<endl;
        fbo1.begin();
        centercircle.begin();
        centercircle.setUniform2f("resolution", ofGetWidth(), ofGetHeight());

        ofClear(0);
        ofSetColor(255,255);
        ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
        centercircle.end();
        fbo1.end();
        
    }
    if(key=='f'){
        
//        ofSetWindowShape(1280, 720);
        ofToggleFullscreen();
        fbo1.allocate(ofGetWidth(),ofGetHeight());
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
