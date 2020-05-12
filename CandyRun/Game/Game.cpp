//
//  Game.cpp
//  CandyRun
//
//  Created by Ciro De Vita on 12/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#include "Game.hpp"

#define MAX_PARTICLES 1000

/*  Poor man's approximation of PI */
#define PI 3.1415926535898
/*  Macro for sin & cos in degrees */
#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))
/*  Determine number of elements in an array  */
#define Length(x) (sizeof (x) / sizeof *(x))

/*  Common #defines */
/*  Defaults for window sizing  */
#define DEF_WINDOW_HEIGHT 720
#define DEF_WINDOW_WIDTH 1280
#define DEF_WINDOW_POS_H 50
#define DEF_WINDOW_POS_W 50

/*  Projection  */
#define DEF_ASP 1
#define DEF_DIM 15
#define DEF_TH 340
#define DEF_PH 30
#define DEF_FOV 60
#define DEF_ECX 0
#define DEF_ECY 0
#define DEF_ECZ 0

/*  Draw defaults  */
#define DEF_AXES 1
#define DEF_PARAMS 1
#define DEF_OVERLAY 0

/*  Skybox Textures  */
#define SKY_FRONT 0
#define SKY_RIGHT 1
#define SKY_LEFT 2
#define SKY_BACK 3
#define SKY_UP 4
#define SKY_DOWN 5

/*  WINDOW  */
char const *windowName="Candy Run";
int windowHeight=DEF_WINDOW_HEIGHT;
int windowWidth=DEF_WINDOW_WIDTH;
int windowPosHeight=DEF_WINDOW_POS_H;
int windowPosWidth=DEF_WINDOW_POS_W;

/*  PROJECTION  */
double asp=DEF_ASP;
double dim=DEF_DIM;
int th=DEF_TH;
int ph=DEF_PH;
int fov=DEF_FOV;
double ecX=DEF_ECX;
double ecY=DEF_ECY;
double ecZ=DEF_ECZ;

/*  COLORS  */
float white[]={1,1,1,1};

SkyBox sky;
WeatherEffects part;
Road road;
Camera camera = Camera(ecX, 3.0f, ecZ + 20, ecX + 0.0, 2.0f, 0.0 - 1.0f, 0.0f, 1.0f, 0.0f);
Server server;
irrklang::ISoundEngine* engine;

GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)DEF_WINDOW_WIDTH / (GLdouble)DEF_WINDOW_HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 700;
float rotateAngle = 0.0;
float x_sphere = 0.0;

Game::Game(int argc, char **argv){
    this->argc = argc;
    this->argv = argv;
}

Game::~Game(){};

void Game::init(){    
    engine = irrklang::createIrrKlangDevice();
    
    engine->play2D("sounds/sound.wav", true);
        
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(windowWidth,windowHeight);
    glutInitWindowPosition(windowPosWidth,windowPosHeight);
    glutCreateWindow(windowName);

    glutDisplayFunc(this->drawScene);
    glutReshapeFunc(this->displayReshape);
    glutKeyboardFunc(this->windowKey);
    glutSpecialFunc(this->windowSpecial);
    initializeGround();
    
    //server.getWeather();
    
    sky.initSkyBox("textures/txStormydays_front.bmp", "textures/txStormydays_right.bmp", "textures/txStormydays_left.bmp", "textures/txStormydays_back.bmp", "textures/txStormydays_up.bmp", "textures/txStormydays_down.bmp");
    
    part.initParticles();
    
    road.init("textures/road.jpg");
    
    glutMainLoop();
}

void Game::drawScene(){
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    //gluPerspective(fovy, aspectRatio, zNear, zFar);
    //double Ex = -2*dim*Sin(th)*Cos(ph);
    //double Ey = +2*dim        *Sin(ph);
    //double Ez = +2*dim*Cos(th)*Cos(ph);
    camera.look();
    
    //gluLookAt(Ex+ecX, Ey,Ez+ecZ, ecX,ecY, ecZ, 0, Cos(ph), 0);
    //gluLookAt(Ex+ecX, -1, Ez+ecZ, 10, 5, 10, 0, Cos(ph), 0);
    //gluLookAt(ecX, 3.0f, ecZ + 20, ecX + 0.0, 2.0f, 0.0 - 1.0f, 0.0f, 1.0f, 0.0f);

    sky.drawSkyBox(3.5*dim);
    part.drawRain();
    
    drawRoad(road);
    
    glColor3f(1.0f, 1.0f, 0.0f);
    glPushMatrix();
        glTranslatef(x_sphere, 0.5, 15);
        glRotatef(rotateAngle, -1, 0, 0);
        glutWireSphere(0.5, 20, 20);
    glPopMatrix();
    
    rotateAngle += 1;
    
    redisplayAll();

    glFlush();
    glutSwapBuffers();
}

void Game::windowSpecial(int key,int x,int y){
    if (key == GLUT_KEY_RIGHT){
        //th += 5;
        //ecX += 1.0;
        engine->play2D("sounds/Jump.wav");
        x_sphere+=0.5;
    }
    else if (key == GLUT_KEY_LEFT){
        //th -= 5;
        //ecX -= 1.0;
        engine->play2D("sounds/Jump.wav");
        x_sphere-=0.5;
    }
    else if (key == GLUT_KEY_UP){
        // ph -= 5;
        //camera.moveZ(0.1);
        //glRotatef(90, 0, 90, 0);
        //road.draw();
        //road.setPosition(road.getX(), road.getY(), camera.center.z);
        //camera.rotateY(90);
    }
    
    else if (key == GLUT_KEY_DOWN)
        //ph += 5;
        road.setPosition(road.getX(), road.getY(), road.getZ()+3);
  
    th %= 360;
    ph %= 360;

    redisplayAll();
}

void Game::windowKey(unsigned char key,int x,int y){
    if (key == 27){
        engine->drop();
        exit(0);
    }
    
    //else if (key == '-' && key>1)
    //    fov--;
    
    //else if (key == '+' && key<179)
    //    fov++;
    else if (key == 'p'){ //1st person
        camera.eye.x = 20;
        camera.eye.y = 4;
        camera.eye.z = 249;
        camera.center.x = 20;
        camera.center.y = 0;
        camera.center.z = 220;
        camera.look();
    }
    else if (key == 'o'){ //3st person
        camera.eye.x = 0;
        camera.eye.y = 12;
        camera.eye.z = 260;
        camera.center.x = 0;
        camera.center.y = 0;
        camera.center.z = 240;
        camera.look();
    }
    redisplayAll();
}

/* OpenGL window reshape routine.
void Game::resize(int w, int h){
    glutReshapeWindow(1280, 720);
}
*/

void Game::displayProject(double fov, double asp, double dim){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov,asp,dim/16,16*dim);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Game::displayReshape(int width,int height){
  asp = (height>0) ? (double)width/height : 1;
  glViewport(0,0, width,height);
  displayProject(fov,asp,dim);
}

void Game::redisplayAll(void){
  displayProject(fov,asp,dim);
  glutPostRedisplay();
}

