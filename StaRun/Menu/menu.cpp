//
//  menu.cpp
//  CandyRun
//
//  Created by Ciro De Vita on 13/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#include "menu.hpp"

typedef struct polygon{
     float x1,y1,x2,y2;
} polygon;
  
polygon polygons[9];

int i = 0;
const int BACKGROUND_COUNT = 3;
const char* BACKGROUND[] = {
    "textures/sky191up.bmp",
    "textures/skyup.bmp",
    "textures/sky303up.bmp"
};
int texture, texture_back[BACKGROUND_COUNT];

/*
const int CHARACTER_COUNT = 2;
const char* CHARACTER_OBJ[] = {
    "textures/txStormydays_front.bmp",
    "textures/skyrt.bmp"
};
const char* CHARACTER_MTL[] = {
    "textures/txStormydays_front.bmp",
    "textures/skyrt.bmp"
};
 */

Menu::Menu(){}

Menu::~Menu(){}

int Menu::getBackground(){
    return this->background;
}

void Menu::initMenu(){
    //MENU BUTTONS z=-1
    polygons[0].x1=-4.0;
    polygons[0].x2=-1.0;
    polygons[0].y1=1.0;
    polygons[0].y2=1.75;
    
    polygons[1].x1=-4.0;
    polygons[1].x2=-1.0;
    polygons[1].y1=-0.25;
    polygons[1].y2=0.5;
    
    polygons[2].x1=-4.0;
    polygons[2].x2=-1.0;
    polygons[2].y1=-1.50;
    polygons[2].y2=-0.75;
    
    //TITLE z = -1
    polygons[3].x1=-3.0;
    polygons[3].x2=3.0;
    polygons[3].y1=2.5;
    polygons[3].y2=3.25;
    
    //WEATHER AND CHARACTER CHOISE z=-1
    polygons[4].x1=0.0;
    polygons[4].x2=4.0;
    polygons[4].y1=1.75;
    polygons[4].y2=-0.75;
    
    polygons[5].x1=0.0;
    polygons[5].x2=4.0;
    polygons[5].y1=-1.0;
    polygons[5].y2=-3.5;
    
    //BACKGROUND z = 0
    polygons[6].x1=-4.0;
    polygons[6].x2=4.0;
    polygons[6].y1=4.0;
    polygons[6].y2=-4.0;
    
    //z=-2
    polygons[7].x1=1.25;
    polygons[7].x2=2.75;
    polygons[7].y1=1.0;
    polygons[7].y2=-0.5;
    
    polygons[8].x1=1.25;
    polygons[8].x2=2.75;
    polygons[8].y1=-1.75;
    polygons[8].y2=-3.25;
    
    texture = SOIL_load_OGL_texture("textures/menu_item.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    
    for(int j=0; j<BACKGROUND_COUNT; j++){
        texture_back[j] = SOIL_load_OGL_texture(BACKGROUND[j], SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    }
}

void Menu::drawMenu(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glDisable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    
    glScalef(0.25,0.25,0.25);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_back[this->background]);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    //SFONDO Z=0
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);
        glVertex3f(polygons[6].x1 , polygons[6].y1, 2);
        glTexCoord2f(0.0f,1);
        glVertex3f(polygons[6].x1 , polygons[6].y2, 2);
        glTexCoord2f(1.0f,1);
        glVertex3f(polygons[6].x2  , polygons[6].y2, 2);
        glTexCoord2f(1.0f,0.0f);
        glVertex3f(polygons[6].x2  , polygons[6].y1, 2);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    
    
    //Z = -1
    for(int i=0;i<6;i++){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);
        glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f,0.0f);
            glVertex3f(polygons[i].x1 , polygons[i].y1, -1);
            glTexCoord2f(0.0f,1);
            glVertex3f(polygons[i].x1 , polygons[i].y2, -1);
            glTexCoord2f(1.0f,1);
            glVertex3f(polygons[i].x2  , polygons[i].y2, -1);
            glTexCoord2f(1.0f,0.0f);
            glVertex3f(polygons[i].x2  , polygons[i].y1, -1);
        glEnd();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    }
    
    //Z=-2
    for(int i=7; i<=8; i++){
        glPushMatrix();
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1.0, 1.0, 1.0, 0.5);
        glBegin(GL_QUADS);
            //glTexCoord2f(0.0f,0.0f);
            glVertex3f(polygons[i].x1 , polygons[i].y1, -2);
            //glTexCoord2f(0.0f,1);
            glVertex3f(polygons[i].x1 , polygons[i].y2, -2);
            //glTexCoord2f(1.0f,1);
            glVertex3f(polygons[i].x2  , polygons[i].y2, -2);
            //glTexCoord2f(1.0f,0.0f);
            glVertex3f(polygons[i].x2  , polygons[i].y1, -2);
        glEnd();
        glDisable(GL_BLEND);
        glPopMatrix();
    }
    
    DrawText(-0.40,2.75,"StaRun");
    DrawText(-2.9,1.25,"Start");
    DrawText(-3.3,0.0,"High Score");
    DrawText(-2.9,-1.25,"Exit");
    DrawText(1.25,1.35,"Character");
    DrawText(1.35,-1.40,"Weather");
    
    glFlush();
    glutSwapBuffers();
}

void Menu::DrawText(float x,float y, const char *text){
    glPushMatrix();
        glColor4f(1.0, 1.0, 0.0, 0.0);
        glTranslatef(x, y, -2);
        glScalef(0.0025,0.0025,0.0025);
        for( const char* p = text; *p; p++){
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
        }
    glPopMatrix();
}

int Menu::select(GLint x, GLint y){
    std::cout<<x<<" "<<y<<std::endl;
    
    if((x>=0 && x<=460) && (y>=210 && y<=270))
        return 1;
    
    else if((x>=0 && x<=460) && (y>=320 && y<=380))
        return 2;
    
    else if((x>=0 && x<=460) && (y>=430 && y<=490))
         return 3;
    
    return -1;
}

void Menu::drawBackground(int key){
    if(key == GLUT_KEY_RIGHT){
        i++;
        this->background = (i % BACKGROUND_COUNT + BACKGROUND_COUNT) % BACKGROUND_COUNT;
    }
    else if(key == GLUT_KEY_LEFT){
        i--;
        this->background = (i % BACKGROUND_COUNT + BACKGROUND_COUNT) % BACKGROUND_COUNT;
    }
}
