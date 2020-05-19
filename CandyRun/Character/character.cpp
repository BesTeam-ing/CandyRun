//
//  character.cpp
//  CandyRun
//
//  Created by Ciro De Vita on 13/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#include "character.hpp"


GLfloat lp[] = { 1.0, 0.7, 0.6, 0.0f };
//GLfloat lp[] = { 1.0f, 0.7f, -0.6f, 0.0f };

GLfloat bianco[]      = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat bluTenue[]    = { 0.1f, 0.1f, 0.3f, 1.0f };

objloader loader;

Character::Character(){};

Character::~Character(){};

void Character::init(){
    this->loadObj = loader.load("/Users/gennaromellone/Downloads/bb8_body2/bb8_body2.obj","/Users/gennaromellone/Downloads/bb8_body2/bb8_body2.mtl");
}

void Character::initialPosition(){
    this->score = ReadHighScore();
    
    this->x = 0.0f;
    this->y = 0.5f;
    this->z = 15.0f;
    this->rotateAngle = 0.0f;
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
    this->x += x;
}

void Character::setY(float y){
    this->y += y;
}

void Character::setZ(float z){
    this->z += z;
}

void Character::setScore(int x){
    this->score = x;
}
int Character::getScore(){
    return this->score;
}

void Character::setLife(int x){
    this->lifes = x;
}

int Character::getLife(){
    return this->lifes;
}

int Character::ReadHighScore() {
    std::ifstream fin("highscore");

    if (!fin.is_open()) {
        std::cout << "Impossibile aprire il file!" << std::endl;
        return -1;
    }

    int score = 0;
    fin >> score;
    fin.close();

    return score;
}

void Character::SaveHighScore(int new_score) {
    if(new_score > this->score){
        std::ofstream myfile;
        myfile.open("highscore");

        if (!myfile.is_open()) {
            std::cout << "Unable to update highscore" << std::endl;
            return;
        }

        myfile << new_score;
        myfile.close();
    }
}

void Character::drawCharacter(){
    this->rotateAngle += 1;
    if(this->rotateAngle > 360.0f)
        this->rotateAngle -= 360.0f;
    
    //glLightfv(GL_LIGHT0,GL_POSITION,lp);
    glPushMatrix();
        glTranslatef(this->x, this->y, this->z);
        glRotatef(this->rotateAngle, -1, 0, 0);
        glLightfv(GL_LIGHT0,GL_POSITION,lp);
        glCallList(this->loadObj);
    glPopMatrix();
    
    
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
}
