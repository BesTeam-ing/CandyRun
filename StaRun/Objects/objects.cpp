//
//  objects.cpp
//  StaRun
//
//  Created by Ciro De Vita and Gennaro Mellone on 09/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#include "objects.hpp"

std::vector< std::vector<Object> > objects(4);
std::vector< std::vector<Object> > lamp(2);
Object o; //Used to manage an object

//Lights properties
GLfloat lightPosition[] = { 0.0f, 10.0f, -8.0f, 0.05f };
GLfloat lampLight[] = { 0.0f, 5.0f, -8.0f, 1.0f };
GLfloat lp_wall[] = { 0.0f, 7.0f, -10.0f, 1.0f };
GLfloat Giallo[] = { 1.0f, 1.0f, 0.0f, 1.0f };

float spotDirection[] = {1.0, -1.0, 0.0};
float spotDirection1[] = {-1.0, -1.0, 0.0};

float lightPos[] = {-2.2, 0.85, 0.0, 0.01};
float lightPos1[] = {2.2, 0.85, 0.0, 0.01};

int wall, battery, light; //Textures variables

//Object Class

Object::Object(){}
Object::~Object(){}

enum OBJ{
    WALL,
    BATTERY,
    LAMP
};

//Load object textures
void Object::load(){
    wall = objload.load("textures/wall.obj","textures/wall.mtl");
    battery = objload1.load("textures/pila.obj","textures/pila.mtl");
    light = objload2.load("textures/lampione.obj","textures/lampione.mtl");
}

// Get and Set Functions
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
void Object::setObj(int obj){
    this->obj = obj;
}
void Object::setRotation(float angle){
    this->angle_rotation = angle;
}

// Function to draw objects (wall, lights and batteries)
void Object::draw(int obj){
    switch (obj) {
        case WALL:
            glLightfv(GL_LIGHT0,GL_POSITION,lp_wall);
            //Draw a wall
            glPushMatrix();
                glEnable(GL_LIGHTING);
                    glTranslatef(this->pos_X, this->pos_Y + 0.2, this->pos_Z);
                    glLightfv(GL_LIGHT0,GL_POSITION,lp_wall);
                    glCallList(wall);
                glDisable(GL_LIGHTING);
            glPopMatrix();
            
            //Draw wall's shadow
            glPushMatrix();
                this->drawShadowWall(this->pos_X, this->pos_Z);
            glPopMatrix();
            
            break;
        
        case BATTERY:
            //Draw battery
            this->rotateAngle += 1;
            if(this->rotateAngle > 360.0f)
                this->rotateAngle -= 360.0f;
            
            glPushMatrix();
                glEnable(GL_LIGHTING);
                    glTranslatef(this->pos_X, this->pos_Y+0.5, this->pos_Z);
                    glRotatef(this->rotateAngle, 0, -1, 0);
                    glRotatef(this->angle_rotation, -1, 0, 0);
                    glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);
                    glCallList(battery);
                glDisable(GL_LIGHTING);
            glPopMatrix();
            
            //Draw battery shadow
            glPushMatrix();
                this->drawShadow(0.5, this->pos_X, this->pos_Z);
            glPopMatrix();
            break;
            
        
        case LAMP:
            //Draw lamp
            glPushMatrix();
                glLightfv(GL_LIGHT0,GL_POSITION,lampLight);
                glEnable(GL_LIGHTING);
                    glTranslatef(this->pos_X, this->pos_Y, this->pos_Z);
                    glRotatef(this->angle_rotation, 0, -1, 0);
                    glCallList(light);
                glDisable(GL_LIGHTING);
            glPopMatrix();
            
            //Left lamp light
            glPushMatrix();
                glEnable(GL_LIGHTING);
                glLightfv(GL_LIGHT2, GL_AMBIENT, Giallo);
                glLightfv(GL_LIGHT2, GL_DIFFUSE, Giallo);
            
                //Spotlight properties including position.
                glLightfv(GL_LIGHT2, GL_POSITION, lightPos);
                glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 25.0);
                glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDirection);
                glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 2.0f);
                glDisable(GL_LIGHTING);
            glPopMatrix();
            
            //Right lamp light
            glPushMatrix();
                glEnable(GL_LIGHTING);
                glLightfv(GL_LIGHT3, GL_AMBIENT, Giallo);
                glLightfv(GL_LIGHT3, GL_DIFFUSE, Giallo);
            
                //Spotlight properties including position.
                glLightfv(GL_LIGHT3, GL_POSITION, lightPos1);
                glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 25.0);
                glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spotDirection1);
                glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 2.0f);
                glDisable(GL_LIGHTING);
            glPopMatrix();
            
            break;
            
        default:
            break;
    }
    
}

