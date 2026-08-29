#ifndef PLANE_H
#define PLANE_H

#include <tuple>
#include "ray.h"
#include "vector3.h"

class Plane
{
private:
    Vector3 normal = Vector3(0, 1, 0);
    Vector3 validPoint;
    Vector3 color = Vector3(1, 1, 1);

public:
    Plane() = default;
    Plane(Vector3 normal, Vector3 validPoint, Vector3 color);
    std::tuple<bool, Vector3, Vector3, double> raycast(Ray ray);
};

#endif