//
//  Camera.hpp
//  StaRun
//
//  Created by Ciro De Vita and Gennaro Mellone on 13/05/2020.
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
    //initial camera position
    void init(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ){
        eye = Vector3f(eyeX, eyeY, eyeZ);
        center = Vector3f(centerX, centerY, centerZ);
        up = Vector3f(upX, upY, upZ);
    }
    
    //move camera
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

    //rotate camera
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
    
private:
    Vector3f eye, center, up;
};


#endif /* Camera_h */
