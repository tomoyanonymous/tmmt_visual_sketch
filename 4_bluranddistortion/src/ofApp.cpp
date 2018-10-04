#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
		shaderBlurX.load("shadersGL3/shaderBlurX");
        shaderBlurY.load("shadersGL3/shaderBlurY");
    shaderDistortion.load("shadersGL3/shaderDistortion");
    shaderPnoise.load("shadersGL3/shaderPnoise");

    img.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR_ALPHA);
     distortion.allocate(ofGetWidth(),ofGetHeight());
    fboBlurOnePass.allocate(ofGetWidth(),ofGetHeight());
    fboBlurTwoPass.allocate(ofGetWidth(),ofGetHeight());
    distortion.begin();
    ofClear(0,0,0,255);
    distortion.end();
    fboBlurOnePass.begin();
    ofClear(0,0,0,255);
    fboBlurOnePass.end();
    fboBlurTwoPass.begin();
    ofClear(0,0,0,255);
    fboBlurTwoPass.end();

    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    
    
    float dist = ofMap(mouseY, 0, ofGetHeight(), 0, 2, true);
    blur = ofMap(mouseX, 0, ofGetWidth(), 0, 2, true)*(atan(1.3*sin(time))*2+2);

    //----------------------------------------------------------
    distortion.begin();

    shaderDistortion.begin();
    shaderDistortion.setUniformTexture("original", img.getTexture(), 1);
    shaderDistortion.setUniform1f("distAmnt", dist);
    shaderDistortion.setUniform1f("distdist", distdist);

    fboBlurTwoPass.draw(0, 0); // fed back

    shaderDistortion.end();

    distortion.end();


    //----------------------------------------------------------
    fboBlurOnePass.begin();

    shaderBlurX.begin();
    shaderBlurX.setUniform1f("blurAmnt", blur);
    
    distortion.draw(0, 0);

    shaderBlurX.end();

    fboBlurOnePass.end();
    
    //----------------------------------------------------------
    ofSetColor(ofColor::white);

    fboBlurTwoPass.begin();
    if(reset){
        time=0;
        shaderPnoise.begin();
        shaderPnoise.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
        shaderPnoise.setUniform1f("scale", 5.);
        shaderPnoise.setUniform1f("time", ofGetElapsedTimef());

        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        shaderPnoise.end();
        reset=false;
    }else{
    shaderBlurY.begin();
    shaderBlurY.setUniform1f("blurAmnt", blur);

    fboBlurOnePass.draw(0, 0);

    shaderBlurY.end();
    }

    fboBlurTwoPass.end();

    //----------------------------------------------------------
    fboBlurTwoPass.draw(0, 0);
    time += 0.008;
    ofDrawBitmapString(distdist,10,10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'z'){
        distdist+=0.1;
    }else if(key=='x'){
        distdist-=0.1;
    }
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
    
    reset=true;
    
    
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
