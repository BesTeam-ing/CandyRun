#include "header.h"

SkyBox sky;
WeatherEffects part;
Road road;
Camera camera = Camera(ecX, 3.0f, ecZ + 20, ecX + 0.0, 2.0f, 0.0 - 1.0f, 0.0f, 1.0f, 0.0f);
Server server;
irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();

GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)DEF_WINDOW_WIDTH / (GLdouble)DEF_WINDOW_HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 700;

void initGlobals(void)
{
    /* WINDOW */
    windowHeight=DEF_WINDOW_HEIGHT;
    windowWidth=DEF_WINDOW_WIDTH;
    windowPosHeight=DEF_WINDOW_POS_H;
    windowPosWidth=DEF_WINDOW_POS_W;

    /* PROJECTION */
    dim=DEF_DIM;
    th=DEF_TH;
    ph=DEF_PH;
    fov=DEF_FOV;
    asp=DEF_ASP;
    ecX=DEF_ECX;
    ecY=DEF_ECY;
    ecZ=DEF_ECZ;
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glutReshapeWindow(1280, 720);
}

void windowKey(unsigned char key,int x,int y)
{
    /*  Exit on ESC */
    if (key == 27){
        engine->drop();
        exit(0);
    }
    
    /*  Change field of view angle */
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

float rotateAngle = 0.0;
float x_sphere = 0.0;

void windowSpecial(int key,int x,int y)
{
    /*  Right/Left - rotate */
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
    /*  Up/Down - elevation */
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
  
    /*  Keep angles at +/- 360 degrees */
    th %= 360;
    ph %= 360;

    redisplayAll();
}

void drawScene()
{
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
    
    /* camera/eye position, aim of camera lens, up-vector */
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

    /* Flush, SwapBuffers, and sanity check */
    glFlush();
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    initGlobals();
    
    engine->play2D("sounds/sound.wav", true);
    
    /* screencast specific variables */
    screencastID = 21;
    
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(windowWidth,windowHeight);
    glutInitWindowPosition(windowPosWidth,windowPosHeight);
    glutCreateWindow(windowName);

    glutDisplayFunc(drawScene);
    glutReshapeFunc(displayReshape);
    glutKeyboardFunc(windowKey);
    glutSpecialFunc(windowSpecial);
    initializeGround();
    
    server.getWeather();
    
    sky.initSkyBox("textures/txStormydays_front.bmp", "textures/txStormydays_right.bmp", "textures/txStormydays_left.bmp", "textures/txStormydays_back.bmp", "textures/txStormydays_up.bmp", "textures/txStormydays_down.bmp");
    
    part.initParticles();
    
    road.init("textures/road.jpg");
    
    glutMainLoop();
    
    return 0;
}
