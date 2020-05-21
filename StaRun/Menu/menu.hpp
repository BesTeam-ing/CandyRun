//
//  menu.hpp
//  CandyRun
//
//  Created by Ciro De Vita on 13/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#ifndef menu_hpp
#define menu_hpp

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <OpenGL/glext.h>
#include <SOIL2/SOIL2.h>

#include <stdio.h>
#include <iostream>

class Menu{
public:
    Menu();
    ~Menu();
    
    void drawMenu();
    void initMenu();
    int select(GLint x, GLint y);
    void drawBackground(int key);
    
    int getBackground();
private:
    void DrawText(float x,float y, const char *text);
    int background = 0;
};

#endif /* menu_hpp */
