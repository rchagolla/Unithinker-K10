#include <cmath>
#include <iostream>
#include <typeinfo>
#include "vector3.h"

Vector3::Vector3(double x = 0.0, double y = 0.0, double z = 0.0)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

// sets 'this' object's values to those from x, y, and z
Vector3 &Vector3::set(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;

    return *this;
}

// creates a clone of function this is invoked on.
Vector3 Vector3::clone()
{
    return Vector3(this->x, this->y, this->z);
}

// copies the values from other into the vector this is invoked on.
Vector3 &Vector3::copy(Vector3 other)
{

    this->x = other.x;
    this->y = other.y;
    this->z = other.z;

    return *this;
}

// negate all the coordinates of the vector this is invoked on.
Vector3 &Vector3::negate()
{
    this->x *= -1;
    this->y *= -1;
    this->z *= -1;

    return *this;
}

// adds coordinates of "other" to vector this invoked on.
Vector3 &Vector3::add(Vector3 other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;

    return *this;
}

// subtracts coordinates of "other" to vector this invoked on.
Vector3 &Vector3::subtract(Vector3 other)
{
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;

    return *this;
}

// multiplies coordinates of  vector this invoked on with "scalar".
Vector3 &Vector3::multiplyScalar(double scalar)
{
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;

    return *this;
}

// returns the magnitude (A.K.A. length) of vector this is invoked on.
double Vector3::length()
{
    double length;
    length = std::pow(this->x, 2) + std::pow(this->y, 2) + std::pow(this->z, 2);
    length = std::sqrt(length);
    return length;
}

// todo - return the squared magnitude of this vector ||v||^2
double Vector3::lengthSqr()
{
    // There are many occasions where knowing the exact length is unnecessary
    // and the square can be substituted instead (for performance reasons).

    return std::pow(length(), 2);
}

// Changes the components of this vector so that its magnitude will equal 1.
Vector3 &Vector3::normalize()
{
    double currLength = length();
    this->x /= currLength;
    this->y /= currLength;
    this->z /= currLength;
    return *this;
}

// Returns the dot product between this vector and "other"
double Vector3::dot(Vector3 other)
{

    return this->x * other.x + this->y * other.y + this->z * other.z;
    ;
}

// Returns the vector that goes from "fromPoint" to "toPoint"
Vector3 Vector3::fromTo(Vector3 fromPoint, Vector3 toPoint)
{
    double newX = toPoint.x - fromPoint.x;
    double newY = toPoint.y - fromPoint.y;
    double newZ = toPoint.z - fromPoint.z;

    return Vector3(newX, newY, newZ);
}

// Changes this vector's length to be newScale
Vector3 &Vector3::rescale(double newScale)
{
    double newlength = newScale / length();
    this->x *= newlength;
    this->y *= newlength;
    this->z *= newlength;
    return *this;
}

// Calculates the angle in degrees between vectors v1 and v2.
double Vector3::angle(Vector3 v1, Vector3 v2)
{
    double angle = v1.dot(v2);
    angle = angle / (v1.length() * v2.length());

    // result is in radians
    angle = std::acos(angle);

    return angle * (180 / M_PI);
}

/* Returns a vector that points in the same direction as "otherVector"
 * but whose length is the projection of "vectorToProject" onto "otherVector" */
Vector3 Vector3::project(Vector3 vectorToProject, Vector3 otherVector)
{
    Vector3 projectionVector = otherVector.clone();
    double newLength = vectorToProject.dot(otherVector) / otherVector.length();
    projectionVector.rescale(newLength);

    return projectionVector;
}