#include "header.h"

SkyBox sky;
WeatherEffects part;
Road road;

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
    if (key == 27)
        exit(0);
    
    /*  Change field of view angle */
    else if (key == '-' && key>1)
        fov--;
    
    else if (key == '+' && key<179)
        fov++;

    redisplayAll();
}

void windowSpecial(int key,int x,int y)
{
    /*  Right/Left - rotate */
    if (key == GLUT_KEY_RIGHT)
        //th += 5;
        ecX += 1.0;
    else if (key == GLUT_KEY_LEFT)
        //th -= 5;
        ecX -= 1.0;
    /*  Up/Down - elevation */
    else if (key == GLUT_KEY_UP)
        ph -= 5;
    else if (key == GLUT_KEY_DOWN)
        ph += 5;
  
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
    
    //double Ex = -2*dim*Sin(th)*Cos(ph);
    //double Ey = +2*dim        *Sin(ph);
    //double Ez = +2*dim*Cos(th)*Cos(ph);
        
    /* camera/eye position, aim of camera lens, up-vector */
    //gluLookAt(Ex+ecX, Ey,Ez+ecZ, ecX,ecY, ecZ, 0, Cos(ph), 0);
    //gluLookAt(Ex+ecX, -1, Ez+ecZ, 10, 5, 10, 0, Cos(ph), 0);
    gluLookAt(ecX, 3.0f, ecZ + 20, ecX + 0.0, 2.0f, 0.0 - 1.0f, 0.0f, 1.0f, 0.0f);

    sky.drawSkyBox(3.5*dim);
    part.drawRain();
    road.draw();
    
    redisplayAll();

    /* Flush, SwapBuffers, and sanity check */
    glFlush();
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    initGlobals();
    
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

    sky.initSkyBox("textures/txStormydays_front.bmp", "textures/txStormydays_right.bmp", "textures/txStormydays_left.bmp", "textures/txStormydays_back.bmp", "textures/txStormydays_up.bmp", "textures/txStormydays_down.bmp");
    part.initParticles();
    road.init("textures/road.jpg");

    glutMainLoop();
    
    return 0;
}

