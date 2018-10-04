//
//  gravityball.hpp
//  mySketch
//
//  Created by 松浦知也 on 2018/09/04.
//

#pragma once

#include <vector>

#include "ofMain.h"

class Gravityball{
public:
    Gravityball();
    ~Gravityball();
    
    float size;
    float grav;
    glm::vec3 pos;
//    ofVec3f pos_past;

    glm::vec3 vel;
    float c_offset;
//    void computeVectormap(std::vector<Gravityball> &ballarray);
    float crotate=0;
    void setup();
    void setup(glm::vec3 initpos,glm::vec3 initvel);
    void update();
    void draw();
    float speedparam;
    float speed=0.02;
    void speedup();
    void slowdown();
    void trimspeed(bool updown);
    float stripwidth=2.5;
    ofPolyline line;
    ofMesh mesh;
    vector<glm::vec3> vertices;
    glm::vec3 starttoend;
//    static float Gravityball::computedistance(Gravityball &ball1,Gravityball &ball2){
//        return ball1.pos.distance(ball2.pos);
//    }
};
