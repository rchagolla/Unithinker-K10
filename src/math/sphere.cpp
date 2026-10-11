#include <cmath>
#include <tuple>
#include "sphere.h"
#include "ray.h"

Sphere::Sphere(Vector3 center, double radius, Vector3 color)
{
    this->center = center;
    this->radius = radius;
    this->color = color;
}

Vector3 Sphere::getColor()
{
    return this->color;
}

std::tuple<bool, Vector3, Vector3, double> Sphere::raycast(Ray ray)
{
    std::tuple<bool, Vector3, Vector3, double> result;
    Vector3 rayDirectionClone = ray.getDirection().clone();

    // (origin of ray - center of sphere)
    Vector3 originSubCenter = ray.getOrigin().clone().subtract(this->center);

    // calculating a part of quadratic equation
    double a = rayDirectionClone.dot(rayDirectionClone);

    // calculating b part of quadratic equation
    double b = rayDirectionClone.dot(originSubCenter) * 2;

    // calculating c part of quadratic equation
    double c = originSubCenter.dot(originSubCenter) - std::pow(this->radius, 2);

    // calculating disriminant
    double discriminant = std::pow(b, 2) - (4 * a * c);

    bool invalidIntersections = false;
    if (discriminant >= 0)
    {
        double alpha1 = (-b + std::sqrt(discriminant)) / (2 * a);
        double alpha2 = (-b - std::sqrt(discriminant)) / (2 * a);

        // check if intersections are negative
        if (alpha1 < 0 && alpha2 < 0)
        {
            invalidIntersections = true;
        }
        else if ((alpha1 >= 0 && alpha2 < 0) || (alpha1 < 0 && alpha2 >= 0))
        {
            invalidIntersections = true;
        }
        else
        {
            if (alpha1 > alpha2)
            {
                alpha1 = alpha2;
            }

            Vector3 intersectionPoint = ray.getOrigin().clone().add(ray.getDirection().clone().multiplyScalar(alpha1));
            result = {
                true,                                                         // hit
                intersectionPoint,                                            // point
                intersectionPoint.clone().subtract(this->center).normalize(), // normal
                alpha1                                                        // distance
            };
        }
    }
    else
    {
        result = {
            false, // hit
            {},    // point
            {},    // normal
            0.0,   // distance
        };
    }

    return result;
}