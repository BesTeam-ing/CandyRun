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

#include <iostream>
// CLASSES

class Road
{
    
private:
    unsigned int texture;
    float start_X = -5.0;
    float start_Y = 0.0;
    float start_Z = -10.0;
    
    float end_X = 5.0;
    float end_Y = 0.0;
    float end_Z = 10.0;
    
    float pos_X = 0;
    float pos_Y = 0;
    float pos_Z = 0;
    
public:
    bool alive = true;
    
    Road();
    ~Road();
    
    void init(char* t);
    void draw();
    void setPosition(float X,float Y,float Z);
    float getX();
    float getY();
    float getZ();
    unsigned int getTexture();
};

//OTHER FUNCTIONS
void drawRoad();


#endif /* objects_hpp */
