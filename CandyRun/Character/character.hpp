//
//  character.hpp
//  CandyRun
//
//  Created by Ciro De Vita on 13/05/2020.
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
    int ReadHighScore();
    void SaveHighScore();
    
    void drawCharacter();
    void drawShadow(float R, float X, float Y, int vert);
    void initialPosition();
    void init();
private:
    float x = 0.0f;
    float y = 0.5f;
    float z = 14.2f;
    float size = 0.5f;
    float rotateAngle = 0.0f;
    
    int score;
    int lifes =3;
    int loadObj;
};

#endif /* character_hpp */
