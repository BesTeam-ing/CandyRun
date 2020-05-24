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

#include "../Server/Server.hpp"
#include "../Character/character.hpp"
#include "../OBJLoader/objloader.hpp"

#include <stdio.h>
#include <iostream>
#include <string>
#include <time.h>
#include <future>

class Menu{
public:
    Menu();
    ~Menu();
    
    void drawMenu();
    void initMenu();
    int select(GLint x, GLint y);
    
    int getBackground();
    int getCharacter();
    int getWeather();
    
private:
    void DrawText(float x,float y, float z, const char *text, int size);
    void draw();
    int background = 0;
    int character = 0;
    int weather = 0;
    
};

#endif /* menu_hpp */
