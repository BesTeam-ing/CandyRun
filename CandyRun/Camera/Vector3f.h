//
//  Vector3f.h
//  CandyRun
//
//  Created by Gennaro Mellone on 10/05/2020.
//  Copyright © 2020 BesTeam-ing. All rights reserved.
//

#ifndef Vector3f_h
#define Vector3f_h

class Vector3f
{
public:
    float x, y, z;

    Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f){
        x = _x;
        y = _y;
        z = _z;
    }

    Vector3f operator+(Vector3f &v){
        return Vector3f(x + v.x, y + v.y, z + v.z);
    }

    Vector3f operator-(Vector3f &v){
        return Vector3f(x - v.x, y - v.y, z - v.z);
    }

    Vector3f operator*(float n){
        return Vector3f(x * n, y * n, z * n);
    }

    Vector3f operator/(float n){
        return Vector3f(x / n, y / n, z / n);
    }

    Vector3f unit(){
        return *this / sqrt(x * x + y * y + z * z);
    }

    Vector3f cross(Vector3f v){
        return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }
};
#endif /* Vector3f_h */
