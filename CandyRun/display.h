//
//  display.h
//  CandyRun
//
//  Created by Ciro De Vita on 07/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#ifndef display_h
#define display_h

#include "header.h"

/*
 * displayProject()
 * ------
 * Sets the projection
 */
void displayProject(double fov, double asp, double dim)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fov,asp,dim/16,16*dim);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/*
 *  displayReshape()
 *  ------
 *  GLUT calls this routine when the window is resized
 */
void displayReshape(int width,int height)
{
  asp = (height>0) ? (double)width/height : 1;
  glViewport(0,0, width,height);
  displayProject(fov,asp,dim);
}

/*
 *  redisplayAll()
 *  ------
 *  This is called whenever we need to draw the display
 */
void redisplayAll(void)
{
  displayProject(fov,asp,dim);
  glutPostRedisplay();
}



#endif /* display_h */
