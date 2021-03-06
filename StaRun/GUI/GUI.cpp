//
//  GUI.cpp
//  StaRun
//
//  Created by Ciro De Vita and Gennaro Mellone on 20/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//


#include "GUI.hpp"

GUI::GUI(){}

GUI::~GUI(){}

void GUI::draw(int score, int life){
    
    char S[10];
    sprintf(S,"%d", score);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    //trapeze
    glColor4f(0.0, 0.1, 0.7, 0.5);
    glPushMatrix();
    glBegin(GL_POLYGON);
        glVertex3f(-19.0f, 12, 1);
        glVertex3f(-10, 12, 1);
        glVertex3f(-10, 10, 1);
        glVertex3f(-15, 7.5, 1);
        glVertex3f(-19.0f, 7.5, 1);
    glEnd();
    glPopMatrix();
    
    //trapeze's shadow
    glColor4f(0.2, 0.2, 0.2, 0.3);
    glPushMatrix();
    glBegin(GL_POLYGON);
        glVertex3f(-19.0f, 12, -0.1f);
        glVertex3f(-10, 12, -0.1f);
        glVertex3f(-10, 10, -0.1f);
        glVertex3f(-15, 7.5, -0.1f);
        glVertex3f(-19.0f, 7.5, -0.1f);
    glEnd();
    glPopMatrix();
    
    //score
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(-18, 10, 1.1);
        glScalef(0.01,0.01,0.01);
        for( const char* p = "Score"; *p; p++){
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
        }
    glPopMatrix();
    
    //score update
    glColor4f(1.0, 1.0, 0.0, 1.0);
    glPushMatrix();
        glTranslatef(-17, 8.5, 1.1);
        glScalef(0.01,0.01,0.01);
        for( const char* p = S; *p; p++){
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
        }
    glPopMatrix();
    
    //lives
    glColor4f(0.0, 0.1, 0.7, 0.5);
    glPushMatrix();
    glBegin(GL_POLYGON);
        glVertex3f(-19.0f, 6.7, 1);
        glVertex3f(-15, 6.7, 1);
        glVertex3f(-15, 4, 1);
        glVertex3f(-19.0f, 4, 1);
    glEnd();
    glPopMatrix();
    
    //lives shadow
    glColor4f(0.2, 0.2, 0.2, 0.3);
    glPushMatrix();
    glBegin(GL_POLYGON);
        glVertex3f(-19.0f, 6.7, -0.1f);
        glVertex3f(-15, 6.7, -0.1f);
        glVertex3f(-15, 4, -0.1f);
        glVertex3f(-19.0f, 4, -0.1f);
    glEnd();
    glPopMatrix();
    
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(-18.7, 6, 1.1);
        glScalef(0.004,0.004,0.004);
        for( const char* p = "Autonomy"; *p; p++){
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
        }
    glPopMatrix();
    
    //lives handling
    if (life >= 1 ){ //if i have only one life, draw RED
        glColor4f(0.7, 0.0, 0.0, 0.9);
        glPushMatrix();
        glBegin(GL_POLYGON);
        glVertex3f(-18.7, 5.5, 1.1);
            glVertex3f(-18.2, 5.5, 1.1);
            glVertex3f(-18.2, 4.2, 1.1);
        glVertex3f(-18.7, 4.2, 1.1);
        glEnd();
        glPopMatrix();
    }
    if (life >= 2){ //if i have at least two lives, draw YELLOW
        glColor4f(0.7, 0.7, 0.0, 0.9);
        glPushMatrix();
        glBegin(GL_POLYGON);
            glVertex3f(-17.9, 5.5, 1.1);
            glVertex3f(-16.7, 5.5, 1.1);
            glVertex3f(-16.7, 4.2, 1.1);
            glVertex3f(-17.9, 4.2, 1.1);
        glEnd();
        glPopMatrix();
    }
    
    if (life >= 3){ //if i havethree lives, draw GREEN
        glColor4f(0.0, 0.7, 0.0, 0.9);
        glPushMatrix();
        glBegin(GL_POLYGON);
            glVertex3f(-16.4, 5.5, 1.1);
            glVertex3f(-15.2, 5.5, 1.1);
            glVertex3f(-15.2, 4.2, 1.1);
            glVertex3f(-16.4, 4.2, 1.1);
        glEnd();
        glPopMatrix();
    }
    glDisable(GL_BLEND);
}
