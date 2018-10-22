#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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
    void updatesorting(int xpos);
        ofFbo fbo[2];
        ofShader sortshader;
        ofImage catimg[7];
    ofTexture tex;
    ofVec2f pickpoint={0,0};
    float offset = 11.;
    float time = 0;
    bool direction=0;
    float time2=0;
    float waitingtime = 1.6;
    int imgindex=4;
};
