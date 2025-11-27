#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class ray
{
private:
	vec3 orig;
	vec3 dir;
public:
	// Initializer list constructors
	ray() = default;
	ray(const vec3& orig, const vec3& dir) : orig(orig), dir(dir) {}
	ray(vec3&& orig, vec3&& dir) 
		: orig(std::move(orig)), dir(std::move(dir)) {}
	// Getters
	const vec3& origin() const;		// Here is the magic of C/C++ getters like this. The result is a reference to an object: but it is const. So writing is UB.
	const vec3& direction() const; // <- Const here is unique to C++, and means that this member function WILL NOT WRITE TO ITS DATAMEMBERS. Helps compiler/optimizer. 
	// ^ Const here means the result is a constant (or more accurately IMMUTABLE).
	// Other methods
	vec3 at(double t) const;
};

#endif // RAY_H