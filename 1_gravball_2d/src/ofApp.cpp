#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
//    balls = new Gravityball[5];
    ofSetBackgroundColor(0, 0, 0);
    ofSetBackgroundAuto(false);
    ofSetFrameRate(60);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    center.set(ofGetWidth()/2,ofGetHeight()/2,0);
    for (int i = 0; i<10; i++) {
        for(int j=0;j<10;j++){
        int x = ofMap(i,0,9,0,ofGetWidth());
        int y = ofMap(j,0,9,0,ofGetHeight());
        balls[i+j*10].setup((float)x,(float)y);
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    float amp;
    for (int i = 0; i<NUM; i++) {
        ofVec3f tempvec;
        int sign;
        
        for (int j = 0; j<NUM; j++) {
            if(balls[i].vel.length()<1.5){
                sign=-1;
            }else{
                sign=1;
            }
            if (i!=j){
                amp = sign*balls[i].pos.distance(balls[j].pos);

                tempvec += balls[i].grav* amp*amp/10000000 * (balls[j].pos-balls[i].pos).normalize();
            }
            amp = balls[i].pos.distance(center);
            tempvec += amp*amp/500000000 *(center-balls[i].pos).normalize();
        }
        balls[i].vel += tempvec;
        
        if(balls[i].vel.length()<0.2){
            balls[i].trimspeed(true);
        }else if( balls[i].vel.length()>15){
            balls[i].trimspeed(false);
        }
        balls[i].update();
    }
    
}
void ofApp::draw(){
 
    if(reset){
        ofSetColor(0, 0, 0);
        reset = !reset;
        ofDisableBlendMode();
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

    }else{
           if (skip==0){
        ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
        ofSetColor(255, 255);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
        ofSetColor(1, 1, 1);

        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
//               for(int i=0;i<NUM;i++){
//                   balls[i].crotate += 0.5;
//               }

    }
    }
    skip = (skip+1)%12;

    ofEnableBlendMode(OF_BLENDMODE_ADD);

    for(int i=0;i<NUM;i++){
        balls[i].draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' '){
    for (int i = 0; i<NUM; i++) {
        balls[i].setup();
    }
    reset = true;
}
    if(key=='z'){
        globalcrotate =fmod((globalcrotate+11.0),360);
        for(int i=0;i<NUM;i++){
            balls[i].crotate = globalcrotate;
        }
    }
    if(key=='x'){
        globalcrotate =fmod((globalcrotate-11.0),360);
        for(int i=0;i<NUM;i++){
            balls[i].crotate = globalcrotate;
        }
    }
    if(key=='f'){
        fullscreen=!fullscreen;
        ofSetFullscreen(fullscreen);
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
