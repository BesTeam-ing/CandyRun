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
#include <math.h>
#include <vector>
#include <iomanip>
#include <iostream>

class Object{

public:
    Object();
    ~Object();
    
    void setPosition(float X,float Y,float Z);
    
    float getX();
    float getY();
    float getZ();
    
    unsigned int getTexture();
    
    bool getObject();
    void setObject(bool obj);
    
    void initObject();
    void drawObject();
    void handleCollision(float x, float y, float z);
    
private:
    unsigned int texture;
    float start_X = -1;
    float start_Y = -1;
    float start_Z = -1;
    
    float end_X = 1;
    float end_Y = 1;
    float end_Z = 1;
    
    float pos_X = 0;
    float pos_Y = 2;
    float pos_Z = -30;
    
    bool isEnemy = true;
    
    void draw();
};

#endif /* objects_hpp */
