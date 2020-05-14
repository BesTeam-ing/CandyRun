//
//  objects.cpp
//  CandyRun
//
//  Created by Gennaro Mellone on 09/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#include "objects.hpp"

Object o;
std::vector<Object> objects;

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

bool Object::getObject(){
    return this->isEnemy;
}

void Object::setPosition(float X, float Y, float Z){
    this->pos_X = X;
    this->pos_Y = Y;
    this->pos_Z = Z;
}

void Object::setObject(bool obj){
    this->isEnemy = obj;
}

void Object::draw(){
    glColor3f(0.0f, 0.0f, 1.0f);
    
    glPushMatrix();
        glTranslatef(this->pos_X, this->pos_Y, this->pos_Z);
        glutSolidCube(1);
    glPopMatrix();

}

void Object::initObject(){
    float beginning = -60.0;
    for(int i=0; i<4; i++){
        int n = rand()%10-5;
        o.setPosition(n, 1.0f, beginning);
        objects.push_back(o);
        
        beginning += 20;
    }
}

void Object::drawObject(){
    int n = rand()%10-5;
    
    for (int i=0; i < objects.size(); i++){
        if(objects[i].getZ() > 30.0){
            objects[i].setPosition(n, 1, -60);
        }
        
        glPushMatrix();
            objects[i].setPosition(objects[i].getX(), objects[i].getY(), objects[i].getZ() + 0.1);
            objects[i].draw();
        glPopMatrix();
    }
}

void Object::handleCollision(float x, float y, float z){
    for (int i=0; i < objects.size(); i++){
        if((objects[i].getZ() <= 15.0f && objects[i].getZ() >= 14.9f) && (objects[i].getX() <= x + 0.5 && objects[i].getX() >= x - 0.5)){
            if(objects[i].getObject())
                std::cout<<"Collision"<<std::endl;
        }
    }
}
