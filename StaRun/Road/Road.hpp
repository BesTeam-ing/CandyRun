//
//  Road.hpp
//  CandyRun
//
//  Created by Ciro De Vita on 13/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#ifndef Road_hpp
#define Road_hpp

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <OpenGL/glext.h>
#include <SOIL2/SOIL2.h>
#include <math.h>
#include <vector>
#include <iostream>

class Road
{
private:
    unsigned int texture;
    float start_X = -7.0;
    float start_Y = 0.0;
    float start_Z = -15.0;
    
    float end_X = 7.0;
    float end_Y = 0.0;
    float end_Z = 15.0;
    
    float pos_X = 0;
    float pos_Y = 0;
    float pos_Z = 0;
    
    void init(const char* t);
    void draw();
    void setPosition(float X,float Y,float Z);
    
public:    
    Road();
    ~Road();
    
    float getX();
    float getY();
    float getZ();
    unsigned int getTexture();
    
    void initializeGround();
    void drawRoad();
};

#endif /* Road_hpp */