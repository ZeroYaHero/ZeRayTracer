#ifndef COLOR_H
#define COLOR_H

#include "Vec3.h"
#include "Interval.h"

#include <iostream>

using color = vec3; // Typename alias.

static const interval intensity(0.0, 0.999);

// Convert a linear color to gamma corrected
inline double linear_to_gamma(double value, int gamma)
{
	if (value > 0)
	{
		return std::pow(value, 1.0 / gamma);
	}
	return 0;
}

// Convert a gamma color to linear color
inline double gamma_to_linear(double value, int gamma)
{
	if (value > 0)
	{
		return std::pow(value, gamma);
	}
	return 0;
}

// Write a color to the outstream
inline void write_color(std::ostream& out, const color& pixel_color)
{
	auto r = linear_to_gamma(pixel_color.x(), 2);
	auto g = linear_to_gamma(pixel_color.y(), 2);
	auto b = linear_to_gamma(pixel_color.z(), 2);

	// Translate the [0.0-1.0] part into a range of 0-255
	unsigned char rbyte = (unsigned char)(255.999 * intensity.clamp(r)); // At maximum this is 255.999, then truncated which fits in unsigned char.
	unsigned char gbyte = (unsigned char)(255.999 * intensity.clamp(g));
	unsigned char bbyte = (unsigned char)(255.999 * intensity.clamp(b));

	out << int(rbyte) << ' ' << int(gbyte) << ' ' << int(bbyte) << '\n';
}

#ifndef COLOR_CONSTANTS
#define COLOR_CONSTANTS

namespace colors 
{
	const color WHITE(1, 1, 1);
	const color BLACK(0, 0, 0);
	const color RED(1, 0, 0);
	const color GREEN(0, 1, 0);
	const color BLUE(0, 0, 1);
	const color GREY(0.5, 0.5, 0.5);
	const color GRAY(GREY); // Lol this is troll.
}

#endif // COLOR_CONSTANTS

#endif // COLOR_H