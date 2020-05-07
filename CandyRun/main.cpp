#include "header.h"

// Drawing routine.
void drawScene(void)
{
    // clear (has to be done at the beginning)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    glColor3f(0.0, 255.0, 0.0); //colore

    //disegna un poligono con vertici specificati
    glBegin(GL_POLYGON); //inizio
        glVertex3f(20.0, 20.0, 0.0);
        glVertex3f(80.0, 20.0, 0.0);
        glVertex3f(80.0, 80.0, 0.0);
        glVertex3f(20.0, 80.0, 0.0);
    glEnd();
    
    // swap buffers (has to be done at the end)
    glutSwapBuffers();
}

// Initialization routine.
void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glViewport(0, 0, W, H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, W, 0.0f, H, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glutReshapeWindow(W, H);
}

int main(int argc, char **argv)
{
    // initialize opengl (via glut)
    glutInit(&argc, argv);
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(W, H);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Candy Run");

    // Register callback functions
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);

    setup();

    // start the whole thing
    glutMainLoop();
    return 0;
}

