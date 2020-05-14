//
//  menu.cpp
//  CandyRun
//
//  Created by Ciro De Vita on 13/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#include "menu.hpp"

typedef struct polygon
{
     bool over; /* TRUE if polygon exists */
     float x1,y1,x2,y2; /* world coordinate */
     int xmin, xmax, ymin, ymax; /* bounding box */
} polygon;
 

/*all global variables*/
 
polygon polygons[4];
long selectedMenu=-1; // no button selected by mouse cursor
GLuint MenuFruitTexture;    //texture for main background
GLuint MainTitleTexture;        //texture for main Title
GLuint MenuItemsTexture;       //texture for buttons

Menu::Menu(){}

Menu::~Menu(){}

void Menu::initMenu(){
    polygons[0].xmin=200;
    polygons[0].xmax=570;
    polygons[0].ymin=150;
    polygons[0].ymax=205;
    
    polygons[1].xmin=200;
    polygons[1].xmax=570;
    polygons[1].ymin=245;
    polygons[1].ymax=300;
    
    polygons[2].xmin=200;
    polygons[2].xmax=570;
    polygons[2].ymin=338;
    polygons[2].ymax=393;
    
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
}

void Menu::drawMenu(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    
    glScalef(0.25,0.25,0.25);
    
    glPushMatrix();
        glColor3f(1.0, 0.25, 0.2);
        for(int i=0;i<4;i++){
            glBegin(GL_QUADS);
                glVertex2f(polygons[i].x1 , polygons[i].y1);
                glVertex2f(polygons[i].x1 , polygons[i].y2);
                glVertex2f(polygons[i].x2  , polygons[i].y2);
                glVertex2f(polygons[i].x2  , polygons[i].y1);
            glEnd();
        }
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1,1,1);
        DrawText(-0.85,2.75,"Candy Run");
        DrawText(-0.35,1.5,"Start");
        DrawText(-0.45,0.25,"Option");
        DrawText(-0.35,-1,"Exit");
    glPopMatrix();
}

void Menu::DrawText(float x,float y, const char *text){
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(0.0025,0.0025,0.0025);
    for( const char* p = text; *p; p++){
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
    }
    glPopMatrix();
}

int Menu::select(GLint x, GLint y){
    if((x>=350 && x<=950) && (y>=180 && y<=240))
        return 1;
    
    else if((x>=350 && x<=950) && (y>=410 && y<=470))
         return 2;
    
    return -1;
}
