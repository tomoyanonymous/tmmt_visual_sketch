#pragma once

#include "ofMain.h"

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
    float circleradius;
    ofVec2f circlecenter;
    float goldenratio = (1+sqrt(5))/2.;
    bool circledirection=true;
    bool reset=true;
    bool fs =false;
};
