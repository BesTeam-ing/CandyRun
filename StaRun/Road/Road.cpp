//
//  Road.cpp
//  StaRun
//
//  Created by Ciro De Vita and Gennaro Mellone on 13/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#include "Road.hpp"

Road r;
std::vector<Road> roads; //vector of road objects

GLfloat lp3[] = { 0.0f, 5.0f, -8.0f, 0.0f }; //light position

//constructor/destructor
Road::Road(){}
Road::~Road(){}

//get and set
float Road::getX(){
    return this->pos_X;
}

float Road::getY(){
    return this->pos_Y;
}

float Road::getZ(){
    return this->pos_Z;
}

unsigned int Road::getTexture(){
    return this->texture;
}

void Road::setPosition(float X, float Y, float Z){
    this->pos_X = X;
    this->pos_Y = Y;
    this->pos_Z = Z;
}

//road initialization
void Road::load(){
    r.init("textures/road_grey.jpg");
}

//load road texture
void Road::init(const char *t){
    texture = SOIL_load_OGL_texture(t, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}

//algorithm to create road segments
void Road::initializeGround(){
    roads.clear();
    
    float beginning = -80.0; //start position
    for(int i=0; i<4; i++){
        r.setPosition(0.0f, 0.0f, beginning);
        roads.push_back(r);
        beginning += 30; //start position update
    }
}

//functions to draw road
void Road::draw(){
    glColor4f(0.8, 0.8, 0.8, 0.1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->texture);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexEnvf(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_REPLACE );

    glPushMatrix();
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);
        glVertex3f(pos_X + start_X, pos_Y + start_Y, start_Z + pos_Z);
        glTexCoord2f(0.0f,1);
        glVertex3f(pos_X + start_X, pos_Y + start_Y, end_Z + pos_Z);
        glTexCoord2f(1.0f,1);
        glVertex3f(pos_X + end_X, pos_Y + end_Y, end_Z + pos_Z);
        glTexCoord2f(1.0f,0.0f);
        glVertex3f(pos_X + end_X, pos_Y + end_Y, start_Z + pos_Z);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void Road::drawRoad(float speed){
    for (int i=0; i < roads.size(); i++){
        if(roads[i].getZ() >= 40.0f)
            roads[i].setPosition(0.0f, 0.0f, -80.f + speed); //position control
        
        glPushMatrix();
            roads[i].setPosition(0.0f, 0.0f, roundf((roads[i].getZ() + speed)*100)/100);
            roads[i].draw();
        glPopMatrix();
    }
}
