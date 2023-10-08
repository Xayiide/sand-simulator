#include "inc/vec3.hpp"

#include <cmath> /* cos, sin */

Vec3::Vec3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vec3::rotate(float x = 1, float y = 1, float z = 1)
{
    float rad = 0;

    rad = x;
    this->y =  (std::cos(rad) * this->y) - (std::sin(rad) * this->z);
    this->z =  (std::sin(rad) * this->y) + (std::cos(rad) * this->z);

    rad = y;
    this->x =  (std::cos(rad) * this->x) + (std::sin(rad) * this->z);
    this->z = (-std::sin(rad) * this->x) + (std::cos(rad) * this->z);

    rad = z;
    this->x =  (std::cos(rad) * this->x) - (std::sin(rad) * this->y);
    this->y =  (std::sin(rad) * this->x) + (std::cos(rad) * this->y);
}

