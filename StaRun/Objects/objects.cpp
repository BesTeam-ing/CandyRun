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
GLfloat lightPosition[] = { 0.0f, 5.0f, -8.0f, 0.0f };

Object::Object(){}
Object::~Object(){}

int wall, battery, light;

enum OBJ{
    WALL,
    BATTERY,
    LAMP
};

void Object::load(){
    wall = objload.load("textures/wall.obj","textures/wall.mtl");
    battery = objload1.load("textures/pila.obj","textures/pila.mtl");
    light = objload2.load("textures/lampione.obj","textures/lampione.mtl");
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

int Object::getObj(){
    return this->obj;
}

float Object::getRotation(){
    return this->angle_rotation;
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

void Object::setObj(int obj){
    this->obj = obj;
}

void Object::setRotation(float angle){
    this->angle_rotation = angle;
}

float spotDirection[] = {-1.0, -1.0, 0.0}; // Spotlight direction.
GLfloat Giallo[]      = { 1.0f, 1.0f, 0.0f, 1.0f };

void Object::draw(int obj){
    
// MODIFICARE PER LUCE
    float lightPos[] = { this->pos_X, 12.0, 8.0, 0.5 }; // Spotlight position.
//-------------
    
    switch (obj) {
        case WALL:
            glPushMatrix();
            glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);
            glEnable(GL_LIGHTING);
                glTranslatef(this->pos_X, this->pos_Y + 0.2, this->pos_Z);
                glCallList(wall);
            glDisable(GL_LIGHTING);
            glPopMatrix();
            
            break;
        
        case BATTERY:
            this->rotateAngle += 1;
            if(this->rotateAngle > 360.0f)
                this->rotateAngle -= 360.0f;
            glPushMatrix();
            glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);
            glEnable(GL_LIGHTING);
                glTranslatef(this->pos_X, this->pos_Y+0.5, this->pos_Z);
                //glLightfv(GL_LIGHT0,GL_POSITION,lightWall);
                glRotatef(this->rotateAngle, 0, -1, 0);
                glRotatef(this->angle_rotation, -1, 0, 0);
                glCallList(battery);
            glDisable(GL_LIGHTING);
            glPopMatrix();
            
            
            glPushMatrix();
                this->drawShadow(0.5, this->pos_X, this->pos_Z);
            glPopMatrix();
            break;
            
        
        case LAMP:
            glPushMatrix();
            glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);
            glEnable(GL_LIGHTING);
            
                glTranslatef(this->pos_X, this->pos_Y, this->pos_Z);
                glRotatef(this->angle_rotation, 0, -1, 0);
        
                glCallList(light);
            glDisable(GL_LIGHTING);
            glPopMatrix();
            
//MODIFICARE PER LUCE
            glPushMatrix();
                glEnable(GL_LIGHTING);
                glLightfv(GL_LIGHT2, GL_AMBIENT, Giallo);
                glLightfv(GL_LIGHT2, GL_DIFFUSE, Giallo);
            //FORSE QUESTO
                glTranslatef(this->pos_X, 0, this->pos_Z); // Move the spotlight.
                                  
            // Spotlight properties including position.
                glLightfv(GL_LIGHT2, GL_POSITION, lightPos);
                glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 25.0);
                glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDirection);
                glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 2.0f);
                glDisable(GL_LIGHTING);
            glPopMatrix();
            break;
         
            
        default:
            break;
    }
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
                    o.setRotation(45);
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
        o.setPosition(-7.0f, 2.1f, beginning_lamp+3);
        o.setObj(LAMP);
        o.setRotation(-35);
        v2.push_back(o);
        
        o.setPosition(7.0f, 2.1f, beginning_lamp+3);
        o.setObj(LAMP);
        o.setRotation(180);
        v2.push_back(o);
        
        lamp.push_back(v2);
        beginning_lamp += 20;
    }
}

void Object::drawObject(float speed,int x){
    //ENEMY OR BATTERY
    for (int i=0; i<objects.size(); i++) {
        for(int j=0; j<objects[i].size(); j++){
            int n = rand()%10-5;
            if(objects[i][j].getZ() > 30.0 or (objects[i][j].pos_Z == 15.0f && (objects[i][j].pos_X <= x + 0.5 && objects[i][j].pos_X >= x - 0.5) && objects[i][j].obj == BATTERY))
                
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
                lamp[i][j].setPosition(-7, 2.1f, -60);
            else if(lamp[i][j].getZ() > 30.0 && j==1)
                lamp[i][j].setPosition(7, 2.1f, -60);
           
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
            if(objects[i][j].pos_Z == 15.0f && (objects[i][j].pos_X <= x + 2.5 && objects[i][j].pos_X >= x - 2.5) && objects[i][j].obj == WALL)
                return OSTACOLO;
            
            else if(objects[i][j].pos_Z == 15.0f  && (objects[i][j].pos_X <= x + 0.5 && objects[i][j].pos_X >= x - 0.5) && objects[i][j].obj == BATTERY){
                return PREMIO;
            }
        }
    }

    return VUOTO;
}

void Object::drawShadow(float R, float X, float Y){
        glColor4f(0.3, 0.3, 0.3, 0.9);
        //glDisable(GL_LIGHTING);
        glRotatef(90, 1, 0, 0);
        GLfloat xOffset = X;
        GLfloat yOffset = Y +0.6;
        glBegin(GL_POLYGON);

        for(float t = -10 * PI; t <= 10 * PI; t += PI/20.0)
            glVertex3f(xOffset+R * cos(t), yOffset+R * sin(t)/2, -0.001);
        glEnd();

        //glEnable(GL_LIGHTING);
}
