//
//  Game.hpp
//  CandyRun
//
//  Created by Ciro De Vita on 12/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <OpenGL/glext.h>
#include <SOIL2/SOIL2.h>
#include "irrKlang.h"


#include "../SkyBox/skybox.hpp"
#include "../WeatherEffects/w_effects.hpp"
#include "../Objects/objects.hpp"
#include "../WeatherEffects/Server.hpp"

#include <iostream>
#include <math.h>
#include <string>

using namespace std;

class Game{
public:
    Game(int argc, char **argv);
    ~Game();
    void init();
private:
    int argc;
    char **argv;

    //static void resize(int w, int h);
    static void drawScene();
    static void windowSpecial(int key,int x,int y);
    static void windowKey(unsigned char key,int x,int y);
    static void displayProject(double fov, double asp, double dim);
    static void displayReshape(int width,int height);
    static void redisplayAll(void);
};

#endif /* Game_hpp */
