//
//  Game.cpp
//  StaRun
//
//  Created by Ciro De Vita and Gennaro Mellone on 12/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#include "Game.hpp"

#define DEF_WINDOW_HEIGHT 720
#define DEF_WINDOW_WIDTH 1280
#define DEF_WINDOW_POS_H 50
#define DEF_WINDOW_POS_W 50

//Istance objects from all classes
SkyBox sky;
WeatherEffects part;
Camera camera;
Road road;
Object obj;
Character character;
Menu menu;
GUI gui;
irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();;

//Camera settings
GLdouble asp;
GLdouble dim = 15.0f;
GLdouble fov = 60.0f;

//InGame boolean variables
bool isStart = false;
bool isPaused = false;
bool isAudio = true;
bool isGameOver = false;
bool isDay = true;

//FOG Settings
static bool isFog = true ; // Is fog on?
static int fogMode = GL_EXP2; // Fog mode.
static float fogDensity = 0.005; // Fog density.
static float fogStart = -70; // Fog start z value.
static float fogEnd = 30; // Fog end z value.
float fogColor[4] = {0.6, 0.6, 0.6, 1.0};
float ambientLight[4] = {0.1, 0.1, 0.1, 1.0};

//Weather type
enum weather{
    CLEAR,
    RAIN,
    SNOW
};
int weather_condition = CLEAR; //Default weather condition

//GUI Strings
char* score;
char* vite;

//Speed settings
float update = 0.2;
float speed = 0.2;

//Background settings
int background_chosen = 0;

//Game constructor
Game::Game(int argc, char **argv, const char *name){
    this->argc = argc;
    this->argv = argv;
    this->windowName = name;
}

Game::~Game(){};

//Function used to manage speed game
void Game::Timer(int value)
{
    if(isStart && !isPaused){
        if(update <= 1.5){
            if(10%(int(update*10)) == 0){
                speed = update;
            }
        }
        else
            return;
        
        update += 0.1;
        glutPostRedisplay();
    }
    glutTimerFunc(10000, Timer, 0);
}

//Overall game initialization
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
        
    this->Timer(0);
    
    glutMainLoop();
}

//Object and environment initialization
void Game::initAll(){
    glClearColor(0.0,0.0,0.0,0.0);
    
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHT0); //General Light
    glEnable(GL_LIGHT2); //Left Lamps Light
    glEnable(GL_LIGHT3); //Right Lamps Light
    
    camera.init(0.0f, 3.0f, 20.0f, 0.0, 2.0f, -1.0f, 0.0f, 1.0f, 0.0f); //Camera initialization
    
    menu.initMenu(); //Menu initialization
        
    //Load objects (WALL, BATTERY e LAMP)
    obj.load();
    obj.initObject();
    
    //Load Road and initialize it
    road.load();
    road.initializeGround();
    
    //Start music
    engine->play2D("sounds/starwars.wav", true);
}

