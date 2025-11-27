#ifndef PRECISION
#define PRECISION double
#endif // PRECISION

#ifndef VEC3_H
#define VEC3_H

#include <iostream>

class vec3
{
public:
	// Data
	PRECISION e[3];

	// Initializer list constructors
	vec3() : e{0.0, 0.0, 0.0} {}										// Zero
	vec3(PRECISION e0, PRECISION e1, PRECISION e2) : e{e0, e1, e2} {}	// Trivial
	vec3(PRECISION e012) : e{e012, e012, e012} {}						// Constant

	// Handles
	PRECISION x() const { return e[0]; }
	PRECISION y() const { return e[1]; }
	PRECISION z() const { return e[2]; }

	// Set operator overrides
	// Takes a reference to another vector & operates on the individual elements.
	// Returns a reference to the vector we are operating on (presumably to chain if we wanted to).
	vec3& operator+=(const vec3& v);
	vec3& operator-=(const vec3& v);
	vec3& operator*=(const vec3& v);
	vec3& operator/=(const vec3& v);
	PRECISION& operator[](const int index);

	// Additional unary operator
	vec3 operator-() const;

	// Length
	PRECISION length() const;
	PRECISION length_squared() const;

	// Misc
	bool almost_zero() const;
	// Randomized
	static vec3 random();
	static vec3 random(double in_min, double in_max);
	// Recall: cross product is really only possible in three dimensions.
	// Requires a pair and returns a vector which is perpindicular to both vectors.
	// Order of the pair determines which direction the resulting vector points to (being negatives of each other).
	static vec3 cross(const vec3& u, const vec3& v);
	// Determines how similar two vectors are to eachother.
	// How it works: projects v onto u. Multiplies the length of v with the new projected length.
	// If v is perpindicular, its projected length is 0. So they have low dot product/no similarity.
	// https://youtu.be/LyGKycYT2v0?si=nA5H72voFhLyK_0_&t=104
	static PRECISION dot(const vec3& u, const vec3& v);
	// Unit vector
	static vec3 unit(const vec3& v);
	// Random unit vector
	static vec3 random_unit();
	// Random unit vector within disk
	static vec3 random_in_unit_disk();
	// Reflect vector
	static vec3 reflect(const vec3& v, const vec3& n);
	// Refract vector based on snells law
	static vec3 refract(const vec3& uv, const vec3& n, double eta_over_etap);
};

// Cout
std::ostream& operator<<(std::ostream& out, const vec3& v);

// Binary operators
vec3 operator+(const vec3& u, const vec3& v);
vec3 operator-(const vec3& u, const vec3& v);
vec3 operator*(const vec3& u, const vec3& v);
vec3 operator/(const vec3& u, const vec3& v);
vec3 operator*(const vec3& v, PRECISION t);
vec3 operator*(const PRECISION t, const vec3& v);
vec3 operator/(const vec3& v, PRECISION t);

#endif // VEC3_H