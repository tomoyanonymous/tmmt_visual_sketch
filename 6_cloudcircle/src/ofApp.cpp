#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    for(int i =0;i<1000;i++){
        circlepos[i] = glm::vec2(i,0);
        circlerad[i] = sin((float)i/200)*40+40;
        circlecolor[i] = ofColor(255/2,255/2,255/2);
// 255-155 =100
        //-1-1
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofVec2f pos1= glm::vec2(0,(float)ofGetHeight()/2);
    for(int j = 0;j<5;j++){
        float time = ofGetElapsedTimef();

    for(int i =0;i<1000;i++){
        circlecolor[i].r=125.5+125.5*sin(((float)i/10.+time)*0.12);
        circlecolor[i].g=125.5+125.5*sin(((float)i/10.12+time)*0.11) ;
        circlecolor[i].b=125.5+125.5*sin(((float)i/10.11+time)*0.10);
        ofSetColor(circlecolor[i]);
        ofDrawCircle(circlepos[i], circlerad[i]);
        circlepos[i] += glm::vec2(0.1,0.1+0.5*(sin(time)+1+cos((float)i/100)));
        
        if(circlepos[i].y>ofGetHeight()){
            circlepos[i].y=0;
        }

        
        if(i<999){
            circlerad[i] =  circlerad[i+1];
        }
    }
    
    circlerad[999]=circlerad[0];
    }
    
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
