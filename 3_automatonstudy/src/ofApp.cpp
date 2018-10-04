#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//    ofSetFrameRate(20);
    pix[0].allocate(ofGetWidth(),ofGetHeight(),OF_PIXELS_RGBA);
    pix[1].allocate(ofGetWidth(),ofGetHeight(),OF_PIXELS_RGBA);
    pix[2].allocate(ofGetWidth(),ofGetHeight(),OF_PIXELS_RGBA);
    tex.allocate(ofGetWidth(),ofGetHeight(),OF_PIXELS_RGBA);
    ofFloatColor c;
    for(int layer=0;layer<3;layer++){

    for(int i=0;i<pix[0].getWidth();i++){
        for (int j=0;j<pix[0].getHeight();j++){
        c.set(ofNoise(i*0.005,j*0.005,1),ofNoise(i*0.005,j*0.005,1.2),ofNoise(i*0.005,j*0.005,1.4));
        pix[layer].setColor(i,j,c);
            hysterisis[i][j]=false;
    }
    }
    }
}
static ofFloatColor activation(ofFloatColor &c1,ofFloatColor &c2, bool hysterisis){
    //input 0~1
    ofFloatColor nc;
    float th;
    if(hysterisis){
        th=+0.4;
    }else{
        th=-0.4;
    }
    c2.setHueAngle((c2.getHueAngle()+1));
    c1.setHueAngle((c1.getHueAngle()+1));
    nc.r =  c1.r + atan((c1.r*0.5+c2.r*0.7+th)*1.99-1)*0.1;
    nc.g =c1.g + atan((c1.g*0.5+c2.g*0.7+th)*1.999-1)*0.1;
    nc.b =c1.b + atan((c1.b*0.5+c2.b*0.71+th)*1.9-1)*0.1;
    nc.setHueAngle((nc.getHueAngle()+1));
    nc.clamp();
    return nc;
}

void ofApp::updatepix(){
    ofFloatColor c;
    ofFloatColor cc;
    for(int layer=2;layer<3;layer++){
         int w = pix[0].getWidth();
        for(int i=1;i<pix[0].getWidth()-1;i++){
            for (int j=1;j<pix[0].getHeight()-1;j++){
                for(int tc=0;tc<3;tc++){
                c[tc] =
                (pix[layer-1].getColor(i-1,j)[tc]*0.2+
                 pix[layer-1].getColor(i+1,j)[tc]*0.3+
                 pix[layer-1].getColor(i,j+1)[tc]*0.3+
                 pix[layer-1].getColor(i,j-1)[tc]*0.2)
                
//                +(pix[layer-1].getColor(i-1, j+1)[tc]*0.1+
//                 pix[layer-1].getColor(i-1, j-1)[tc]*0.1+
//                 pix[layer-1].getColor(i+1, j-1)[tc]*0.1+
//                 pix[layer-1].getColor(i+1, j+1)[tc]*0.1)
                ;
                }
                cc =pix[layer-1].getColor(i, j);
                c =  activation(cc, c,hysterisis[i][j]);
                
                hysterisis[i][j] = cc.getBrightness()>c.getBrightness();

                pix[layer].setColor(i, j, c);
                
            }
        }
        for(int i=1;i<pix[0].getWidth()-1;i++){
            for (int j=1;j<pix[0].getHeight()-1;j++){
                for(int tc=0;tc<3;tc++){
                c[tc] =
                (pix[layer].getColor(i-1,j)[tc]+
                 pix[layer].getColor(i+1,j)[tc]+
                 pix[layer].getColor(i,j+1)[tc]+
                 pix[layer].getColor(i,j-1)[tc])*0.04;
                
//                (pix[layer].getColor(i-1, j+1)*0.01+
//                  pix[layer].getColor(i-1, j-1)*0.01+
//                  pix[layer].getColor(i+1, j-1)*0.01+
//                  pix[layer].getColor(i+1, j+1)*0.01)+
                c[tc] = pix[layer].getColor(i,j)[tc]+c[tc]-1.5*pix[layer].getColor(i,j)[tc]*c[tc];
                }
                c+=0.012;
                pix[0].setColor(i,j,c);

    }
    }
    }
    pix[2] =pix[0];
    pix[1] = pix[2];
}
//--------------------------------------------------------------
void ofApp::update(){
    updatepix();
    tex.loadData(pix[2]);
}

//--------------------------------------------------------------
void ofApp::draw(){
    tex.draw(0,0);
    ofDrawBitmapString(ofGetFrameRate(),10,10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    ofFloatColor c;
    float t = ofGetElapsedTimef();
    for(int layer=0;layer<3;layer++){
        
        for(int i=0;i<pix[0].getWidth();i++){
            for (int j=0;j<pix[0].getHeight();j++){
                c.set(ofNoise(i*0.007,j*0.007,1+t),ofNoise(i*0.007,j*0.007,1.2+t),ofNoise(i*0.007,j*0.007,1.4+t));
                pix[layer].setColor(i,j,c);
                hysterisis[i][j]=false;
            }
        }
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
    updatepix();
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
