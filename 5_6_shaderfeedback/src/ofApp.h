#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"

enum ControlMode { AUTO = 0, MANUAL = 1, OSC = 2 };

enum MessageType { BLUR_AMOUNT, SCALE, UNKNOWN };
MessageType addressToMessage(std::string const &str);

class ofApp : public ofBaseApp {

  public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

  private:
    void resetBlank();
    void resetCircle();
    static void applyBlur1d(ofShader &blurshader, ofFbo &target, float amount);
    void applyBlur(ofFbo &target, float amount);
    void updateParams();
    void drawMainShader();
    void processOscMessage();

    ofShader shader;
    ofShader noise;
    ofShader blurx, blury, centercircle;
    ofFbo fbo1;
    ofxOscReceiver osc;
    ofxOscMessage latest_msg;
	
    float time;
    float myscale;
    float myblur;
    ControlMode mode;
    bool debug_view;
};
