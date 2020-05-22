//
//  objects.hpp
//  CandyRun
//
//  Created by Gennaro Mellone on 09/05/2020.
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
    
    void load();
    unsigned int getTexture();
    void setDimension(float f);
    void setColor(GLfloat r, GLfloat g, GLfloat b);
    
    bool getEnemy();
    void setEnemy(bool obj);
    
    void initObject();
    void drawObject(float speed);
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
    
    bool isEnemy = true;
    
    objloader objload, objload1;
    
    const GLfloat lightWall[4] = { 0.1, 0.5, 0.5, 0.1};
    
    void draw(bool isEnemy);
};

#endif /* objects_hpp */
