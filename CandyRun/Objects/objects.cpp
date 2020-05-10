//
//  objects.cpp
//  CandyRun
//
//  Created by Gennaro Mellone on 09/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#include "objects.hpp"


Road::Road(){}
Road::~Road(){}

void Road::init(char *t){

    texture = SOIL_load_OGL_texture(t, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}

void Road::draw()
{
    glColor4f(0.8, 0.8, 0.8, 0.1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);
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

void Road::setPosition(float X, float Y, float Z){
    this->pos_X = X;
    this->pos_Y = Y;
    this->pos_Z = Z;
}

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
float groundSegments[10];
int sceneMotion = 0;

void initializeGround(){
    float beginning = 240.0;
    for (int i = 0; i < 10; i++){
        groundSegments[i] = beginning;
        beginning -= 30.0;
    }
}

void drawRoad(Road road)
{
    for (int i = 0; i < 10; i++){
        glPushMatrix();
        glTranslatef( 0, 0,groundSegments[i]);
        road.draw();
        
        glPopMatrix();
    }
    
}

void sceneAnim(int value){
    sceneMotion += 1;
    
    for (int i = 0; i < 10; i++){
        if (sceneMotion + groundSegments[i] >= 270){
            
            groundSegments[i] -= 300;
            std::cout<<groundSegments[i]<<std::endl;
        }

    }
    glutPostRedisplay();
    glutTimerFunc(34, sceneAnim, 0);
}
// CAMERA



