#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    for(int i=0;i<2;i++){
    fbo[i].allocate(512,512,GL_RGBA32F_ARB);
}
        for(int i=0;i<7;i++){
            std::string filename = "cat"+std::to_string(i)+".jpg";
            catimg[i].load(filename);
        }
    sortshader.load("myshader");
    tex = catimg[imgindex].getTexture();
    fbo[1].begin();
    tex.draw(0,0);
    fbo[1].end();
}
void ofApp::updatesorting(int posx){
    fbo[0].begin();
    sortshader.begin();
    sortshader.setUniform2f("resolution", 512, 512);
    sortshader.setUniform2f("pickpoint", posx,0);
    sortshader.setUniformTexture("cat",catimg[0].getTexture(),1);
    sortshader.setUniform2f("mouse",mouseX,mouseY);
    sortshader.setUniform1f("offset",offset);
    sortshader.setUniform1f("direction",(direction)?0:1);

    fbo[1].draw(0,0);
    sortshader.end();
    fbo[0].end();
    fbo[1].begin();
    fbo[0].draw(0,0);
    fbo[1].end();
}
//--------------------------------------------------------------
void ofApp::update(){
    for(int t=0;t<5;t++){
    for(int i=0;i<1;i++){
        updatesorting(pickpoint.x);
    }
    pickpoint.x++;
    }
// TIME SEQUENCE
//    time+=1/60.;
//    time2+=1/60.;
//    if(time>waitingtime){
//        direction = !direction;
//    }
//    if(time>waitingtime*2){
//        time=0;
//        time2=0;
//        offset*=2.;
//        waitingtime*=1.5;
//        direction = !direction;
//    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo[1].draw(0,0,720,720);
//    ofSetColor(255,0,0);
//    ofDrawCircle(pickpoint*720./512.,1);
    ofSetColor(255);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case ' ':
            fbo[1].begin();
            tex.draw(0,0);
            fbo[1].end();
//            offset = 11.;
            waitingtime=1.5;
            break;
        case 'z':
            direction=!direction;
            break;
        case OF_KEY_DOWN:
            offset*=2;
            break;
        case OF_KEY_UP:
            offset/=2;
            break;
        case OF_KEY_LEFT:
            imgindex = (imgindex>6)?0:imgindex+1;
            fbo[1].begin();
            tex = catimg[imgindex].getTexture();
            tex.draw(0,0);
            fbo[1].end();
//            offset = 11.;
            waitingtime=1.5;
            break;
        case OF_KEY_RIGHT:
            imgindex = (imgindex<1)?6:imgindex-1;
            fbo[1].begin();
            tex = catimg[imgindex].getTexture();
            tex.draw(0,0);
            fbo[1].end();
//            offset = 11.;
            waitingtime=1.5;
            break;
        default:
            break;
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
