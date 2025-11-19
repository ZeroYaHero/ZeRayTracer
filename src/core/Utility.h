#ifndef UTILITY
#define UTILITY

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

#endif // UTILITY