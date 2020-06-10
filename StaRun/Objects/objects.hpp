//
//  objects.hpp
//  StaRun
//
//  Created by Ciro De Vita and Gennaro Mellone on 09/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#ifndef objects_hpp
#define objects_hpp

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <OpenGL/glext.h>
#include <SOIL2/SOIL2.h>

#include "../OBJLoader/objloader.hpp"

#include <math.h>
#include <vector>
#include <iomanip>
#include <iostream>
#define PI 3.14159265358979324

enum OBJECT{
    VUOTO,
    OSTACOLO,
    PREMIO
};

class Object{

public:
    Object();
    ~Object();
    
    void setPosition(float X,float Y,float Z);
    
    float getX();
    float getY();
    float getZ();
    float getRotation();
    void setRotation(float angle);
    
    void load();
    unsigned int getTexture();
    
    int getObj();
    void setObj(int obj);
    
    void initObject();
    void drawObject(float speed, int x);
    int handleCollision(float x, float y, float z);
    
private:
    unsigned int texture;
    float start_X = -1;
    float start_Y = -1;
    float start_Z = -1;
    
    float end_X = 1;
    float end_Y = 1;
    float end_Z = 1;
    
    float pos_X = 0;
    float pos_Y = 1;
    float pos_Z = -30;
    
    GLfloat r = 0.0;
    GLfloat g = 0.0;
    GLfloat b = 0.0;
    
    int obj;
    objloader objload, objload1, objload2;
    
    float angle_rotation = 0.0f;
    float rotateAngle = 0.0f;
    
    const GLfloat lightWall[4] = { -2.1, 2.9, 0.5, 0.4};
    const GLfloat lightB[4] = { 0.1, 0.9, 0.5, 0.1};
    const GLfloat lightL[4] = { 4.0, 2.8, 0.1, 0.8};
    void drawShadow(float R, float X, float Y);
    void drawShadowWall(float X, float Y);
    
    void draw(int obj);
};

#endif /* objects_hpp */
