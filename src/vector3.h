// Vector class that holds x, y, and z coordinates and can manipulate them.

#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3
{

public:
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    Vector3() = default;
    Vector3(double x, double y, double z);
    Vector3 &set(double x, double y, double z);
    Vector3 clone();
    Vector3 &copy(Vector3 other);
    Vector3 &negate();
    Vector3 &add(Vector3 other);
    Vector3 &subtract(Vector3 other);
    Vector3 &multiplyScalar(double scalar);
    double length();
    double lengthSqr();
    Vector3 &normalize();
    double dot(Vector3 other);
    Vector3 fromTo(Vector3 fromPoint, Vector3 toPoint);
    Vector3 &rescale(double newScale);
    double angle(Vector3 v1, Vector3 v2);
    Vector3 project(Vector3 vectorToProject, Vector3 otherVector);
};

#endif