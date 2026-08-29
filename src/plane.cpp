#include <tuple>
#include "plane.h"
#include "vector3.h"
#include "ray.h"

Plane::Plane(Vector3 normal, Vector3 validPoint, Vector3 color)
{
    this->normal = normal.clone().normalize();
    this->validPoint = validPoint.clone();
    this->color = color;
}

std::tuple<bool, Vector3, Vector3, double> Plane::raycast(Ray ray)
{
    double numerator = this->normal.dot(this->validPoint) - this->normal.dot(ray.getOrigin());
    double denominator = this->normal.dot(ray.getDirection());

    double alpha = numerator / denominator;

    if (alpha > 0.0 && this->normal.dot(ray.getDirection()) < 0.0)
    {
        Vector3 hitPoint = ray.getOrigin().clone().add(ray.getDirection().clone().multiplyScalar(alpha));
        return {
            true,
            hitPoint,
            this->normal,
            alpha};
    }
    else
    {
        return {
            false,
            {},
            {},
            0.0};
    }
}