//Main drawGame function
void Game::drawGame(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(0.0,0.0,0.0,1.0);
    glLoadIdentity();
    
    //Set camera position
    camera.look();
    
    //Draw Skybox
    sky.drawSkyBox(9.5*dim);
    
    //Check game status
    if(isPaused){//If it is paused
        glDisable(GL_LIGHTING);
        glDisable(GL_FOG);
        
        const char* text;
        const char* text_resume;
        const char* text_esc;
        int x, x1;
        
        if(isGameOver){ //If it is GameOver
            text = "GAME OVER";
            text_resume = "PRESS 'P' TO RESTART";
            text_esc = "PRESS 'ESC' TO QUIT";
            x = -20;
            x1 = -15;
        }
            
        else{//Or it is Pause
            text = "PAUSE";
            text_resume = "PRESS 'P' TO RESUME";
            text_esc = "PRESS 'ESC' TO QUIT";
            x = -10;
            x1 = -15;
        }
        
        //Show text PAUSE
        glPushMatrix();
            glColor4f(1.0, 1.0, 1.0, 0.0);
            glTranslatef(x, 3, 0);
            glScalef(0.05,0.05,0.05);
        
            for( const char* p = text; *p; p++){
                glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
            }
        glPopMatrix();
        
        //Show text RESUME
        glPushMatrix();
            glColor4f(1.0, 1.0, 1.0, 0.0);
            glTranslatef(x1, -2, 0);
            glScalef(0.02,0.02,0.02);
        
            for( const char* p = text_resume; *p; p++){
                glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
            }
        glPopMatrix();
        
        //Show text EXIT
        glPushMatrix();
            glColor4f(1.0, 1.0, 1.0, 0.0);
            glTranslatef(x1, -7, 0);
            glScalef(0.02,0.02,0.02);
        
            for( const char* p = text_esc; *p; p++){
                glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
            }
        glPopMatrix();
    }
    else{
        isGameOver = false;
                
        //Set weather condition
        switch (weather_condition) {
            case CLEAR:
                break;
            case RAIN:
                part.drawRain();
                break;
            case SNOW:
                part.drawSnow();
                break;
            default:
                break;
        }
        
        glEnable(GL_LIGHTING);
        
        //Check FOG
        if(isFog){
            glEnable(GL_FOG);
            glFogfv(GL_FOG_COLOR, fogColor);
            glFogi(GL_FOG_MODE, fogMode);
            glFogf(GL_FOG_START, fogStart);
            glFogf(GL_FOG_END, fogEnd);
            glFogf(GL_FOG_DENSITY, fogDensity);
            glHint(GL_FOG_HINT, GL_NICEST);
        }
        else{
            glDisable(GL_FOG);
        }

        //Draw Road
        road.drawRoad(speed);
        
        //Draw GUI (Lifes and Points)
        gui.draw(character.getScore(), character.getLife());
        
        //Draw character
        character.drawCharacter();
    
        //Draw objects
        obj.drawObject(speed, character.getX());
        
        //Manage Collisions
        if(obj.handleCollision(character.getX(), character.getY(), character.getZ()) == 1){
            engine->play2D("sounds/impact.wav", false); //If hit a WALL
            character.setLife(-1); //Lose a life
            
            if(character.getLife() == 0)
                gameOver();
        }
        else if(obj.handleCollision(character.getX(), character.getY(), character.getZ()) == 2){
            character.setScore(10); //If hit a BATTERY
            engine->play2D("sounds/score.wav", false);
        }
    }
    
    glFlush();
    glutSwapBuffers();
}

//Function to manage scene
void Game::drawScene(){
    if(isStart) //If game is started
        drawGame(); //Show game
    
    else //Else if we are in main menu
        menu.drawMenu(); //Show main menu
    
    redisplayAll();
}
//GameOver function
void Game::gameOver(){
    engine->play2D("sounds/screaming.wav", false);
    
    //Restore default settings
    obj.initObject();
    character.SaveHighScore();
    character.initialPosition();
    road.initializeGround();
    isPaused = true;
    isGameOver = true;
    speed = 0.2;
    update = 0.2;
}

