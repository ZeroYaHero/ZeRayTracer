#include "Ray.h"

const vec3& ray::origin() const
{
	return orig;
}

const vec3& ray::direction() const
{
	return dir;
}

vec3 ray::at(double t) const
{
	return orig + (t * dir);
}