//
//  Game.hpp
//  StaRun
//
//  Created by Ciro De Vita and Gennaro Mellone on 12/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <OpenGL/glext.h>
#include <SOIL2/SOIL2.h>
#include <irrklang/irrKlang.h>

#include "../SkyBox/skybox.hpp"
#include "../WeatherEffects/w_effects.hpp"
#include "../Server/Server.hpp"
#include "../Road/Road.hpp"
#include "../Camera/Camera.hpp"
#include "../Objects/objects.hpp"
#include "../Character/character.hpp"
#include "../Menu/menu.hpp"
#include "../GUI/GUI.hpp"

#include <iostream>
#include <math.h>
#include <string>

using namespace std;

class Game{
public:
    Game(int argc, char **argv, const char *windowName);
    ~Game();
    
    void init();
private:
    int argc;
    char **argv;
    const char *windowName;

    static void drawScene();
    
    static void windowSpecial(int key,int x,int y);
    static void windowKey(unsigned char key,int x,int y);
    static void mouseInput(GLint button, GLint state, GLint x, GLint y);
    
    static void displayProject(double fov, double asp, double dim);
    static void displayReshape(int width,int height);
    static void redisplayAll(void);
    
    void initAll();
    
    static void drawGame();
    static void gameOver();
    static int ReadHighScore();
    static void Timer(int value);
    
    static void setFogColor(float r, float g, float b, float a);
    static void setAmbientLight(float r, float g, float b, float a);

};

#endif /* Game_hpp */
