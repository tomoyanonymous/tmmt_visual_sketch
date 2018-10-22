#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    pingpong.allocate(512,512);
    imgidx=4;

    shader.load("myshader");
    for(int i=0;i<7;i++){
        img[i].load("cat"+std::to_string(i)+".jpg");
    }
    tex = img[imgidx].getTexture();

    pingpong.clear();
    pingpong.src->begin();
    tex.draw(0,0);
    pingpong.src->end();

}

//--------------------------------------------------------------
void ofApp::update(){
    pingpong.dst->begin();
    shader.begin();
    shader.setUniform2f("resolution", w, h);
    shader.setUniform1f("time", time);
    pingpong.src->draw(0,0);
    shader.end();
    pingpong.dst->end();
    pingpong.swap();
    time+=1/60.;
}

//--------------------------------------------------------------
void ofApp::draw(){
    pingpong.dst->draw(0,0,720,720);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case OF_KEY_RIGHT:
            imgidx++;
            if(imgidx>=7){
                imgidx=0;
            }
            break;
        case OF_KEY_LEFT:
            imgidx--;
            if(imgidx<0){
                imgidx=6;
            }
            break;
    }
    tex = img[imgidx].getTexture();
    pingpong.clear();
    pingpong.src->begin();
    tex.draw(0,0);
    pingpong.src->end();

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
