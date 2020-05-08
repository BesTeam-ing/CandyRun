//
//  global.h
//  CandyRun
//
//  Created by Ciro De Vita on 07/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#ifndef global_h
#define global_h

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
#define DEF_WINDOW_POS_H 150
#define DEF_WINDOW_POS_W 150

/*  Projection  */
#define DEF_ASP 1
#define DEF_DIM 25
#define DEF_TH 340
#define DEF_PH 30
#define DEF_FOV 25
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

#include <string>

/*  ID-used to keep screencasts separate  */
int screencastID = 0;

/*  WINDOW  */
char *windowName="Candy Run";
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

#endif /* global_h */
