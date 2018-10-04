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
#define STRIPNUM 250
void Gravityball::setup(){

    Gravityball::setup({ofRandom(-10,10),ofRandom(-10,10),ofRandom(-10,10)},{ofRandom(-10,10),ofRandom(-10,10),ofRandom(-10,10)});
    
}
void Gravityball::setup(glm::vec3 initpos,glm::vec3 initvel){
    
    pos =  initpos;
    vel = initvel;
    //    vel ={0,0,0};
    c_offset =ofRandom(0,50);
    grav = ofRandom(0.9,1.);
    speedparam = 0.98;
    speed = ofRandom(0.02,0.05);
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    //    mesh.setupIndicesAuto();
    for(int i=0;i < STRIPNUM;i++){
        ofColor c;
        vertices.push_back(pos);
        mesh.addColor(c);
    }
    mesh.addVertices(vertices);
    for(int i=0;i < STRIPNUM;i++){
        mesh.addIndex(i);
    }
    
}

void Gravityball::update(){
//    pos_past = pos;
    vel *= speedparam;
    pos += vel;
    vertices.push_back(glm::vec3(pos.x,pos.y,pos.z));
    
    if(vertices.size()>STRIPNUM){
    vertices.erase(vertices.begin());
    }
    starttoend= vertices[0]-vertices.back();

    for(int i=0;i<vertices.size();i++){
        float fi = (float)i;
        ofColor c;
        if(i>0 && i<vertices.size()-1){
            float v =glm::fastDistance(vertices[i],vertices[i+1]);
            ofVec3f rot =vertices[i];
            int d = (i%2==0)? 1 : -1;
//            glm::Rotate(vertices[i],)
            
            rot = rot.rotate(stripwidth*v*0.1*d,starttoend);
        c.set(255*(glm::fastSin(v/6.1+fi*0.02)/2+0.5), 255*(glm::fastSin(v/5.9+fi*0.022)/2+0.5), 255*(glm::fastSin(v/6+fi*0.023)/2+0.5));
            c.setHueAngle(fmod(c.getHueAngle()+crotate+c_offset,360));
//            c.a = 400*grav/((fi+1)*0.01);
            c.a = 740*fi/(v *(vertices.size()-1));
            c.clamp();
            mesh.setColor(i,c);
            mesh.setVertex(i, rot);
        }
    }
    mesh.setVertex(0, vertices[0]);
    mesh.setVertex(vertices.size()-1, vertices.back());
    mesh.setColor(0,mesh.getColor(1));
    mesh.setColor(vertices.size()-1,mesh.getColor(vertices.size()-2));

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
    
//    float size = grav*4* vel.length()+1;

//    for(int i=0;i<line.size()-1;i++){
//        ofColor c;
//        float v =glm::fastDistance(line[i],line[i+1]);
//        c.set(255*(glm::fastSin(v/10+(float)i*0.02)/2+0.5), 128*(glm::fastCos(v/11+(float)i*0.022)/2+0.5), 255*(glm::fastSin(v/12+(float)i*0.023+PI/4)/2+0.5));
//        ofSetLineWidth(glm::fastPow(v,2)*(((float)i+0.0001)/300));
//        c.setHueAngle(fmod(c.getHueAngle()+crotate+c_offset,360));
//
//        ofSetColor(c,700*grav/v);
//
//            ofDrawLine(line[i],line[i+1]);
//    }
    
//    mesh.drawFaces();
    mesh.draw();
//    mesh.drawVertices();
//    mesh.drawWireframe();
//    ofDrawLine(pos_past.x,pos_past.y,pos_past.z,pos.x,pos.y,pos.z);
}
