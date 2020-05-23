//
//  character.cpp
//  CandyRun
//
//  Created by Ciro De Vita on 13/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#include "character.hpp"

//GLfloat lp[] = { 1.0, 0.7, 0.6, 0.0f };
GLfloat lp[] = {0.5, 0.5, 0.9, 0.4};

enum character{
    BB8,
    D0
};

objloader loader;

Character::Character(){};

Character::~Character(){};

void Character::init(const char* file_obj_body, const char* file_mtl_body, const char* file_obj_head, const char* file_mtl_head, int value){
    this->body = loader.load(file_obj_body,file_mtl_body);
    this->head = loader.load(file_obj_head, file_mtl_head);
    this->character_choosen = value;
}

void Character::initialPosition(){
    this->x = 0.0f;
    this->y = 0.5f;
    this->z = 14.2f;
    this->rotateAngle = 0.0f;
    this->lifes = 3;
    this->score = 0;
}

float Character::getX(){
    return this->x;
}

float Character::getY(){
    return this->y;
}

float Character::getZ(){
    return this->z;
}

void Character::setX(float x){
    if((this->x + x) > 7 || (this->x + x) < -7)
        return;
    else
        this->x += x;
}

void Character::setY(float y){
    this->y += y;
}

void Character::setZ(float z){
    this->z += z;
}

void Character::setScore(int x){
    this->score += x;
}

int Character::getScore(){
    return this->score;
}

void Character::setLife(int x){
    this->lifes += x;
}

int Character::getLife(){
    return this->lifes;
}

int Character::ReadHighScore() {
    std::ifstream fin("/Users/ciro/Desktop/Università/Computer Graphics/Progetto/StaRun/StaRun/Character/highscore.txt");

    if (!fin.is_open()) {
        std::cout << "Impossibile aprire il file!" << std::endl;
        return -1;
    }

    int score = 0;
    fin >> score;
    fin.close();

    return score;
}

void Character::SaveHighScore() {    
    if(ReadHighScore() < this->score){
        std::ofstream myfile;
        myfile.open("/Users/ciro/Desktop/Università/Computer Graphics/Progetto/StaRun/StaRun/Character/highscore.txt");

        if (!myfile.is_open()) {
            std::cout << "Unable to update highscore" << std::endl;
            return;
        }

        myfile << this->score;
        myfile.close();
    }
}

void Character::drawCharacter(){
    this->rotateAngle += 1;
    if(this->rotateAngle > 360.0f)
        this->rotateAngle -= 360.0f;
    
    //glLightfv(GL_LIGHT0,GL_POSITION,lp)
    
    //D0
    if(this->character_choosen == D0){
        //CORPO
        glPushMatrix();
            glTranslatef(this->x, this->y, this->z);
            glRotatef(this->rotateAngle, -1, 0, 0);
            glRotatef(90, 0, 1, 0);
            glLightfv(GL_LIGHT0,GL_POSITION,lp);
            glCallList(this->body);
        glPopMatrix();
        
        //TESTA
        glPushMatrix();
            glTranslatef(this->x, this->y, this->z);
            glRotatef(180, 0, -1, 0);
            glRotatef(90, 0, -1, 0);
            glRotatef(10, -1, 0, 0);
            glRotatef(10, 1, 0, 0);
            glLightfv(GL_LIGHT0,GL_POSITION,lp);
            glCallList(this->head);
        glPopMatrix();
    }
    else if(this->character_choosen == BB8){ //BB8
        //CORPO
        glPushMatrix();
            glTranslatef(this->x, this->y, this->z);
            glRotatef(this->rotateAngle, -1, 0, 0);
            glLightfv(GL_LIGHT0,GL_POSITION,lp);
            glCallList(this->body);
        glPopMatrix();
        
        //TESTA
        /*
        glPushMatrix();
            glTranslatef(this->x, this->y, this->z);
            glRotatef(180, 0, -1, 0);
            //glRotatef(10, 0, 0, 1); TESTA A DESTRA
            glRotatef(10, 1, 0, 0);
            glLightfv(GL_LIGHT0,GL_POSITION,lp);
            glCallList(this->head);
        glPopMatrix();
         */
    }
    
    glPushMatrix();
        drawShadow(0.5, this->x, this->y, 15);
    glPopMatrix();
}

void Character::drawShadow(float R, float X, float Y, int vert){
        glColor4f(0.3, 0.3, 0.3, 0.9);
        glDisable(GL_LIGHTING);
        
        
        glRotatef(90, 1, 0, 0);
        GLfloat xOffset = X;
        GLfloat yOffset = this->z +0.6;
        glBegin(GL_POLYGON);

        for(float t = -10 * PI; t <= 10 * PI; t += PI/20.0)
            glVertex3f(xOffset+R * cos(t), yOffset+R * sin(t)/2, -0.001);
        glEnd();

        glEnable(GL_LIGHTING);
        /*float t = 0;
        
        glBegin(GL_LINE_LOOP);
        
           for(int i = 0; i < vert; ++i)
           {
              glColor3f((float)rand()/(float)RAND_MAX, (float)rand()/(float)RAND_MAX, (float)rand()/(float)RAND_MAX);
              glVertex3f(X + R * cos(t), Y + R * sin(t), 0.0);
              t += 2 * PI / vert;
           }
        glEnd();*/
}
    /*
    glMaterialfv( GL_FRONT, GL_AMBIENT,  bluTenue );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,  blu );
    glMaterialfv( GL_FRONT, GL_SPECULAR, bianco );
    glMaterialf( GL_FRONT, GL_SHININESS, 20.0f );
    glPushMatrix();
        glTranslatef(this->x, this->y, this->z-3);
        glRotatef(this->rotateAngle, -1, 0, 0);
        glutWireSphere(this->size, 20, 20);
    glPopMatrix();
    */
