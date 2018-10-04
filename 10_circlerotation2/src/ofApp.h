#pragma once

#include "ofMain.h"
#include "pendulums.h"

//class doublePendulum{
//    public:
//        void setup(double _len, ofVec2f _pos1);
//        void setVel();
//        void update();
//        void draw();
//        double len;
//    double angle1,angle2,vangle1,vangle2,aangle1,aangle2;
//        ofVec2f pos1,pos2,pos3, vel1,vel2,vel3,acc1,acc2,acc3;
//        bool fixedpoint;
//    
//    
//};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    void initdraw();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    ofFbo fbo1;
    ofFbo fbo2;
    ofShader shader;
    ofShader initshader;
    float acc;
    float vel;
    float angle;
    float delta;
    const float targetangle=270;
    float time=0;
    float circleradius;
    ofVec2f circlecenter;
    float goldenratio = (1+sqrt(5))/2.;
    bool circledirection=true;
    bool reset=true;
    bool fs =false;
    bool debug = false;
//    doublePendulum pendulum;
    pendulums::pendClass pend;
    ofImage img;
    bool cat;
};
