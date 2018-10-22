#include "ofApp.h"
#include "data.h"
void ofApp::initDraw(){
    pingpong.src->begin();
    ofBackground(0);
    ofSetColor(255);
    int rectnum = 10;
    float rectsize = 640/(rectnum*2);
    for(int i = 0;i<rectnum*2;i++){ // y
        for(int j = 0;j<rectnum;j++){ // x
            int oddoffset  = (i%2==0)? rectsize:0;
            ofDrawRectangle(j*2*rectsize+oddoffset,i*rectsize,rectsize,rectsize);
        }
    }
    pingpong.src->end();
    velbuffer.begin();
    ofBackground(0);
    velbuffer.end();
    
    databuffer.begin();
    ofSetColor(255);
    ofClear(0);
    databuffer.end();
    
    ofFloatPixels pix;

    databuffer.readToPixels(pix);
    float* data;
    data = new float[24*30*4];
    for (int i = 0; i < 30; i++){
        for (int j = 0; j < 24; j++){
            ofFloatColor c;
            c.r =frames2d[i][j].x;
            c.g =frames2d[i][j].y;
            c.b=0;
            c.a=1;
            pix.setColor(j, i, c);
            for(int rgba=0;rgba<4;rgba++){
                if(rgba<2){//only r and g
                    data[i*24*4+j*4+rgba]=frames2d[i][j][rgba];
                }else{
                data[i*24*4+j*4+rgba]=1.0;
                }
            }
        }
    }
//    databuffer.getTexture().loadData(data,24,30,GL_RGBA32F);
    databuffer.getTexture().loadData(pix);

    delete data;

}
//--------------------------------------------------------------
void ofApp::setup(){


    
    //----------------------------------------------------------------
    // the data is stored in a big flat array, let's copy it into something more managable
    // don't have to touch this :)
    
    for (int i = 0; i < 30; i++){
        for (int j = 0; j < 24; j++){
            float x = data3d[ i * 24 * 3  + j * 3 + 0 ];
            float y = data3d[ i * 24 * 3  + j * 3 + 1 ];
            float z = data3d[ i * 24 * 3  + j * 3 + 2 ];
            frames[i][j].set(x,y,z);
        }
    }
    
    for (int i = 0; i < 30; i++){
        for (int j = 0; j < 24; j++){
            float x = data2d[ i * 24 * 2  + j * 2 + 0 ];
            float y = data2d[ i * 24 * 2  + j * 2 + 1 ];
            frames2d[i][j].set(x,y);
        }
    }
    //----------------------------------------------------------------
    drawbuffer.allocate(640,640,GL_RGBA,1);
    pingpong.allocate(640,640);
    
    velbuffer.allocate(640,640,GL_RGBA32F,1);
    ofFboSettings fbosetting;
    fbosetting.maxFilter = GL_LINEAR;
    fbosetting.minFilter = GL_LINEAR;
    fbosetting.internalformat = GL_RGBA32F;
    fbosetting.wrapModeHorizontal = GL_CLAMP_TO_EDGE;
    fbosetting.wrapModeVertical = GL_CLAMP_TO_EDGE;
    fbosetting.width=24;
    fbosetting.height=30;
    databuffer.allocate(fbosetting);


    blurshaderx.load("shaderBlurX");
    blurshadery.load("shaderBlurY");
    myshader.load("myshader");
    datashader.load("datashader");
    
    initDraw();
    

}

//--------------------------------------------------------------
void ofApp::update(){
    time+=0.4;
    if(time>30){
        time=0;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);

    
    // you don't have to touch this either:)
    //----------------------------- copy data into array
    ofPoint data3d[24];
    ofPoint data2d[24];
    ofPoint data2d_past[24];
    ofSetColor(255);

    int frameNumber =(int)(time);
    for (int i = 0; i < 24; i++){
        data3d[i] = frames[ frameNumber][i];
        data2d[i] = frames2d[(frameNumber+1)%30][i];
        data2d_past[i] = frames2d[frameNumber][i];
    }
    // end do not touch
    float scale = mouseX/500.;

    velbuffer.begin();
   
//    float intensityx,intensityy;
//
//    for (int i = 0; i < 24; i++){
//        intensityx =(data2d[i]-data2d_past[i]).x*scale;
//        intensityy =(data2d[i]-data2d_past[i]).y*scale;
//        ofFloatColor c = ofFloatColor(intensityx,intensityy,0,0.2);
//        ofDrawCircle(data2d[i],20);
//    }
    blurshaderx.begin();

    blurshaderx.setUniform1f("blurAmnt", mouseY/220.);
    velbuffer.draw(0,0);
    blurshaderx.end();
    blurshadery.begin();
    blurshadery.setUniform1f("blurAmnt",mouseY/220.);
    velbuffer.draw(0,0);
  
    blurshadery.end();
    
    datashader.begin();
    datashader.setUniformTexture("data", databuffer.getTexture(), 1);
    datashader.setUniform1f("time",time);
    datashader.setUniform1f("scale",mouseX/640.);
    velbuffer.draw(0,0);
    //    ofDrawRectangle(0,0,640,640);
    datashader.end();
    
    velbuffer.end();
    
    pingpong.dst->begin();
    drawbuffer.activateAllDrawBuffers();
    myshader.begin();
    myshader.setUniformTexture("velocity", velbuffer.getTexture(), 1);
    pingpong.src->draw(0,0);
//    ofDrawRectangle(0,0,640,640);
    myshader.end();
    pingpong.dst->end();
    float time = ofGetElapsedTimef();


    if(drawdebug){
        velbuffer.draw(0,0);
    }else{
        pingpong.dst->draw(0,0);
//        databuffer.draw(0,0);
    }
    if(drawgeometry){
            for (int i = 0; i < 24; i++){
                int i2 = (i+i)%24;
                ofDrawLine(data2d[i],data2d_past[i]);
                ofDrawCircle(data2d[i],10);
            }
    }
    pingpong.swap();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case ' ':
            initDraw();
            break;
        case 'd':
            drawgeometry=!drawgeometry;
            break;
        case 'g':
            drawdebug=!drawdebug;
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
    drawdebug =!drawdebug;
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
