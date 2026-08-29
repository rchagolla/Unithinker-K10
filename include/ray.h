#ifndef RAY_H
#define RAY_H

#include "vector3.h"

class Ray
{
private:
    Vector3 origin;
    Vector3 direction;

public:
    Ray() = delete;
    Ray(Vector3 origin, Vector3 direction);
    Ray clone();
    Vector3 &getOrigin();
    Vector3 &getDirection();
};

#endif