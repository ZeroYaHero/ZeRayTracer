#ifndef COLOR_H
#define COLOR_H

#include "Vec3.h"

#include <iostream>

using color = vec3; // Typename alias.

inline void write_color(std::ostream& out, const color& pixel_color)
{
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	// Translate the [0.0-1.0] part into a range of 0-255
	unsigned char rbyte = (unsigned char)(255.999 * r); // At maximum this is 255.999, then truncated which fits in unsigned char.
	unsigned char gbyte = (unsigned char)(255.999 * g);
	unsigned char bbyte = (unsigned char)(255.999 * b);

	out << int(rbyte) << ' ' << int(gbyte) << ' ' << int(bbyte) << '\n';
}

#endif // COLOR_H