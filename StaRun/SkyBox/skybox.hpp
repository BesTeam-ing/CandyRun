//
//  skybox.hpp
//  StaRun
//
//  Created by Ciro De Vita and Gennaro Mellone on 08/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#ifndef skybox_hpp
#define skybox_hpp

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <OpenGL/glext.h>
#include <SOIL2/SOIL2.h>

//skybox faces
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
    
    void initSkyBox(char const *front, char const *right, char const *left, char const *back, char const *up, char const *down);
    void drawSkyBox(double D);
    
private:
    unsigned int skybox[6]; //array that contains pointers to textures
};

#endif /* skybox_hpp */
