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

PRECISION& vec3::operator[](const int index)
{
	return e[index];
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

bool vec3::almost_zero() const
{
	auto s = 1e-8;
	return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
}

vec3 vec3::random()
{
	return vec3(random_double(), random_double(), random_double());
}

vec3 vec3::random(PRECISION in_min, PRECISION in_max)
{
	return vec3(random_double(in_min, in_max), random_double(in_min, in_max), random_double(in_min, in_max));
}

vec3 vec3::random_unit()
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

vec3 vec3::random_in_unit_disk()
{
	while (1)
	{
		vec3 result(random_double(-1, 1), random_double(-1, 1), 0);
		if (result.length_squared() < 1)
		{
			return result;
		}
	}
}

vec3 vec3::reflect(const vec3& v, const vec3& n)
{
	return v - 2 * dot(v, n) * n; 
	// We are projecting V on to N. What does this mean? We are choosing N as our axis, we want to know how much of N is in V. 
	// So essentially, "isolating" the V's components to that of N (?) 
	// Once we know that, we can then multiply N by that much. This then gives us the normal vector by that same length. This is our "b"
}

vec3 vec3::refract(const vec3& uv, const vec3& n, double eta_over_etap)
{
	auto cos_theta = std::fmin(dot(-uv, n), 1.0);
	vec3 r_out_perp = eta_over_etap * (uv + cos_theta * n);
	vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
	return r_out_perp + r_out_parallel;
}