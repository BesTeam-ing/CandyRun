//
//  character.cpp
//  StaRun
//
//  Created by Ciro De Vita and Gennaro Mellone on 13/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#include "character.hpp"

GLfloat lp[] = { 0.0f, 5.0f, 1.0f, 0.5f }; //light position

//character's number
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
    if(this->x + x < this->x){ //right movement
        this->rotate = 1;
    }
    else{ //left movement
        this->rotate = -1;
    }
    //position control
    if((this->x + x) > 6 || (this->x + x) < -6)
        return;
    else
        this->x += x;
}

//get and set
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

int Character::getD0score(){
    return this->d0_score;
}
int Character::getBB8score(){
    return this->bb8_score;
}

//function to read score from file
int Character::ReadHighScore() {
    std::ifstream fin("Character/highscore.txt"); //open file

    //check errors
    if (!fin.is_open()) {
        std::cout << "Impossibile aprire il file!" << std::endl;
        return -1;
    }
    int i = 0;
    
    std::string str;
    int score[2];
    while (std::getline(fin, str)){ //read from file
        score[i] = std::stoi(str);
        i++;
    }
    
    //set score
    this->bb8_score = score[0];
    this->d0_score = score[1];

    fin.close(); //close file

    return 1;
}

//function to save highscore to file
void Character::SaveHighScore() {
    //check if new score is higher highscore
    if(ReadHighScore() == 1){
        
        if (this->bb8_score < this->score and this->character_choosen == BB8){
            this->bb8_score = this->score;
            
        }
        else if (this->d0_score < this->score and this->character_choosen == D0){
            this->d0_score = this->score;
        }
        
        std::ofstream myfile;
        myfile.open("Character/highscore.txt"); //open file

        //check errors
        if (!myfile.is_open()) {
            std::cout << "Unable to update highscore" << std::endl;
            return;
        }

        myfile << this->bb8_score << std::endl << this->d0_score; //write on file
        myfile.close();
    }
}

//function to draw character
void Character::drawCharacter(){
    //character rotation
    this->rotateAngle += 1;
    if(this->rotateAngle > 360.0f)
        this->rotateAngle -= 360.0f;
    
    //D0
    if(this->character_choosen == D0){
        //body
        glPushMatrix();
            glEnable(GL_LIGHTING);
                glTranslatef(this->x-0.1, this->y, this->z+0.5);
                glRotatef(this->rotation, 0, 0, this->rotate);
                glRotatef(this->rotateAngle, -1, 0, 0);
                glRotatef(90, 0, 1, 0);
                glLightfv(GL_LIGHT0,GL_POSITION,lp);
                glCallList(this->body);
            glDisable(GL_LIGHTING);
        glPopMatrix();
            
        //head
        glPushMatrix();
            glEnable(GL_LIGHTING);
                glTranslatef(this->x-0.1, this->y, this->z+0.5);
                glRotatef(this->rotation, 0, 0, this->rotate);
                glRotatef(180, 0, -1, 0);
                glRotatef(90, 0, -1, 0);
                glRotatef(10, -1, 0, 0);
                glRotatef(10, 1, 0, 0);
                glLightfv(GL_LIGHT0,GL_POSITION,lp);
                glCallList(this->head);
            glDisable(GL_LIGHTING);
        glPopMatrix();
    }
    else if(this->character_choosen == BB8){ //BB8
        //body
        glPushMatrix();
            glEnable(GL_LIGHTING);
                glTranslatef(this->x, this->y, this->z+0.2);
                glRotatef(this->rotation, 0, 0, -this->rotate);
                glLightfv(GL_LIGHT0,GL_POSITION,lp);
                glRotatef(this->rotateAngle, -1, 0, 0);
                glCallList(this->body);
            glDisable(GL_LIGHTING);
        glPopMatrix();
        
        //head
        glPushMatrix();
            glEnable(GL_LIGHTING);
            glTranslatef(this->x, this->y, this->z+0.2);
                //glRotatef(180, 0, -1, 0);
                glRotatef(this->rotation, 0, 0, -this->rotate);
                glRotatef(10, 1, 0, 0);
                glLightfv(GL_LIGHT0,GL_POSITION,lp);
                glCallList(this->head);
            glDisable(GL_LIGHTING);
        glPopMatrix();
    }
    
    if (this->rotate != 0){
        if (this->rotation < 30 and this->start_curve)
            this->rotation += 5;
        else if (this->rotation < 30 and !this->start_curve)
            this->rotation -= 5;
        
        else if(this->rotation == 30){
            this->rotation -= 5;
            this->start_curve = false;
        }
            
        if (this->rotation == 0 and !this->start_curve){
            this->rotation = 0;
            this->rotate = 0;
            this->start_curve = true;
        }
    }
    
    //draw shadow
    glPushMatrix();
        drawShadow(0.5, this->x, this->y);
    glPopMatrix();
}

//function to draw character's shadow
void Character::drawShadow(float R, float X, float Y){
    glColor4f(0.2, 0.2, 0.2, 1.0);
    glRotatef(90, 1, 0, 0);
    GLfloat xOffset = X;
    GLfloat yOffset = this->z +0.6;
    
    //draw circle
    glBegin(GL_POLYGON);
        for(float t = -10 * PI; t <= 10 * PI; t += PI/20.0)
            glVertex3f(xOffset+R * cos(t), yOffset+R * sin(t)/2, -0.001);
    glEnd();
}
