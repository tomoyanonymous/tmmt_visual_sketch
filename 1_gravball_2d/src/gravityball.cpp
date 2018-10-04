//
//  gravityball.cpp
//  mySketch
//
//  Created by 松浦知也 on 2018/09/04.
//

#include "gravityball.hpp"

Gravityball::Gravityball(){
//    setup();
}

Gravityball::~Gravityball(){
    
}

void Gravityball::setup(){

    pos = {ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),0 };
    vel = {ofRandom(-10,10),ofRandom(-10,10),ofRandom(-10,10)};
//    vel ={0,0,0};
    c_offset =ofRandom(0,2.);
    grav = ofRandom(0.7,1.5);
    speedparam = 0.993;
    speed = ofRandom(0.05,0.06);
}
void Gravityball::setup(float x,float y){
    
    pos = {x,y,0 };
    //    vel = {ofRandom(-10,10),ofRandom(-10,10),ofRandom(-10,10)};
    vel ={0,0,0};
    c_offset =ofRandom(0,3);
grav = ofRandom(0.7,1.5);

    speedparam = 0.98;
    speed = ofRandom(0.02,0.05);

}

void Gravityball::update(){
    pos_past = pos;
    vel *= speedparam;
    float t = ofGetElapsedTimef();
    vel+= 0.07*ofVec2f(ofNoise(0,grav*3,t/10.5),ofNoise(100,grav*3,t/10.5))/(vel.length()+1);
    pos += vel;
    
    
}

void Gravityball::trimspeed(bool updown){
    if(updown){
    speedparam= 1+speed;
    }else{
        speedparam = 1-speed;
    }
}
//
//void Gravityball::computeVectormap(std::vector<Gravityball> &ballarray){
//    ofVec2f tempvel;
//    for (int i =0;i<ballarray.size();i++){
//        for (int j =0;j<i-1;j++){
//        tempvel += computedistance(ballarray[i],ballarray[j]);
//        }
//        
//    }
//}

void Gravityball::draw(){
    
    float size = (grav*2.5*vel.length())+0.01;
    ofColor c;
    ofSetLineWidth(size);
    c.set(255*(sin(vel.length()/10+c_offset)/2+0.5), 128*(atan(vel.length()/15+c_offset)/2+0.5), 255*(cos(vel.length()/10+c_offset)/2+0.5));
    c.setHueAngle((c.getHueAngle()+crotate));
    ofSetColor(c,std::fmin(400*grav/(std::fmax(size,1)),230.0));
    ofDrawLine(pos_past.x,pos_past.y,pos_past.z,pos.x,pos.y,pos.z);
}
