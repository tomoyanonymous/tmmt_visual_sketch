#pragma once

#include "ofMain.h"
#include <vector>
#include "gravityball.hpp"


#define NUM 100

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

        Gravityball balls[NUM];
//    ofPolyLine pl;
    float globalcrotate = 0;
    bool reset =false;
    bool fullscreen;
		        ofVec3f center;
    int skip;
};