//Main function to handle mouse input
void Game::mouseInput(GLint button, GLint state, GLint x, GLint y){

    if(!isStart){//If we are in Main Menu
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
            int select = menu.select(x,y);
            
            if(select == 1){ //We select START GAME
                isStart = true;
                engine->stopAllSounds();
                
                part.initParticles(); //Intialize particles (Rain and Snow)
                
// SKYBOXES SELECTION
                switch (menu.getBackground()) {
                    case 0: //DAY SUNNY
                        
                        //Load textures
                        sky.initSkyBox("textures/sky191ft.bmp", "textures/sky191rt.bmp", "textures/sky191lf.bmp", "textures/sky191bk.bmp", "textures/sky191up.bmp", "textures/sky191dn.bmp");
                        
                        //Set variables
                        isDay = true;
                        weather_condition = CLEAR;
                        
                        //Set fog
                        fogDensity = 0.005;
                        setFogColor(0.7, 0.7, 0.7, 1.0);
                        
                        //Set Lights
                        glDisable(GL_LIGHT2);
                        glDisable(GL_LIGHT3);
                        setAmbientLight(0.4, 0.4, 0.4, 1.0);
                        glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
                        
                        break;
                    
                    case 1: //DAY SNOW
                        
                        //Load textures
                        sky.initSkyBox("textures/sky303ft.bmp", "textures/sky303rt.bmp", "textures/sky303lf.bmp", "textures/sky303bk.bmp", "textures/sky303up.bmp", "textures/sky303dn.bmp");
                        
                        //Set variables
                        weather_condition = RAIN;
                        isDay = true;
                        
                        //Set fog
                        fogDensity = 0.01;
                        setFogColor(0.6, 0.6, 0.6, 1.0);
                        
                        //Set Lights
                        glDisable(GL_LIGHT2);
                        glDisable(GL_LIGHT3);
                        setAmbientLight(0.2, 0.2, 0.2, 1.0);
                        glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
                        
                        break;
                        
                    case 2: //DAY SNOW
                        //Load textures
                        sky.initSkyBox("textures/sky303ft.bmp", "textures/sky303rt.bmp", "textures/sky303lf.bmp", "textures/sky303bk.bmp", "textures/sky303up.bmp", "textures/sky303dn.bmp");
                        
                        //Set variables
                        weather_condition = SNOW;
                        isDay = true;
                        
                        //Set fog
                        fogDensity = 0.015;
                        setFogColor(0.6, 0.6, 0.6, 1.0);
                        
                        //Set Lights
                        glDisable(GL_LIGHT2);
                        glDisable(GL_LIGHT3);
                        setAmbientLight(0.2, 0.2, 0.2, 1.0);
                        glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
                        
                        break;
                    
                    case 4: //MARS
                        
                        //Load textures
                        sky.initSkyBox("textures/pinkft.bmp", "textures/pinkrt.bmp", "textures/pinklf.bmp", "textures/pinkbk.bmp", "textures/pinkup.bmp", "textures/pinkdn.bmp");
                        
                        //Set variables
                        weather_condition = CLEAR;
                        isDay = true;
                        
                        //Set fog
                        fogDensity = 0.005;
                        setFogColor(0.6, 0.3, 0.3, 1.0);
                        
                        //Set Lights
                        glDisable(GL_LIGHT2);
                        glDisable(GL_LIGHT3);
                        setAmbientLight(0.5, 0.3, 0.3, 1.0);
                        glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
                        
                        break;
                        
                    case 5: //SPACE
                        
                        //Load textures
                        sky.initSkyBox("textures/spaceft.bmp", "textures/spacert.bmp", "textures/spacelf.bmp", "textures/spacebk.bmp", "textures/spaceup.bmp", "textures/spacedn.bmp");
                        
                        //Set variables
                        weather_condition = CLEAR;
                        isDay = false;
                        
                        //Set fog
                        fogDensity = 0.002;
                        setFogColor(0.3, 0.3, 0.3, 1.0);
                        
                        //Set Lights
                        glDisable(GL_LIGHT2);
                        glDisable(GL_LIGHT3);
                        setAmbientLight(0.15, 0.15, 0.15, 1.0);
                        glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
                        
                        break;
                        
                    case 6: //NIGHT CLEAR
                        
                        //Load textures
                        sky.initSkyBox("textures/skyft.bmp", "textures/skyrt.bmp", "textures/skylf.bmp", "textures/skybk.bmp", "textures/skyup.bmp", "textures/skydn.bmp");
                        
                        //Set variables
                        weather_condition = CLEAR;
                        isDay = false;
                        
                        //Set fog
                        fogDensity = 0.005;
                        setFogColor(0.3, 0.3, 0.3, 1.0);
                        
                        //Set Lights
                        setAmbientLight(0.4, 0.4, 0.2, 1.0);
                        glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
                        
                        break;
                        
                    case 7: //NIGHT RAIN
                        
                        //Load textures
                        sky.initSkyBox("textures/skyft.bmp", "textures/skyrt.bmp", "textures/skylf.bmp", "textures/skybk.bmp", "textures/skyup.bmp", "textures/skydn.bmp");
                        //Set variables
                        weather_condition = RAIN;
                        isDay = false;
                        
                        //Set fog
                        fogDensity = 0.03;
                        setFogColor(0.4, 0.4, 0.3, 1.0);
                        
                        //Set Lights
                        setAmbientLight(0.4, 0.4, 0.2, 1.0);
                        glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
                        
                        break;
                        
                    case 8: //NIGHT SNOW
                        
                        //Load textures
                        sky.initSkyBox("textures/skyft.bmp", "textures/skyrt.bmp", "textures/skylf.bmp", "textures/skybk.bmp", "textures/skyup.bmp", "textures/skydn.bmp");
                        //Set variables
                        weather_condition = SNOW;
                        isDay = false;
                        
                        //Set fog
                        fogDensity = 0.03;
                        setFogColor(0.4, 0.4, 0.3, 1.0);
                        
                        //Set Lights
                        setAmbientLight(0.4, 0.4, 0.2, 1.0);
                        glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
                        
                        break;
                        
                    default: //DAY SUNNY
                        
                        //Load textures
                        sky.initSkyBox("textures/txStormydays_front.bmp", "textures/txStormydays_right.bmp", "textures/txStormydays_left.bmp", "textures/txStormydays_back.bmp", "textures/txStormydays_up.bmp", "textures/txStormydays_down.bmp");
                        
                        //Set variables
                        weather_condition = CLEAR;
                        
                        //Set fog
                        fogDensity = 0.005;
                        setFogColor(0.7, 0.7, 0.7, 1.0);
                        
                        //Set Lights
                        glDisable(GL_LIGHT2);
                        glDisable(GL_LIGHT3);
                        setAmbientLight(0.2, 0.2, 0.2, 1.0);
                        glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
                }
                
//CHARACTER SELECTION
                switch (menu.getCharacter()) {
                    case 0: //BB8
                        character.init("textures/bb8_body.obj","textures/bb8_body.mtl", "textures/bb8_head.obj", "textures/bb8_head.mtl", 0);
                        break;
                    case 1: //D0
                        character.init("textures/d0_body.obj","textures/d0_body.mtl", "textures/d0_head.obj", "textures/d0_head.mtl", 1);
                        break;
                        
                    default: //Default is BB8
                        character.init("textures/bb8_body.obj","textures/bb8_body.mtl", "textures/bb8_head.obj", "textures/bb8_head.mtl", 0);
                        break;
                }
            }
            
            //Exit Game
            else if(select == 3){
                engine->drop();
                exit(0);
            }
        }
    }
}

