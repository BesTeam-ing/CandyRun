//
//  w_effects.cpp
//  CandyRun
//
//  Created by Gennaro Mellone on 08/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#include "w_effects.hpp"

WeatherEffects::WeatherEffects(){};
WeatherEffects::~WeatherEffects(){};

void WeatherEffects::init(int i){
    this->par_sys[i].alive = true;
    this->par_sys[i].life = 1.0;
    this->par_sys[i].fade = float (rand()%100)/1000.0f+0.003f;

    this->par_sys[i].xpos = (float) (rand() % 30) + start_X;
    this->par_sys[i].ypos = start_Y;
    this->par_sys[i].zpos = (float) (rand() % 20) + start_Z;

    this->par_sys[i].red = 0.5;
    this->par_sys[i].green = 0.5;
    this->par_sys[i].blue = 1.0;

    this->par_sys[i].vel = this->velocity;
    this->par_sys[i].gravity = -0.8; //-0.8;
};

void WeatherEffects::initParticles(){
    for (int loop = 0; loop < MAX_PARTICLES; loop++){
        this->init(loop);
    }
};

void WeatherEffects::drawRain(){
    float x, y, z;
    
    for (int loop = 0; loop < MAX_PARTICLES; loop=loop+2) {
        if (this->par_sys[loop].alive == true) {
            x = this->par_sys[loop].xpos;
            y = this->par_sys[loop].ypos;
            z = this->par_sys[loop].zpos + zoom;

          
            glColor3f(0.5, 0.5, 1.0);
            glPushMatrix();
                glBegin(GL_LINES);
                    glVertex3f(x, y, z);
                    glVertex3f(x, y+0.5, z);
                glEnd();
            glPopMatrix();
            
            this->par_sys[loop].ypos += this->par_sys[loop].vel / (slowdown*1000);
            this->par_sys[loop].vel += this->par_sys[loop].gravity;
            this->par_sys[loop].life -= this->par_sys[loop].fade;

            if (this->par_sys[loop].ypos <= final_Y) {
              this->par_sys[loop].life = -1.0;
            }
            
            if (this->par_sys[loop].life < 0.0) {
              this->init(loop);
            }
        }
    }
};

void WeatherEffects::drawSnow(){
    float x, y, z;
    
    for (int loop = 0; loop < MAX_PARTICLES; loop=loop+2) {
        if (par_sys[loop].alive == true) {
            x = par_sys[loop].xpos;
            y = par_sys[loop].ypos;
            z = par_sys[loop].zpos + zoom;

            glColor3f(1.0, 1.0, 1.0);
            glPushMatrix();
                glTranslatef(x, y, z);
                glutSolidSphere(0.2, 16, 16);
            glPopMatrix();

            par_sys[loop].ypos += par_sys[loop].vel / (slowdown*1000);
            par_sys[loop].vel += par_sys[loop].gravity;
            par_sys[loop].life -= par_sys[loop].fade;

            if (par_sys[loop].ypos <= final_Y) {
              par_sys[loop].life = -1.0;
            }

            if (par_sys[loop].life < 0.0) {
              init(loop);
            }
        }
    }
};

void WeatherEffects::drawHail(){
    float x, y, z;

    for (int loop = 0; loop < MAX_PARTICLES; loop=loop+2) {
        if (par_sys[loop].alive == true) {
            x = par_sys[loop].xpos;
            y = par_sys[loop].ypos;
            z = par_sys[loop].zpos + zoom;

            // Draw particles
            glColor3f(0.8, 0.8, 0.9);
            glPushMatrix();
                glBegin(GL_QUADS);
                  // Front
                  glVertex3f(x-hailsize, y-hailsize, z+hailsize); // lower left
                  glVertex3f(x-hailsize, y+hailsize, z+hailsize); // upper left
                  glVertex3f(x+hailsize, y+hailsize, z+hailsize); // upper right
                  glVertex3f(x+hailsize, y-hailsize, z+hailsize); // lower left
                  //Left
                  glVertex3f(x-hailsize, y-hailsize, z+hailsize);
                  glVertex3f(x-hailsize, y-hailsize, z-hailsize);
                  glVertex3f(x-hailsize, y+hailsize, z-hailsize);
                  glVertex3f(x-hailsize, y+hailsize, z+hailsize);
                  // Back
                  glVertex3f(x-hailsize, y-hailsize, z-hailsize);
                  glVertex3f(x-hailsize, y+hailsize, z-hailsize);
                  glVertex3f(x+hailsize, y+hailsize, z-hailsize);
                  glVertex3f(x+hailsize, y-hailsize, z-hailsize);
                  //Right
                  glVertex3f(x+hailsize, y+hailsize, z+hailsize);
                  glVertex3f(x+hailsize, y+hailsize, z-hailsize);
                  glVertex3f(x+hailsize, y-hailsize, z-hailsize);
                  glVertex3f(x+hailsize, y-hailsize, z+hailsize);
                  //Top
                  glVertex3f(x-hailsize, y+hailsize, z+hailsize);
                  glVertex3f(x-hailsize, y+hailsize, z-hailsize);
                  glVertex3f(x+hailsize, y+hailsize, z-hailsize);
                  glVertex3f(x+hailsize, y+hailsize, z+hailsize);
                  //Bottom
                  glVertex3f(x-hailsize, y-hailsize, z+hailsize);
                  glVertex3f(x-hailsize, y-hailsize, z-hailsize);
                  glVertex3f(x+hailsize, y-hailsize, z-hailsize);
                  glVertex3f(x+hailsize, y-hailsize, z+hailsize);
                glEnd();
            glPopMatrix();

            if (par_sys[loop].ypos <= final_Y) {
                par_sys[loop].vel = par_sys[loop].vel * -1.0;
            }
            par_sys[loop].ypos += par_sys[loop].vel / (slowdown*1000); // * 1000
            par_sys[loop].vel += par_sys[loop].gravity;
            par_sys[loop].life -= par_sys[loop].fade;

            if (par_sys[loop].life < 0.0) {
              init(loop);
            }
        }
    }
};
