//
//  w_effects.hpp
//  CandyRun
//
//  Created by Gennaro Mellone on 08/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#ifndef w_effects_hpp
#define w_effects_hpp


#include <GL/glew.h>
#include <GL/freeglut.h>
#include <OpenGL/glext.h>

#define MAX_PARTICLES 1000
class WeatherEffects{
    
public:
    WeatherEffects();
    
    ~WeatherEffects();
    void initParticles();
    
    void drawRain();
    void drawSnow();
    void drawHail();

    
    
private:
    void init(int i);
    
    typedef struct
    {
      // Life
          bool alive;    // is the particle alive?
          float life;    // particle lifespan
          float fade; // decay
          // color
          float red;
          float green;
          float blue;
          // Position/direction
          float xpos;
          float ypos;
          float zpos;
          // Velocity/Direction, only goes down in y dir
          float vel;
          // Gravity
          float gravity;
    }particles;
    
    particles par_sys[MAX_PARTICLES];
    
    float slowdown = 2.0;
    float velocity = 2.0;
    float zoom = -40.0;
    float pan = 0.0;
    float tilt = 0.0;
    float hailsize = 0.1;
    
    float start_X = -15.0;
    float start_Y = 15.0;
    float start_Z = 40.0;
    float final_Y = 0;
};

#endif /* w_effects_hpp */