//Special keys function
void Game::windowSpecial(int key,int x,int y){

    if(isStart && !isPaused){ //If we are in Game Window
        
        if (key == GLUT_KEY_RIGHT){
            if(isAudio) //If audio is enabled
                engine->play2D("sounds/bb8-05.wav", false);
            
            character.setX(1); //Move Right
        }
        else if (key == GLUT_KEY_LEFT){
            if(isAudio) //If audio is enabled
                engine->play2D("sounds/bb8-05.wav", false);
            
            character.setX(-1); //Move Left
        }
    }

    redisplayAll();
}

//Keys function
void Game::windowKey(unsigned char key,int x,int y){

    if (key == 27){ //ESC
        if(isStart){ //If we are in game
            if(isPaused){ //If game is paused
                
                //Return to main menu and set variables to default
                engine->play2D("sounds/starwars.wav", true);
                obj.initObject();
                character.initialPosition();
                road.initializeGround();
                isStart = false;
                isPaused = false;
                speed = 0.2;
                update = 0.2;
            }
        }
        else{ //Else quit game
            engine->drop();
            exit(0);
        }
    }
    
    //PAUSE or RESUME
    else if(key == 'p' or key == 'P'){
        if(isStart)
            isPaused = !isPaused;
    }
    
    // MUTE ON or OFF
    else if(key == 'm' or key == 'M'){
        if(isAudio){
            engine->setSoundVolume(0.0f);
            isAudio = false;
        }
        else{
            engine->setSoundVolume(0.3f);
            isAudio = true;
        }
    }
    
    redisplayAll();
}
//Default displayProject function
void Game::displayProject(double fov, double asp, double dim){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov,asp,dim/16,16*dim);
    glMatrixMode(GL_MODELVIEW);
    glutReshapeWindow( DEF_WINDOW_WIDTH, DEF_WINDOW_HEIGHT);
}

//Function to manage screen size
void Game::displayReshape(int width,int height){
    asp = (height>0) ? (double)width/height : 1;
    glutReshapeWindow( DEF_WINDOW_WIDTH, DEF_WINDOW_HEIGHT);
    displayProject(fov, asp, dim);
}

// Function to redisplay all
void Game::redisplayAll(void){
    displayProject(fov, asp, dim);
    glutPostRedisplay();
}

//Set the fog color
void Game::setFogColor(float r, float g, float b, float a){
    fogColor[0] = r;
    fogColor[1] = g;
    fogColor[2] = b;
    fogColor[3] = a;
}

//Set the ambient light color
void Game::setAmbientLight(float r, float g, float b, float a){
    ambientLight[0] = r;
    ambientLight[1] = g;
    ambientLight[2] = b;
    ambientLight[3] = a;
}
