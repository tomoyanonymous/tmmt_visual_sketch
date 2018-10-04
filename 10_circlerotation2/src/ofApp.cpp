
#include "ofApp.h"
//void doublePendulum::setup(double _len,ofVec2f _pos1){
//    len  = _len;
//    pos1 = _pos1;
//    pos2 = pos1+ofVec2f(len, 0).rotate(ofRandom(360));
//    pos3 = pos2+ofVec2f(len, 0).rotate(ofRandom(360));
//    fixedpoint = true;
//}
//void doublePendulum::update(){
//    double delta = angle1-angle2;
//    double sdelta = sin(delta);
//    double cdelta = cos(delta);
//    ofVec2f fixed,end,mid;
//    mid = pos2;
//    if(fixedpoint){
//        fixed=pos1;
//        end = pos3;
//    }else{
//        end = pos1;
//        fixed = pos3;
//    }
//    aangle1 = (-pow(vangle1,2)*cdelta+2*pow(vangle2,2))*sdelta/(cdelta-2)-0.004*vangle1;
//    aangle2 = (-pow(vangle2,2)*cdelta+2*pow(vangle1,2))*sdelta/(cdelta-2)-0.004*vangle2;
////    aangle1 = std::fmax(-1,std::fmin(aangle1,1));
////    aangle2 = std::fmax(-1,std::fmin(aangle2,1));
//
//    vangle1 +=aangle1;
//    vangle2 +=aangle2;
//    
//    angle1 = angle1+vangle1;
//    angle2 =angle2+vangle2;
//    
//    mid = fixed+ ofVec2f(len,0).rotateRad(angle1);
//    end = mid+ofVec2f(len*2,0).rotateRad(angle2);
//    pos2 = mid;
//    if(fixedpoint){
//        pos1= fixed;
//        pos3 = end;
//    }else{
//        pos1=end;
//        pos3 =fixed;
//    }
//}
//void doublePendulum::setVel(){
//    vangle1=0.1;
//    vangle2=0.02;
//}
//void doublePendulum::draw(){
//    ofSetColor(255);
//    ofDrawLine(pos1,pos2);
//    ofDrawLine(pos2, pos3);
//    ofDrawCircle(pos1,10);
//    ofDrawCircle(pos2,10);
//    ofDrawCircle(pos3,10);
//
//}

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
//    pendulum.setup(50,ofVec2f(ofGetWidth()/2.,ofGetHeight()/2.));
//    pendulum.setVel();
    pend.initialize();
    pend.setIntegrate(3);
    ofSetFrameRate(60);
    ofBackground(0);
    img.load("cat4.jpg");
    for (int i=0; i<img.getWidth(); i++) {
        for (int j=0; j<img.getHeight(); j++) {
            ofColor c = img.getColor(i, j);
            c.a = 255-c.getBrightness();
            img.setColor(i,j,c);
        }
    }
}

void ofApp::initdraw(){

    fbo1.begin();
    ofBackground(255);
    ofSetColor(0);
    
    //shader init
//    initshader.begin();
//    shader.setUniform1f ("time",ofGetElapsedTimef());
//    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
//    initshader.end();
    
    //or geometry
//    ofDrawTriangle(0, 0, ofGetWidth(),0,0, ofGetHeight());
    if(cat){
        ofSetColor(255);

        int w = std::fmin(ofGetWidth(),ofGetHeight());
        img.draw(0,0,w,w);
    }else{
        ofSetColor(0);

    int height = 100;
    ofDrawRectangle(0,ofGetHeight()/2.-height/2.,ofGetWidth(),height);
    ofDrawRectangle(ofGetWidth()/2.-height/2,0.,height,ofGetHeight());
    }

    fbo1.end();

}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetColor(255);

//    pendulum.update();
    std::vector<std::pair<double,double>> vertpast =pend.vertices();
    ofVec2f tmp1past = 250*ofVec2f(vertpast[2].first,vertpast[2].second);
    ofVec2f tmp2past = 250*ofVec2f(vertpast[3].first,vertpast[3].second);
    pend.move(0.007);
    std::vector<std::pair<double,double>> vert =pend.vertices();
    ofVec2f tmp1 = 250*ofVec2f(vert[2].first,vert[2].second);
    ofVec2f tmp2 = 250*ofVec2f(vert[3].first,vert[3].second);
    angle=-(tmp2-tmp1).angle(tmp2past-tmp1past)/5.;
    ofVec2f tcenter = tmp1+(tmp2-tmp1)*0.5;
    circlecenter.set(tcenter.x+ofGetWidth()/2.,tcenter.y+ofGetHeight()/2.);
    circleradius = (tmp2-tmp1).length()/2.;
    if(reset){
        initdraw();
        reset=false;
    }else{

        fbo1.begin();
        shader.begin();
        shader.setUniform1f("circleradius",circleradius);
        shader.setUniform2f("circlecenter",circlecenter.x,circlecenter.y);
        shader.setUniform1f ("circledelta",angle);
        shader.setUniform1f ("time",time);

        fbo1.draw(0,0);
        shader.end();
        fbo1.end();
    }
    
    time+=1/60.;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);

//    pendulum.draw();

    fbo1.draw(0,0);
    if(debug){
    ofSetColor(50,50,50,50);

        ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    ofSetColor(219, 109, 19);
    std::vector<std::pair<double,double>> vert =pend.vertices();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    for(int i=0;i<4;i++){
        ofDrawCircle(vert[i].first*250.,vert[i].second*250.,10);
    }
        
        ofVec2f tmp1 = ofVec2f(vert[3].first,vert[3].second)*250.;
        ofVec2f tmp2 = ofVec2f(vert[2].first,vert[2].second)*250.;
        
        ofSetLineWidth(10.);
        ofDrawLine(vert[0].first*250.,vert[0].second*250,vert[1].first*250,vert[1].second*250);
        ofDrawLine(vert[1].first*250.,vert[1].second*250,vert[2].first*250,vert[2].second*250);
        ofDrawLine(vert[2].first*250.,vert[2].second*250,vert[3].first*250,vert[3].second*250);
        ofNoFill();
        ofDrawCircle(tmp2+(tmp1-tmp2)*0.5,0.8*250./2.);
        ofFill();
        ofSetLineWidth(1);

    }
//    ofDrawBitmapString("Framerate:",10,10);
//    ofDrawBitmapString(ofGetFrameRate(),40,10);


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='f'){
        fs=!fs;
        ofSetFullscreen(fs);
        if(fs==false){
        ofSetWindowShape(720, 720);
        }
        fbo1.allocate(ofGetWidth(),ofGetHeight());
        fbo2.allocate(ofGetWidth(),ofGetHeight());
    }
    if(key=='r'){
        pend.initialize();
        reset =true;
        time=0;
    }
    if(key=='d'){
        debug=!debug;
    }
    if(key=='c'){
        cat =!cat;
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
    pend.initialize();
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
