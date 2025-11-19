#include "Vec3.h"
#include "Utility.h"

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

PRECISION vec3::dot(const vec3& u, const vec3& v)
{
	return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

vec3 vec3::cross(const vec3& u, const vec3& v)
{
	return vec3(
		(u.e[1] * v.e[2]) - (u.e[2] * v.e[1]),
		(u.e[2] * v.e[0]) - (u.e[0] * v.e[2]),
		(u.e[0] * v.e[1]) - (u.e[1] * v.e[0])
	);
}

vec3 vec3::unit(const vec3& v)
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

vec3 vec3::operator-() const
{
	return {-e[0], -e[1], -e[2]};
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

vec3 vec3::random()
{
	return vec3(random_double(), random_double(), random_double());
}

vec3 vec3::random(PRECISION in_min, PRECISION in_max)
{
	return vec3(random_double(in_min, in_max), random_double(in_min, in_max), random_double(in_min, in_max));
}

vec3 vec3:: random_unit()
{
	while (1)
	{
		vec3 result = random(-1, 1);
		auto length_squared = result.length_squared();
		if (1e-160 < length_squared && length_squared <= 1)
		{
			PRECISION pr = std::sqrt(length_squared);
			return result / std::sqrt(length_squared);
		}
	}
}