//Initialize objects to fit on the road
void Object::initObject(){
    objects.clear();
    lamp.clear();
    
    //CHOSE WALL OR BATTERY
    float beginning = -60.0;
    for (int i = 0; i < 4; i++) {
        std::vector<Object> v1;
        int x = 0;
        for(int j = 0; j < 2; j++){
            int n = rand()%10-5;
            int e;
            
            if(x < 1){
                if (rand() % 2 == 0){
                    e = WALL;
                    o.setPosition(n, 1.0f, beginning+5);
                }
                else{
                    e = BATTERY;
                    x++;
                    o.setPosition(n, 1.0f, beginning);
                    o.setRotation(45);
                }
            }
            else{
                e = WALL;
                o.setPosition(n, 1.0f, beginning+5);
            }
            
            o.setObj(e);
            v1.push_back(o); //Push object in the vector
        }
        objects.push_back(v1); //Push vector v1 in vector objects
        beginning += 20;
    }
    
    //INTIALIZE LAMPS
    float beginning_lamp = -60.0;
    for (int i = 0; i < 4; i++) {
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

//Function to draw objects
void Object::drawObject(float speed,int x){
    //ENEMY OR BATTERY
    for (int i = 0; i < objects.size(); i++) {
        for(int j = 0; j < objects[i].size(); j++){
            int n = rand()%10-5;
            
            //If object goes out of the view or hit a battery, restore position
            if(objects[i][j].getZ() > 30.0 or (objects[i][j].pos_Z == 15.0f && (objects[i][j].pos_X <= x + 0.5 && objects[i][j].pos_X >= x - 0.5) && objects[i][j].obj == BATTERY)){
                
                objects[i][j].setPosition(n, 1, -60);
            }
           
            objects[i][j].setPosition(objects[i][j].getX(), objects[i][j].getY(), roundf((objects[i][j].getZ() + speed)*100)/100); //Set the object position
            objects[i][j].draw(objects[i][j].obj); //Draw the object in the right position
        }
    }
    
    //DRAW LAMPS
    for (int i=0; i<lamp.size(); i++) {
        for(int j=0; j<lamp[i].size(); j++){
            
            //If left lamp goes out of the view, restore default position
            if(lamp[i][j].getZ() > 30.0 && j==0)
                lamp[i][j].setPosition(-7, 2.1f, -60);
            //If right lamp goes out of the view, restore default position
            else if(lamp[i][j].getZ() > 30.0 && j==1)
                lamp[i][j].setPosition(7, 2.1f, -60);
           
            lamp[i][j].setPosition(lamp[i][j].getX(), lamp[i][j].getY(), roundf((lamp[i][j].getZ() + speed)*100)/100); //Set lamp position
            lamp[i][j].draw(lamp[i][j].obj); //Draw lamp

        }
    }
}

//Function to handle collision between objects and character
int Object::handleCollision(float x, float y, float z){

    for (int i = 0; i < objects.size(); i++) {
        for(int j = 0; j < objects[i].size(); j++){
            //If hit an Enemy
            if(objects[i][j].pos_Z == 15.0f && (objects[i][j].pos_X <= x + 2.5 && objects[i][j].pos_X >= x - 2.5) && objects[i][j].obj == WALL)
                return OSTACOLO;
            
            //If hit a Bonus
            else if(objects[i][j].pos_Z == 15.0f  && (objects[i][j].pos_X <= x + 0.5 && objects[i][j].pos_X >= x - 0.5) && objects[i][j].obj == BATTERY){
                return PREMIO;
            }
        }
    }
    
    //else return VUOTO
    return VUOTO;
}

//Function to draw battery shadow (circle)
void Object::drawShadow(float R, float X, float Y){

    glColor4f(0.2, 0.2, 0.2, 0.9);
    glDisable(GL_LIGHTING);
    glRotatef(90, 1, 0, 0);
    GLfloat xOffset = X;
    GLfloat yOffset = Y +0.6;
    
    glBegin(GL_POLYGON);
        for(float t = -10 * PI; t <= 10 * PI; t += PI/20.0)
            glVertex3f(xOffset+R * cos(t), yOffset+R * sin(t)/2, -0.001);
    glEnd();
}

//Function to draw wall shadow (trapeze)
void Object::drawShadowWall(float X, float Y){

    float offsetX = 2.4;
    float offsetY = 0.6;
    float trap = 0.5;
    
    glColor4f(0.1, 0.1, 0.1, 0.9);
    glDisable(GL_LIGHTING);
    glRotatef(90, 1, 0, 0);

    glBegin(GL_POLYGON);
        glVertex3f(X - offsetX, Y, -0.001);
        glVertex3f(X + offsetX, Y, -0.001);
        glVertex3f(X + offsetX - trap, Y + offsetY, -0.001);
        glVertex3f(X - offsetX + trap, Y + offsetY, -0.001);
    glEnd();
}
