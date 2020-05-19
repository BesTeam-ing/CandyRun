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
  
polygon polygons[5];
int texture, texture_road;

Menu::Menu(){}

Menu::~Menu(){}

void Menu::initMenu(){
    polygons[0].x1=-2.0;
    polygons[0].x2=2.0;
    polygons[0].y1=1.25;
    polygons[0].y2=2.0;
    
    polygons[1].x1=-2.0;
    polygons[1].x2=2.0;
    polygons[1].y1=0;
    polygons[1].y2=0.75;
    
    polygons[2].x1=-2.0;
    polygons[2].x2=2.0;
    polygons[2].y1=-1.25;
    polygons[2].y2=-0.5;
    
    polygons[3].x1=-3.0;
    polygons[3].x2=3.0;
    polygons[3].y1=2.5;
    polygons[3].y2=3.25;
    
    polygons[4].x1=-4.0;
    polygons[4].x2=4.0;
    polygons[4].y1=4.0;
    polygons[4].y2=-4.0;
    
    texture = SOIL_load_OGL_texture("textures/menu_item.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    
    texture_road = SOIL_load_OGL_texture("textures/background.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}

void Menu::drawMenu(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glColor3f(0.0, 0.0, 0.0);
    glLoadIdentity();
    
    glDisable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    
    glScalef(0.25,0.25,0.25);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_road);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);
        glVertex3f(polygons[4].x1 , polygons[4].y1, 0);
        glTexCoord2f(0.0f,1);
        glVertex3f(polygons[4].x1 , polygons[4].y2, 0);
        glTexCoord2f(1.0f,1);
        glVertex3f(polygons[4].x2  , polygons[4].y2, 0);
        glTexCoord2f(1.0f,0.0f);
        glVertex3f(polygons[4].x2  , polygons[4].y1, 0);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    
    for(int i=0;i<4;i++){
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
    
    DrawText(-0.40,2.75,"StaRun");
    DrawText(-0.35,1.5,"Start");
    DrawText(-0.95,0.25,"High Score");
    DrawText(-0.35,-1,"Exit");
    
    glFlush();
    glutSwapBuffers();
}

void Menu::DrawText(float x,float y, const char *text){
    glPushMatrix();
        glColor4f(0.0, 0.0, 0.0, 0.0);
        glTranslatef(x, y, -2);
        glScalef(0.0025,0.0025,0.0025);
        for( const char* p = text; *p; p++){
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
        }
    glPopMatrix();
}

int Menu::select(GLint x, GLint y){
    if((x>=350 && x<=950) && (y>=180 && y<=240))
        return 1;
    
    else if((x>=350 && x<=950) && (y>=300 && y<=360))
        return 2;
    
    else if((x>=350 && x<=950) && (y>=410 && y<=470))
         return 3;
    
    return -1;
}
