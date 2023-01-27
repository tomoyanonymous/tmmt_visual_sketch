#pragma once

#include "BaseTheme.h"
#include "ofMain.h"
#include "ofParameter.h"
#include "ofxGui.h"
#include "ofxImGui.h"
#include "ofxImGuiLoggerChannel.h"

#include "ofxOsc.h"
#include <memory>
#include <sstream>

enum ControlMode { AUTO = 0, MANUAL = 1, OSC = 2, GUI = 3 };

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
    void resetOscReceiver(int port);
    void initGui();
    static void applyBlur1d(ofShader &blurshader, ofFbo &target, float amount);
    void applyBlur(ofFbo &target, float amount);
    void updateParams();
    void drawMainShader();
    void drawUi();
    void processOscMessage();
    void setFullScreen(bool flag);


    ofShader shader;
    ofShader noise;
    ofShader blurx, blury, centercircle;
    ofFbo fbo1;
    ofxOscReceiver osc;
    ofxOscMessage latest_msg;
    std::stringstream osc_log;

    ofParameterGroup params;
    std::unique_ptr<ofxPanel> gui;
    ofxImGui::Gui imgui;
    ofxImGui::LoggerChannel log;
    float time;
    ofParameter<float> myscale;
    ofParameter<float> myblur;
    ofParameter<int> mode;
    ofParameter<int> port;
    bool debug_view;
    ofParameter<bool> fullscreen;
};
