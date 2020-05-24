//
//  GUI.cpp
//  CandyRun
//
//  Created by Gennaro Mellone on 20/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//


#include "GUI.hpp"

void GUI::draw(int score, int life){
    
    char S[10];
    sprintf(S,"%d", score);
    
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
//Gestisco lo SCORE
    
    //Disegno trapezio frontale
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
    
    //Disegno ombra trapezio
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
    
    //Disegno scritta SCORE
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(-18, 10, 1.1);
        glScalef(0.01,0.01,0.01);
        for( const char* p = "Score"; *p; p++){
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
        }
    glPopMatrix();
    
    //Aggiungo lo score
    glPushMatrix();
    glTranslatef(-17, 8.5, 1.1);
        glScalef(0.01,0.01,0.01);
        for( const char* p = S; *p; p++){
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
        }
    glPopMatrix();
    
//Gestisco le VITE
    
    //Disegno rettangolo Vite
    glColor4f(0.0, 0.1, 0.7, 0.5);
    glPushMatrix();
    glBegin(GL_POLYGON);
        glVertex3f(-19.0f, 6.7, 1);
        glVertex3f(-15, 6.7, 1);
        glVertex3f(-15, 4, 1);
        glVertex3f(-19.0f, 4, 1);
    glEnd();
    glPopMatrix();
    
    //Disegno ombra trapezio
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
    
    if (life >= 1 ){    // Se ho almeno UNA vita disegno il ROSSO
        glColor4f(0.5, 0.0, 0.0, 0.7);
        glPushMatrix();
        glBegin(GL_POLYGON);
        glVertex3f(-18.7, 5.5, 1.1);
            glVertex3f(-18.2, 5.5, 1.1);
            glVertex3f(-18.2, 4.2, 1.1);
        glVertex3f(-18.7, 4.2, 1.1);
        glEnd();
        glPopMatrix();
    }
    if (life >= 2){     // Se ho almeno DUE vita disegno il GIALLO
        glColor4f(0.5, 0.5, 0.0, 0.7);
        glPushMatrix();
        glBegin(GL_POLYGON);
            glVertex3f(-17.9, 5.5, 1.1);
            glVertex3f(-16.7, 5.5, 1.1);
            glVertex3f(-16.7, 4.2, 1.1);
            glVertex3f(-17.9, 4.2, 1.1);
        glEnd();
        glPopMatrix();
    }
    
    if (life >= 3){     // Se ho almeno TRE vite disegno il VERDE
        
        glColor4f(0.0, 0.5, 0.0, 0.7);
        glPushMatrix();
        glBegin(GL_POLYGON);
            glVertex3f(-16.4, 5.5, 1.1);
            glVertex3f(-15.2, 5.5, 1.1);
            glVertex3f(-15.2, 4.2, 1.1);
            glVertex3f(-16.4, 4.2, 1.1);
        glEnd();
        glPopMatrix();
    }
    glEnable(GL_LIGHTING);
    glDisable(GL_BLEND);
}
