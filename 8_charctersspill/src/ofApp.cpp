#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    font.load("futura.ttc",72);
    font.setSpaceSize(1.2);
    spillshader.load("myshader");
    wid=ofGetWidth();
    het=ofGetHeight();
    fbo1.allocate(ofGetWidth(),ofGetHeight());
    time=ofRandom(0,10000);
    ofBackground(255);
    fbo1.begin();
    ofSetColor(0);
    ofDrawRectangle(0,0,wid,het);
    fbo1.end();


}

//--------------------------------------------------------------
void ofApp::update(){
    fbo1.begin();

    if(reset){
        ofBackground(240);
        initdraw();
    }
    if(resetoverwrite||resetcount>905){
        initdraw();
        resetcount=0;
    }
    scale = pow( abs(sin(time*0.8)),3)*2+0.5;
        spillshader.begin();
        spillshader.setUniform2f("resolution",wid,het);
//        spillshader.setUniform1f("scale",ofMap(mouseX,0,ofGetWidth(),0,5));
    spillshader.setUniform1f("scale",scale);

        spillshader.setUniform1f("time",time);
        ofSetColor(255);
        fbo1.draw(0,0);
        spillshader.end();
        fbo1.end();
    time+=1/60.;
    resetcount++;
}
void ofApp::initdraw(){
    int y = 135;
    int yoff=0;
    int x = 80;
    ofSetColor(0);
    if(fullscreen){
        
        font.drawString("THE QUICK BROWN FOX",0,y);
        font.drawString("JUMPS OVER THE LAZY DOG",0,y*2);

    }else{
    
    font.drawString("THE QUICK",x,y*1);
    font.drawString("BROWN FOX",x,y*2);
    
    font.drawString("JUMPS OVER",x,y*3);
    font.drawString("THE LAZY",x,y*4);
    font.drawString("DOG",x,y*5);
    }
    reset = false;
    resetoverwrite=false;
    ofSetBackgroundAuto(true);

}

//--------------------------------------------------------------
void ofApp::draw(){

    fbo1.draw(0,0);


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key==' '){
    resetoverwrite=true;
    }
    if(key=='f'){
        fullscreen=!fullscreen;
        ofSetFullscreen(fullscreen);
        wid=ofGetWidth();
        het=ofGetHeight();
        fbo1.allocate(ofGetWidth(),ofGetHeight());
        reset =true;
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
    reset = true;
    time=ofRandom(0,10000);
    ofSetBackgroundAuto(false);

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
