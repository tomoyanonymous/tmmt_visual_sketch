#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofDisableDepthTest();
//    balls = new Gravityball[5];
    ofSetBackgroundColor(0, 0, 0);
//    ofSetBackgroundAuto(false);
    ofSetFrameRate(60);
//    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    center = {0,0,0};
//    for (int i = 0; i<10; i++) {
//        for(int j=0;j<10;j++){
//        int x = ofMap(i,0,9,-100,100);
//        int y = ofMap(j,0,9,-100,100);
//        balls[i+j*10].setup((float)x,(float)y);
//        }
//    }
    for(int i=0;i<NUM;i++){
        Gravityball* b = new Gravityball();
        b->setup();
        balls.push_back(*b);
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    float amp;
    for (int i = 0; i<balls.size(); i++) {
        glm::vec3 tempvec;
        float len = glm::fastLength(balls[i].vel);
        int sign;
        
        for (int j = 0; j<balls.size(); j++) {
            if(len<1.5){
                sign=-1;
            }else{
                sign=1;
            }
            if (i!=j){
                amp = sign*glm::fastDistance(balls[i].pos,balls[j].pos);

                tempvec += balls[i].grav* amp*amp/10000000 * glm::fastNormalize(balls[j].pos-balls[i].pos);
            }
            amp = glm::fastDistance(balls[i].pos,center);
            tempvec += amp*amp/500000000 * glm::fastNormalize(center-balls[i].pos);
        }
        balls[i].vel += tempvec;
        

        balls[i].update();
        if(len<0.2){
            balls[i].trimspeed(true);
        }else if( len>15){
            balls[i].trimspeed(false);
        }
        if(ofRandom(0,1)<0.0001){
            balls.erase(balls.begin()+i);
        }
    }
    while(balls.size()<NUM){
        Gravityball* newball = new Gravityball();
        ofVec3f vel = 50*ofVec3f(ofRandom(-100,100),ofRandom(-100,100),ofRandom(-100,100)).normalize();
        newball->setup({ofRandom(-100,100),ofRandom(-100,100),ofRandom(-100,100)},vel);
        balls.push_back(*newball);
    }
}
void ofApp::draw(){
    if(drawenable){
//    if(reset){
//        ofSetColor(0, 0, 0);
//        reset = !reset;
//        ofDisableBlendMode();
//        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
//
//    }else{
           if (skip==0){
//        ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
//        ofSetColor(255, 255);
//        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
//        ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
//        ofSetColor(1, 1, 1);
//
//        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
               for(int i=0;i<balls.size();i++){
                   balls[i].crotate += 1;
               }
//
//    }
    }
    skip = (skip+1)%15;
    ofBackgroundGradient(ofColor(20, 20, 20),ofColor(220, 220, 220),OF_GRADIENT_CIRCULAR);

    cam.begin();
    ofSetLineWidth(0.1);
    ofSetColor(255,8);
//    ofDrawAxis(1000);
    ofDrawGridPlane(50,15);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);

    for(int i=0;i<balls.size();i++){
        balls[i].draw();
    }
    cam.end();
    ofSetColor(255);
     string fpsStr = "frame rate: "+ofToString(ofGetFrameRate(), 2);
     ofDrawBitmapString(fpsStr, 10,10);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' '){
    for (int i = 0; i<NUM; i++) {
        glm::mat4 mat;
        glm::vec3 axis;
        mat = glm::rotate(ofDegToRad(ofRandom(-30,30)), glm::vec3(1, 0, 0));
        mat = glm::rotate(ofDegToRad(ofRandom(-30,30)),glm::vec3(0, 1, 0))*mat;
        mat = glm::rotate(ofDegToRad(ofRandom(-30,30)),glm::vec3(0,0 , 1))*mat;

        balls[i].vel = 3 * glm::vec3(mat * glm::vec4(balls[i].vel,1.0f));
        balls[i].speedparam += 0.5;
    }
        
    reset = true;
}
    if(key=='z'){
        drawenable = !drawenable;
        ofSetBackgroundAuto(drawenable);
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
    for(int i=0;i<NUM;i++){
        balls[i].crotate += 13;
    }
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
