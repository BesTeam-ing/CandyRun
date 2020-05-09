//
//  skybox.cpp
//  CandyRun
//
//  Created by Gennaro Mellone on 08/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#include "skybox.hpp"

SkyBox::SkyBox(){}

SkyBox::~SkyBox(){}

void SkyBox::initSkyBox(char const *front, char const *right, char const *left, char const *back, char const *up, char const *down){
    this->skybox[FRONT] = SOIL_load_OGL_texture(front, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    this->skybox[RIGHT] = SOIL_load_OGL_texture(right, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    this->skybox[LEFT] = SOIL_load_OGL_texture(left, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    this->skybox[BACK] = SOIL_load_OGL_texture(back, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    this->skybox[UP] = SOIL_load_OGL_texture(up, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    this->skybox[DOWN] = SOIL_load_OGL_texture(down, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}

void SkyBox::drawSkyBox(double D){
    glColor3f(1.0f,1.0f,1.0f);
    glEnable(GL_TEXTURE_2D);

        /* Sides */
        glBindTexture(GL_TEXTURE_2D,this->skybox[RIGHT]);
        glBegin(GL_QUADS);
            glTexCoord2f(0,0); glVertex3f(-D,-D,-D);
            glTexCoord2f(1,0); glVertex3f(+D,-D,-D);
            glTexCoord2f(1,1); glVertex3f(+D,+D,-D);
            glTexCoord2f(0,1); glVertex3f(-D,+D,-D);
        glEnd();
        
        glBindTexture(GL_TEXTURE_2D,this->skybox[FRONT]);
        glBegin(GL_QUADS);
            glTexCoord2f(0,0); glVertex3f(+D,-D,-D);
            glTexCoord2f(1,0); glVertex3f(+D,-D,+D);
            glTexCoord2f(1,1); glVertex3f(+D,+D,+D);
            glTexCoord2f(0,1); glVertex3f(+D,+D,-D);
        glEnd();
        
        glBindTexture(GL_TEXTURE_2D,this->skybox[LEFT]);
        glBegin(GL_QUADS);
            glTexCoord2f(0,0); glVertex3f(+D,-D,+D);
            glTexCoord2f(1,0); glVertex3f(-D,-D,+D);
            glTexCoord2f(1,1); glVertex3f(-D,+D,+D);
            glTexCoord2f(0,1); glVertex3f(+D,+D,+D);
        glEnd();
        
        glBindTexture(GL_TEXTURE_2D,this->skybox[BACK]);
        glBegin(GL_QUADS);
            glTexCoord2f(0,0); glVertex3f(-D,-D,+D);
            glTexCoord2f(1,0); glVertex3f(-D,-D,-D);
            glTexCoord2f(1,1); glVertex3f(-D,+D,-D);
            glTexCoord2f(0,1); glVertex3f(-D,+D,+D);
        glEnd();

        /* Top and Bottom */
        glBindTexture(GL_TEXTURE_2D,this->skybox[UP]);
        glBegin(GL_QUADS);
            glTexCoord2f(0,0); glVertex3f(-D,+D,-D);
            glTexCoord2f(1,0); glVertex3f(+D,+D,-D);
            glTexCoord2f(1,1); glVertex3f(+D,+D,+D);
            glTexCoord2f(0,1); glVertex3f(-D,+D,+D);
        glEnd();
        
        glBindTexture(GL_TEXTURE_2D,this->skybox[DOWN]);
        glBegin(GL_QUADS);
            glTexCoord2f(1,1); glVertex3f(+D,-D,-D);
            glTexCoord2f(0,1); glVertex3f(-D,-D,-D);
            glTexCoord2f(0,0); glVertex3f(-D,-D,+D);
            glTexCoord2f(1,0); glVertex3f(+D,-D,+D);
        glEnd();
    
    glDisable(GL_TEXTURE_2D);
    
    
     glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, this->skybox[UP]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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
