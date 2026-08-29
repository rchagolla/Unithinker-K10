#include <iostream>
#include "ray.h"

Ray::Ray(Vector3 origin, Vector3 direction)
{
    this->origin = origin.clone();
    this->direction = direction.clone().normalize();
}

Ray Ray::clone()
{
    return Ray(this->origin, this->direction);
}

Vector3 &Ray::getOrigin()
{
    return this->origin;
}

Vector3 &Ray::getDirection()
{
    return this->direction;
}