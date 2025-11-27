#ifndef UTILITY
#define UTILITY

#include <cmath>
#include <cstdlib>
#include <limits>
#include <random>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double rads)
{
	return rads * pi / 180.0;
}

inline double random_double()
{
	return std::rand() / (RAND_MAX + 1.0);
}

inline double random_double(double in_min, double in_max)
{
	return in_min + (in_max - in_min) * random_double();
}

// Schlick's approximation
// Formula for approximating the contribution of the "Fresnel Fraction"
inline double reflectance(double cosine, double refraction_index)
{
	auto r0 = (1 - refraction_index) / (1 + refraction_index);
	r0 = r0 * r0;
	return r0 + (1 - r0) * std::pow((1 - cosine), 5);
}

#endif // UTILITY