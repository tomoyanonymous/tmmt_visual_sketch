#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    acc = 0;
    vel =0;
    angle=targetangle;
    circlecenter.set(ofGetWidth()/2.,ofGetHeight()/2.);
    circleradius = std::fmin(ofGetWidth(),ofGetHeight())/2.;
    shader.load("myshader");
    initshader.load("initshader");
    fbo1.allocate(ofGetWidth(),ofGetHeight());
    fbo2.allocate(ofGetWidth(),ofGetHeight());

    ofBackground(0);
}

void ofApp::initdraw(){

    fbo2.begin();
    ofBackground(0);
    ofSetColor(255);
    
    //shader init
//    initshader.begin();
//    shader.setUniform1f ("time",ofGetElapsedTimef());
//    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
//    initshader.end();
    
    //or geometry
    ofDrawTriangle(0, 0, ofGetWidth(),0,0, ofGetHeight());

    fbo2.end();

}

//--------------------------------------------------------------
void ofApp::update(){
    float scale =ofMap(circleradius,10,377,3,1);
    acc = (-0.97*vel-0.72*angle)*scale;
    vel += 0.3*acc;
    angle+=vel;
//    angle = fmod(angle,360);
    
    if(abs(vel)<0.0005){
        
        angle=targetangle;
        if(circledirection){
            circlecenter.x = circlecenter.x+circleradius - circleradius/goldenratio;
        }else{
            circlecenter.x = circlecenter.x-circleradius + circleradius/goldenratio;
        }
        circleradius /= goldenratio;
        circledirection = !circledirection;
        if(circleradius<2.0){
            circleradius = std::fmin(ofGetWidth(),ofGetHeight())/2.;
            circlecenter.set(ofGetWidth()/2.,ofGetHeight()/2.);
//            circledirection = !circledirection;

        }
        fbo2.begin();
        fbo1.draw(0,0);
        fbo2.end();
        
    };
    if(reset){
        acc = 0;
        vel =0;
        angle=targetangle;
        circlecenter.set(ofGetWidth()/2.,ofGetHeight()/2.);
        circleradius = std::fmin(ofGetWidth(),ofGetHeight())/2.;
        initdraw();
        reset=false;
    }else{
        fbo1.begin();
        shader.begin();
        shader.setUniform1f("circleradius",circleradius);
        shader.setUniform2f("circlecenter",circlecenter.x,circlecenter.y);
        shader.setUniform1f ("circledelta",angle+targetangle);
        fbo2.draw(0,0);
        shader.end();
        fbo1.end();
    }
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo1.draw(0,0);
    ofVec2f cir;
    cir.set(1,0);
    cir.normalize().scale(circleradius);
    cir.rotate(angle);
    cir+=circlecenter;
    
//    ofDrawCircle(cir, 10);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='f'){
        fs=!fs;
        ofSetFullscreen(fs);
        fbo1.allocate(ofGetWidth(),ofGetHeight());
        fbo2.allocate(ofGetWidth(),ofGetHeight());
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
    reset =true;
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
