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
objloader loader;
Character character;
Menu menu;
irrklang::ISoundEngine* engine;

GLdouble asp;
GLdouble dim = 15.0f;
GLdouble fov = 60.0f;

int loadObj;

bool isStart = false;
bool isPaused = false;

//GLfloat lightPosition[] = { 1.0f, 0.7f, -0.6f, 0.0f };
GLfloat lightPosition[] = { 1.0f, 0.7f, -0.6f, 0.0f };


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
    glClearColor(0.0,0.0,0.0,0.0);
    
    glEnable(GL_LIGHT0);
    
    menu.initMenu();
    
    obj.initObject();

    road.initializeGround();
    
    //server.getWeather();
    
    sky.initSkyBox("textures/txStormydays_front.bmp", "textures/txStormydays_right.bmp", "textures/txStormydays_left.bmp", "textures/txStormydays_back.bmp", "textures/txStormydays_up.bmp", "textures/txStormydays_down.bmp");
    
    part.initParticles();
    glMatrixMode(GL_MODELVIEW);
    
    loadObj = loader.load("textures/bb8.obj","textures/bb8.mtl");
    
    engine = irrklang::createIrrKlangDevice();
    
    //engine->play2D("sounds/sound.wav", true);
    //engine->setSoundVolume(0.3f);
}

void Game::drawGame(){
    if(isPaused){
        //std::cout<<"PAUSED"<<std::endl;
    }
    else{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glLoadIdentity(); //NEW
        glEnable(GL_DEPTH_TEST);
        
        camera.look();
            
        sky.drawSkyBox(9.5*dim);
            
        road.drawRoad();
        
        glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);
        glEnable(GL_LIGHTING);
        
        glPushMatrix();
        glEnable(GL_COLOR_MATERIAL);
            glColor3f(0, 0, 0);
            glTranslatef(0, 2, 10);
            glScalef(0.15, 0.15, 0.15);
            glCallList(loadObj);
        glPopMatrix();
        
        part.drawRain();
        character.drawCharacter();
        obj.drawObject();
        
        if(obj.handleCollision(character.getX(), character.getY(), character.getZ()) == 1)
            gameOver();
        else if(obj.handleCollision(character.getX(), character.getY(), character.getZ()) == 2)
            std::cout<<"Premio +1"<<std::endl;
            
        glDisable(GL_LIGHTING);
    }
}

void Game::drawScene(){
    if(isStart)
        drawGame();
    else
        menu.drawMenu();
    
    redisplayAll();
    
    glFlush();
    glutSwapBuffers();
}

void Game::gameOver(){
    engine->play2D("sounds/game_over.wav");
    obj.initObject();
    character.initialPosition();
    character.SaveHighScore(30);
    std::cout<<"Game Over"<<std::endl;
    isPaused = true;
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
    else{
        std::cout<<"Do nothing"<<std::endl;
    }

    redisplayAll();
}

void Game::windowKey(unsigned char key,int x,int y){
    if (key == 27){
        if(isStart){
            if(isPaused){
                obj.initObject();
                character.initialPosition();
                isStart = false;
                isPaused = false;
            }
        }
        else{
            engine->drop();
            exit(0);
        }
    }
    
    else if(key == 'p' or key == 'P')
        if(isStart)
            isPaused = !isPaused;
    
    redisplayAll();
}

void Game::displayProject(double fov, double asp, double dim){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov,asp,dim/16,16*dim);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutReshapeWindow( DEF_WINDOW_WIDTH, DEF_WINDOW_HEIGHT);
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

void Game::mouseInput(GLint button, GLint state, GLint x, GLint y){
    if(!isStart){
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
            int select = menu.select(x,y);
            
            if(select == 1)
                isStart = true;
            else if(select == 2){
                std::cout<<character.ReadHighScore()<<std::endl;
            }
            else if(select == 3){
                engine->drop();
                exit(0);
            }
        }
    }
}
