//
//  Camera.hpp
//  CandyRun
//
//  Created by Ciro De Vita on 13/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#ifndef Camera_h
#define Camera_h

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <OpenGL/glext.h>

#include "Vector3f.h"

#define DEG2RAD(a) (a*0.0174532925)

class Camera
{
public:
    Vector3f eye, center, up;

    Camera(float eyeX = 0.0f, float eyeY = 12.0f, float eyeZ = 260.0f, float centerX = 0.0f, float centerY = 0.0f, float centerZ = 240.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f){
        eye = Vector3f(eyeX, eyeY, eyeZ);
        center = Vector3f(centerX, centerY, centerZ);
        up = Vector3f(upX, upY, upZ);
    }

    void moveX(float d){
        
        Vector3f right = up.cross(center - eye).unit();
        Vector3f r_d = right * d;
        
        eye = eye + r_d;
        center = center + r_d;
    }

    void moveY(float d){
        Vector3f u_d = up.unit() * d;
        eye = eye + u_d;
        center = center + u_d;
    }

    void moveZ(float d){
        Vector3f view = (center - eye).unit();
        Vector3f v_d = view * d;
        
        eye = eye + v_d;
        center = center + v_d;
    }

    void rotateX(float a){
        Vector3f view = (center - eye).unit();
        Vector3f right = up.cross(view).unit();
        Vector3f c1 = view * cos(DEG2RAD(a));
        Vector3f c2 =up * sin(DEG2RAD(a));
        
        view = c1 + c2;
        up = view.cross(right);
        center = eye + view;
    }

    void rotateY(float a){
        Vector3f view = (center - eye).unit();
        Vector3f right = up.cross(view).unit();
        Vector3f c1 = view * cos(DEG2RAD(a));
        Vector3f c2 =right * sin(DEG2RAD(a));
        
        view = c1 + c2;
        right = view.cross(up);
        center = eye + view;
    }

    void look(){
        gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z);
    }
};


#endif /* Camera_h */
