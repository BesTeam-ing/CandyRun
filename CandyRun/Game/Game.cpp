//
//  Game.cpp
//  CandyRun
//
//  Created by Ciro De Vita on 12/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#include "Game.hpp"

#define DEF_WINDOW_HEIGHT 720
#define DEF_WINDOW_WIDTH 1280
#define DEF_WINDOW_POS_H 50
#define DEF_WINDOW_POS_W 50

SkyBox sky;
WeatherEffects part;
Camera camera = Camera(0.0f, 3.0f, 20.0f, 0.0, 2.0f, -1.0f, 0.0f, 1.0f, 0.0f);
Server server;
Road road;
Object obj;
Character character;
Menu menu;
irrklang::ISoundEngine* engine;

GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)DEF_WINDOW_WIDTH / (GLdouble)DEF_WINDOW_HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 700;
double asp;
double dim = 15;
double fov = 60;

bool isStart = false;

Game::Game(int argc, char **argv, const char *name){
    this->argc = argc;
    this->argv = argv;
    this->windowName = name;
}

Game::~Game(){};

void Game::init(){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(DEF_WINDOW_WIDTH, DEF_WINDOW_HEIGHT);
    glutInitWindowPosition(DEF_WINDOW_POS_W, DEF_WINDOW_POS_H);
    glutCreateWindow(this->windowName);

    glutDisplayFunc(this->drawScene);
    glutReshapeFunc(this->displayReshape);
    glutKeyboardFunc(this->windowKey);
    glutSpecialFunc(this->windowSpecial);
    glutMouseFunc(this->mouseInput);
    
    this->initAll();
        
    glutMainLoop();
}

void Game::initAll(){
    obj.initObject();
    
    road.initializeGround();
    
    //server.getWeather();
    
    sky.initSkyBox("textures/txStormydays_front.bmp", "textures/txStormydays_right.bmp", "textures/txStormydays_left.bmp", "textures/txStormydays_back.bmp", "textures/txStormydays_up.bmp", "textures/txStormydays_down.bmp");
    
    part.initParticles();
    
    engine = irrklang::createIrrKlangDevice();
    
    //engine->play2D("sounds/sound.wav", true);
    //engine->setSoundVolume(0.3f);
}

void Game::drawScene(){
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    
    if(isStart){
        camera.look();
        
        sky.drawSkyBox(3.5*dim);
        
        part.drawRain();
        
        road.drawRoad();
        
        character.drawCharacter();
        
        obj.drawObject();
        obj.handleCollision(character.getX(), character.getY(), character.getZ());
    }
    else{
        menu.initMenu();
        
        menu.drawMenu();
    }
    
    redisplayAll();
    
    glFlush();
    glutSwapBuffers();
}

void Game::windowSpecial(int key,int x,int y){
    if(isStart){
        if (key == GLUT_KEY_RIGHT){
            engine->play2D("sounds/Jump.wav");
            character.setX(0.5);
        }
        else if (key == GLUT_KEY_LEFT){
            engine->play2D("sounds/Jump.wav");
            character.setX(-0.5);
        }
    }

    redisplayAll();
}

void Game::windowKey(unsigned char key,int x,int y){
    if (key == 27){
        engine->drop();
        exit(0);
    }
    else if(key == 'R'){
        if(isStart)
            isStart = false;
        else{
            isStart = true;
        }
    }
    
    redisplayAll();
}

void Game::displayProject(double fov, double asp, double dim){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov,asp,dim/16,16*dim);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Game::displayReshape(int width,int height){
    asp = (height>0) ? (double)width/height : 1;
    glViewport(0,0, width, height);
    displayProject(fov, asp, dim);
}

void Game::redisplayAll(void){
    displayProject(fov, asp, dim);
    glutPostRedisplay();
}

void Game::mouseInput(GLint button, GLint state, GLint x, GLint y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        std::cout<<x<<" "<<y<<std::endl;
    }
}
