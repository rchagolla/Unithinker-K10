#ifndef SPHERE_H
#define SPHERE_H

#include <tuple>
#include "ray.h"
#include "vector3.h"

class Sphere
{
private:
    Vector3 center = Vector3(0, 0, 0);
    double radius = 1.0;
    Vector3 color = Vector3(1, 1, 1);

public:
    Sphere() = default;
    Sphere(Vector3 center, double radius, Vector3 color = Vector3(1, 1, 1));
    Vector3 getColor();
    std::tuple<bool, Vector3, Vector3, double> raycast(Ray ray);
};

#endif