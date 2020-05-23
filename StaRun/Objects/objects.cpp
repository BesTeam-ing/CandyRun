//
//  objects.cpp
//  CandyRun
//
//  Created by Gennaro Mellone on 09/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#include "objects.hpp"

GLfloat lp1[] = { 0.0f, 1.0f, -1.0f, 0.0f };
std::vector< std::vector<Object> > objects(4);
std::vector< std::vector<Object> > lamp(2);
Object o;

Object::Object(){}
Object::~Object(){}

int wall, battery;

enum OBJ{
    WALL,
    BATTERY,
    LAMP
};

void Object::load(){
    battery = objload1.load("textures/pila.obj","textures/pila.mtl");;
    wall = objload.load("textures/wall.obj","textures/wall.mtl");
}

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

void Object::draw(int obj){
    switch (obj) {
        case WALL:
            glPushMatrix();
            glTranslatef(this->pos_X, this->pos_Y, this->pos_Z);
                glScalef(1, 1, 0.1);
                glLightfv(GL_LIGHT0,GL_POSITION,lightWall);
                glCallList(wall);
            glPopMatrix();
            break;
        
        case BATTERY:
            glPushMatrix();
                glTranslatef(this->pos_X, this->pos_Y, this->pos_Z);
                glLightfv(GL_LIGHT0,GL_POSITION,lightWall);
                glCallList(battery);
            glPopMatrix();
            
        /*
        case LAMP:
            glPushMatrix();
                glTranslatef(this->pos_X, this->pos_Y, this->pos_Z);
                glLightfv(GL_LIGHT0,GL_POSITION,lightWall);
                //glCallList(_lamp);
            glPopMatrix();
            break;
         */
            
        default:
            break;
    }
}

int Object::getObj(){
    return this->obj;
}

void Object::setObj(int obj){
    this->obj = obj;
}

void Object::initObject(){
    objects.clear();
    lamp.clear();
    
    //ENEMY OR BATTERY
    float beginning = -60.0;
    for (int i=0; i<4; i++) {
        std::vector<Object> v1;
        int x = 0;
        for(int j=0; j<2; j++){
            int n = rand()%10-5;
            int e;
            if(x<1){
                if (rand() % 2 == 0){
                    e = WALL;
                    o.setPosition(n, 0.5f, beginning+7);
                }
                else{
                    e = BATTERY;
                    x++;
                    o.setPosition(n, 0.5f, beginning);
                }
            }
            else{
                e = WALL;
                o.setPosition(n, 0.5f, beginning+7);
            }
            
            o.setObj(e);
            
            v1.push_back(o);
        }
        objects.push_back(v1);
        beginning += 20;
    }
    
    //LAMPIONI
    float beginning_lamp = -60.0;
    for (int i=0; i<4; i++) {
        std::vector<Object> v2;
        o.setPosition(-7.0f, 0.5f, beginning_lamp+3);
        o.setObj(LAMP);
        v2.push_back(o);
        
        o.setPosition(7.0f, 0.5f, beginning_lamp+3);
        o.setObj(LAMP);
        v2.push_back(o);
        
        lamp.push_back(v2);
        beginning_lamp += 20;
    }
}

void Object::drawObject(float speed){
    //ENEMY OR BATTERY
    for (int i=0; i<objects.size(); i++) {
        for(int j=0; j<objects[i].size(); j++){
            int n = rand()%10-5;
            if(objects[i][j].getZ() > 30.0)
                objects[i][j].setPosition(n, 1, -60);
           
            glPushMatrix();
                objects[i][j].setPosition(objects[i][j].getX(), objects[i][j].getY(), roundf((objects[i][j].getZ() + speed)*100)/100);
                objects[i][j].draw(objects[i][j].obj);
            glPopMatrix();
        }
    }
    
    //LAMP
    for (int i=0; i<lamp.size(); i++) {
        for(int j=0; j<lamp[i].size(); j++){
            if(lamp[i][j].getZ() > 30.0 && j==0)
                lamp[i][j].setPosition(-7, 1, -60);
            else if(lamp[i][j].getZ() > 30.0 && j==1)
                lamp[i][j].setPosition(7, 1, -60);
           
            glPushMatrix();
                lamp[i][j].setPosition(lamp[i][j].getX(), lamp[i][j].getY(), roundf((lamp[i][j].getZ() + speed)*100)/100);
            lamp[i][j].draw(lamp[i][j].obj);
            glPopMatrix();
        }
    }
}

int Object::handleCollision(float x, float y, float z){
    for (int i=0; i<objects.size(); i++) {
        for(int j=0; j<objects[i].size(); j++){
            if((objects[i][j].pos_Z <= 15.0f && objects[i][j].pos_Z >= 14.99f) && (objects[i][j].pos_X <= x + 2.5 && objects[i][j].pos_X >= x - 2.5) && objects[i][j].obj == WALL)
                return OSTACOLO;
            else if((objects[i][j].pos_Z <= 15.0f && objects[i][j].pos_Z >= 14.99f) && (objects[i][j].pos_X <= x + 0.5 && objects[i][j].pos_X >= x - 0.5) && objects[i][j].obj == BATTERY){
                //objects[i][j].setPosition(0, 0, 30);
                return PREMIO;
            }
        }
    }

    return VUOTO;
}
