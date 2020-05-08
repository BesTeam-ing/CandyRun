//
//  skybox.hpp
//  CandyRun
//
//  Created by Gennaro Mellone on 08/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#ifndef skybox_hpp
#define skybox_hpp

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <OpenGL/glext.h>
#include <SOIL2/SOIL2.h>

enum FACES{
    FRONT,
    RIGHT,
    LEFT,
    BACK,
    UP,
    DOWN
};

class SkyBox{
public:
    SkyBox();
    
    ~SkyBox();
    
    void initSkyBox(char *front, char *right, char *left, char *back, char *up, char *down);
    void drawSkyBox(double D);
    
private:
    unsigned int skybox[6];
};

#endif /* skybox_hpp */
