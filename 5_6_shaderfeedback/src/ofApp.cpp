#include "ofApp.h"

#include "BaseTheme.h"
#include "DefaultTheme.h"
#include "ImHelpers.h"
#include "imgui.h"
#include "ofAppRunner.h"
#include "ofColor.h"
#include "ofGraphics.h"
#include "ofLog.h"
#include "ofParameter.h"
#include "ofVec2f.h"
#include <memory>

MessageType addressToMessage(std::string const &str) {
    if (str == "/blur")
        return MessageType::BLUR_AMOUNT;
    if (str == "/scale")
        return MessageType::SCALE;
    return MessageType::UNKNOWN;
}

void ofApp::initGui() {
    this->params.clear();
    this->params.setName("parameters");

    this->myblur.set("Blur", 5.0, 0.0, 5.0);
    this->myscale.set("Noise Intensity", 5.0, 0.0, 5.0);

    this->mode.set("Control Mode", ControlMode::MANUAL);
    this->port.set("OSC Port", 8000, 0, 99999);
    this->params.add(this->myblur, this->myscale);

    this->debug_view = false;
    this->fullscreen = false;
    imgui.setup();
}
void ofApp::resetOscReceiver(int port) {
    if (osc.isListening()) {
        osc.stop();
    }
    this->osc.setup(port);
    this->osc.start();
    log.log(OF_LOG_NOTICE, "app", "reset osc");
}
//--------------------------------------------------------------
void ofApp::setup() {
    ofSetLogLevel(OF_LOG_NOTICE);
    ofSetEscapeQuitsApp(false);
    this->latest_msg.clear();
    initGui();
    this->resetOscReceiver(this->port);

    shader.load("myshader");
    centercircle.load("centercircle");
    noise.load("shaderPnoise");
    blurx.load("shaderBlurX");
    blury.load("shaderBlurY");

    fbo1.allocate(ofGetWidth(), ofGetHeight());
    fbo1.begin();
    ofClear(0);
    noise.begin();
    ofSetColor(255, 255);
    noise.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    noise.setUniform1f("scale", 5.);
    noise.setUniform1f("rgbcorel", 0.1);
    noise.setUniform1f("time", ofGetElapsedTimef());
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

    noise.end();
    fbo1.end();
}

//--------------------------------------------------------------
void ofApp::applyBlur1d(ofShader &blurshader, ofFbo &target, float amount) {
    blurshader.begin();
    blurshader.setUniform1f("blurAmnt", amount);
    target.draw(0, 0);
    blurshader.end();
}

void ofApp::applyBlur(ofFbo &target, float amount) {
    ofApp::applyBlur1d(this->blurx, target, amount);
    ofApp::applyBlur1d(this->blury, target, amount);
}

void ofApp::processOscMessage() {

    while (this->osc.getNextMessage(this->latest_msg)) {
        // osc_log << this->latest_msg;
        // log.log(OF_LOG_NOTICE, "osc", osc_log.str());
        // osc_log.clear();
        std::string address = this->latest_msg.getAddress();
        MessageType v_type = addressToMessage(address);
        switch (v_type) {
        case BLUR_AMOUNT: {
            auto blur = this->latest_msg.getArgAsFloat(0);
            this->myblur = blur;
        } break;
        case SCALE: {
            auto scale = this->latest_msg.getArgAsFloat(0);
            this->myscale = scale;
        } break;

        case UNKNOWN:
            break;
        }
    }
}

