#include <iostream>

#include "ChapterInterface.h"

int main()
{
	init_chapter();
	std::cin;
	return 0;
}

// Notes:
// - At its core: a raytracer sends rays through each pixels, and computes the color seen in the direction of those rays.
// 1. Calculate the ray from the “eye” through the pixel,
// 2. Determine which objects the ray intersects, and
// 3. Compute a color for the closest intersection point.