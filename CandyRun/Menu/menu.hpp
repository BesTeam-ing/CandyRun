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

#include <stdio.h>

class Menu{
public:
    Menu();
    ~Menu();
    
    void drawMenu();
    void initMenu();
private:
    
};

#endif /* menu_hpp */
