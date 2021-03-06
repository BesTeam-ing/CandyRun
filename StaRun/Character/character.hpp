//
//  character.hpp
//  StaRun
//
//  Created by Ciro De Vita and Gennaro Mellone on 13/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#ifndef character_hpp
#define character_hpp

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <OpenGL/glext.h>

#include <fstream>
#include <cmath>
#include <iostream>

#include "../OBJLoader/objloader.hpp"
#define PI 3.14159265358979324

class Character{
public:
    Character();
    ~Character();
    
    float getX();
    float getY();
    float getZ();
    void setX(float x);
    void setY(float y);
    void setZ(float z);
    
    void setScore(int x);
    void setLife(int x);
    
    int getScore();
    int getLife();
    
    int getBB8score();
    int getD0score();
    int ReadHighScore();
    void SaveHighScore();
    
    void drawCharacter();
    void drawShadow(float R, float X, float Y);
    void initialPosition();
    void init(const char* file_obj_body, const char* file_mtl_body, const char* file_obj_head, const char* file_mtl_head, int value);
private:
    //character position
    float x = 0.0f;
    float y = 0.5f;
    float z = 14.2f;
    //body angle rotation
    float rotateAngle = 0.0f;
    
    //character score
    int score;
    int bb8_score = -1;
    int d0_score = -1;
    
    //character life
    int lifes =3;
    
    int rotate = 0;
    int rotation = 0;
    bool start_curve = true;
    
    //texture pointers
    int body, head;
    
    int character_choosen;
};

#endif /* character_hpp */
