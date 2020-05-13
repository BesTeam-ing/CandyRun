//
//  menu.cpp
//  CandyRun
//
//  Created by Ciro De Vita on 13/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#include "menu.hpp"

Menu::Menu(){}

Menu::~Menu(){}

void Menu::initMenu(){
    glOrtho(0.0, 100.0, 0.0, 100.0, 0.0, 20.0);
}

void Menu::drawMenu(){
    glColor3f(0.0, 1.0, 0.0); //colore
    
    glPushMatrix();
        glBegin(GL_POLYGON);
            glVertex3f(-5.0, 0.0, 1.0);
            glVertex3f(105.0, 0.0, 1.0);
            glVertex3f(105.0, 100.0, 1.0);
            glVertex3f(-5.0, 100.0, 1.0);
        glEnd();
    glPopMatrix();
}
