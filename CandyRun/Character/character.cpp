//
//  character.cpp
//  CandyRun
//
//  Created by Ciro De Vita on 13/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#include "character.hpp"

Character::Character(){};

Character::~Character(){};

void Character::initialPosition(){
    this->x = 0.0f;
    this->y = 0.5f;
    this->z = 15.0f;
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

void Character::drawCharacter(){
    this->rotateAngle += 1;
    
    glColor3f(1.0f, 1.0f, 0.0f);
    glPushMatrix();
        glTranslatef(this->x, this->y, this->z);
        glRotatef(this->rotateAngle, -1, 0, 0);
        glutWireSphere(this->size, 20, 20);
    glPopMatrix();
}
