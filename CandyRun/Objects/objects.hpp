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

class Road{
    
private:
    unsigned int texture;
    float start_X;
    float start_Y;
    float start_Z;
    float end_X;
    float end_Y;
    float end_Z;
    
public:
    Road();
    ~Road();
    
    void init(char* t);
    void draw();
};

#endif /* objects_hpp */
