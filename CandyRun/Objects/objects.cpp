//
//  objects.cpp
//  CandyRun
//
//  Created by Gennaro Mellone on 09/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#include "objects.hpp"

Object::Object(){}
Object::~Object(){}

float Object::getX(){
    return this->pos_X;
}

float Object::getY(){
    return this->pos_Y;
}

float Object::getZ(){
    return this->pos_Z;
}

unsigned int Object::getTexture(){
    return this->texture;
}

void Object::setPosition(float X, float Y, float Z){
    this->pos_X = X;
    this->pos_Y = Y;
    this->pos_Z = Z;
}

void Object::setDimension(float f){

    this-> start_X = -f;
    this-> start_Y = -f;
    this-> start_Z = -f;
    
    this-> end_X = f;
    this-> end_Y = f;
    this-> end_Z = f;
}

void Object::setColor(GLfloat r, GLfloat g, GLfloat b){
    this->r = r;
    this->g = g;
    this->b = b;
}

void Object::draw(){
    glColor3f(this->r, this->g, this->b);
    
    glPushMatrix();
        glTranslatef(this->pos_X, this->pos_Y, this->pos_Z);
        glutSolidCube(this->end_X);
    glPopMatrix();

}

bool Object::getEnemy(){
    return this->isEnemy;
}

void Object::setEnemy(bool obj){
    this->isEnemy = obj;
}

std::vector< std::vector<Object> > objects(4);
Object o;

void Object::initObject(){
    objects.clear();
    
    float beginning = -60.0;
    for (int i=0; i<4; i++) {
        std::vector<Object> v1;
        for(int j=0; j<3; j++){
            int n = rand()%10-5;
            bool e;
            if (rand() % 2 == 0)
                e = true;
            else
                e = false;
            o.setEnemy(e);
            if(!e)
                o.setColor(0.0, 1.0, 0.0);
            else
                o.setColor(1.0, 0.0, 0.0);
            o.setPosition(n, 0.5f, beginning);
            v1.push_back(o);
        }
        objects.push_back(v1);
        beginning += 20;
    }
}

void Object::drawObject(){
    for (int i=0; i<objects.size(); i++) {
        for(int j=0; j<objects[i].size(); j++){
            int n = rand()%10-5;
            if(objects[i][j].getZ() > 30.0)
                objects[i][j].setPosition(n, 1, -60);
           
            glPushMatrix();
            objects[i][j].setPosition(objects[i][j].getX(), objects[i][j].getY(), objects[i][j].getZ() + 0.1);
                objects[i][j].draw();
            glPopMatrix();
        }
    }
}

int Object::handleCollision(float x, float y, float z){
    for (int i=0; i<objects.size(); i++) {
        for(int j=0; j<objects[i].size(); j++){
            if((objects[i][j].pos_Z <= 15.0f && objects[i][j].pos_Z >= 14.9f) && (objects[i][j].pos_X <= x + 0.5 && objects[i][j].pos_X >= x - 0.5)){
                if(objects[i][j].isEnemy)
                    return OSTACOLO;
                else
                    return PREMIO;
            }
        }
    }
    
    return VUOTO;
}
