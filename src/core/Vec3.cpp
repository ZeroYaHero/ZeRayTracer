#include "Vec3.h"

std::ostream& operator<<(std::ostream& out, const vec3& v)
{
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

vec3 operator+(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

vec3 operator-(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

vec3 operator*(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

vec3 operator/(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] / v.e[0], u.e[1] / v.e[1], u.e[2] / v.e[1]);
}

vec3 operator*(const vec3& v, PRECISION t)
{
	return vec3(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}

vec3 operator*(const PRECISION t, const vec3& v)
{
	return vec3(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}

vec3 operator/(const vec3& v, PRECISION t)
{
	return vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

// Determines how similar two vectors are to eachother.
// How it works: projects v onto u. Multiplies the length of v with the new projected length.
// If v is perpindicular, its projected length is 0. So they have low dot product/no similarity.
// https://youtu.be/LyGKycYT2v0?si=nA5H72voFhLyK_0_&t=104
PRECISION dot(const vec3& u, const vec3& v)
{
	return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

// Recall: cross product is really only possible in three dimensions.
// Requires a pair and returns a vector which is perpindicular to both vectors.
// Order of the pair determines which direction the resulting vector points to (being negatives of each other).
vec3 cross(const vec3& u, const vec3& v)
{
	return vec3(
		(u.e[1] * v.e[2]) - (u.e[2] * v.e[1]),
		(u.e[2] * v.e[0]) - (u.e[0] * v.e[2]),
		(u.e[0] * v.e[1]) - (u.e[1] * v.e[0])
	);
}

vec3 unit(const vec3& v)
{
	return v / v.length();
}

vec3& vec3::operator+=(const vec3& v)
{
	e[0] += v.e[0];
	e[1] += v.e[1];
	e[2] += v.e[2];
	return *this; // Recall: references are sugary pointers. This is a pointer, we then derefernce it, but because the return type is a reference it becomes a reference.
}

vec3& vec3::operator-=(const vec3& v)
{
	e[0] -= v.e[0];
	e[1] -= v.e[1];
	e[2] -= v.e[2];
	return *this;
}

vec3& vec3::operator*=(const vec3& v)
{
	e[0] *= v.e[0];
	e[1] *= v.e[1];
	e[2] *= v.e[2];
	return *this;
}

vec3& vec3::operator/=(const vec3& v)
{
	e[0] /= v.e[0];
	e[1] /= v.e[1];
	e[2] /= v.e[2];
	return *this;
}

PRECISION vec3::length() const
{
	return std::sqrt(length_squared());
}

PRECISION vec3::length_squared() const
{
	//return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	return dot(*this, *this); // Length squared is just the dot product of itself
}