void ofApp::drawMainShader() {
    shader.begin();
    shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    shader.setUniform1f("scale", myscale);
    shader.setUniform1f("time", time);
    fbo1.draw(0, 0);
    shader.end();
}
void ofApp::updateParams() {
    float range = 4.0;
    float exp = 2.0;
    auto getpos = [=](float speed) {
        return pow((cos(time * speed) + 1.0) * 0.5, exp);
    };
    processOscMessage();
    switch (this->mode) {
    case AUTO:
        myblur.disableEvents();
        myscale.disableEvents();
        // AM
        //  0~4
        myblur = getpos(1.2) * getpos(0.2) * range;
        myscale = getpos(1.0) * getpos(0.3) * range;

        break;
    case MANUAL:
        myblur.disableEvents();
        myscale.disableEvents();
        myblur = 5.0 * (float)mouseY / ofGetHeight();
        myscale = 5.0 * (float)mouseX / ofGetWidth();

        break;
    case OSC:

    case GUI:
        myblur.enableEvents();
        myscale.enableEvents();
        break;
    }
}
void ofApp::update() {

    this->updateParams();

    fbo1.begin();
    this->applyBlur(fbo1, myblur);
    this->drawMainShader();
    fbo1.end();

    this->time += 1 / 60.;
}
void ofApp::drawUi() {
    auto mainsettings = ofxImGui::Settings();
    this->imgui.begin();
    ofxImGui::BeginWindow("Debug View(D to toggle)", mainsettings);
    int port_tmp = this->port;
    if (ImGui::InputInt("OSC Port", &port_tmp)) {
        resetOscReceiver(port_tmp);
        this->port = port_tmp;
    };
    std::vector<std::string> labels = {"auto", "mouse", "osc", "gui"};
    int mode_tmp = mode;
    ofxImGui::VectorListBox("Control Mode", &mode_tmp, labels);

    mode = mode_tmp;
    bool fullscreen_tmp = this->fullscreen;
    if (ImGui::Checkbox("Full Screen(F)", &fullscreen_tmp)) {
        this->fullscreen = fullscreen_tmp;
        setFullScreen(fullscreen_tmp);
    }
    if (ImGui::SmallButton("Reset To Blank(Space)")) {
        this->resetBlank();
    }

    if (ImGui::SmallButton("Reset To Circle(R)")) {
        this->resetCircle();
    }
    ImGui::BeginGroup();
    ofxImGui::AddParameter(myscale);
    ofxImGui::AddParameter(myblur);

    ImGui::EndGroup();
    ofxImGui::EndWindow(mainsettings);

    //logs are super heavy,disabled 

    // auto logwindow_settings = ofxImGui::Settings();
    // logwindow_settings.windowSize = ofVec2f(400, 200);
    // logwindow_settings.windowPos =
    //     mainsettings.windowPos + ImVec2(0.0, mainsettings.windowSize.y);
    // ofxImGui::BeginWindow("OSC Log", logwindow_settings);

    // ImGui::TextWrapped(log.getBuffer().c_str());
    // ImGui::LogButtons();
    // ofxImGui::EndWindow(logwindow_settings);

    this->imgui.end();
}
//--------------------------------------------------------------
void ofApp::draw() {
    this->fbo1.draw(0, 0);
    if (this->debug_view) {
        ofSetColor(ofColor::red);
        ofDrawCircle(ofVec2f(this->myscale / 5.0 * ofGetWidth(),
                             this->myblur / 5.0 * ofGetHeight()),
                     4.0);
        ofSetColor(ofColor::white);

        drawUi();
    }
}
void ofApp::setFullScreen(bool flag) {
    ofSetFullscreen(flag);
    fbo1.allocate(ofGetWidth(), ofGetHeight());
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    switch (key) {
    case ' ':
        this->resetBlank();
        break;
    case 'r':
        this->resetCircle();
        break;
    case 'f':
        fullscreen = !fullscreen;
        this->setFullScreen(this->fullscreen);
        break;
    case 'd':
        this->debug_view = !this->debug_view;
        break;
    case 'm':
        this->mode = ControlMode(((int)this->mode + 1) % 3);
    }
}

void ofApp::resetBlank() {
    fbo1.begin();
    ofClear(0);
    noise.begin();
    ofSetColor(255, 255);
    noise.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
    noise.setUniform1f("scale", 5.);
    noise.setUniform1f("rgbcorel", 0.01);
    noise.setUniform1f("time", ofGetElapsedTimef());
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

    noise.end();
    fbo1.end();
}
void ofApp::resetCircle() {
    // time = (int)ofRandom(10000) * TWO_PI;
    time = 0;
    // cout << time <<endl;
    fbo1.begin();
    centercircle.begin();
    centercircle.setUniform2f("resolution", ofGetWidth(), ofGetHeight());

    ofClear(0);
    ofSetColor(255, 255);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    centercircle.end();
    fbo1.end();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
