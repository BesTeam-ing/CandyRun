//
//  objects.cpp
//  CandyRun
//
//  Created by Gennaro Mellone on 09/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#include "objects.hpp"

Road::Road(){}
Road::~Road(){}

void Road::init(char *t){

    texture = SOIL_load_OGL_texture(t, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}

void Road::draw(){
    glColor4f(0.2, 0.2, 0.2, 0.1);
    glEnable(GL_TEXTURE_2D);
           glBindTexture(GL_TEXTURE_2D, this->texture);
           glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
           glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

           //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);
           glBegin(GL_QUADS);
               glTexCoord2f(0.0f,0.0f);
               glVertex3f(-5.0f, 0.0f, -10000.0f);
               glTexCoord2f(0.0f,2000.0f);
               glVertex3f(-5.0f, 0.0f, 10000.0f);
               glTexCoord2f(1.0f,2000.0f);
               glVertex3f(5.0f, 0.0f, 10000.0f);
               glTexCoord2f(1.0f,0.0f);
               glVertex3f(5.0f, 0.0f, -10000.0f);
           glEnd();
        glDisable(GL_TEXTURE_2D);
}

