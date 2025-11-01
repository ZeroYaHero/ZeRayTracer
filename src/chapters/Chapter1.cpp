#include "ChapterInterface.h"

#ifdef CHAPTER_1

#include <iostream>

int init_chapter()
{
	// Image
	int image_width = 256;
	int image_height = 256;

	// Render Text File
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = 0; j < image_height; j++)			// We loop through each row
	{
		std::clog << "\rCurrent: " << j << "\nRemaining: " << (image_height - j) << ' ' << std::flush;
		for (int i = 0; i < image_width; i++)		// So we can write each column of that row first. (Technically Top-Down then Left-Right, but you can think of it as filling row L-R then going T-D).
		{
			auto r = double(i) / (image_width - 1);	// Normalized/saturated 0.0-1.0 scalar for RGB components.
			auto g = double(j) / (image_height - 1);
			auto b = 0.0;

			int ir = int(255.999 * r);				// Scale to 0-255 inclusive
			int ig = int(255.999 * g);
			int ib = int(255.999 * b);

			std::cout << ir << ' ' << ig << ' ' << ib << '\n';
		}
	}
	std::clog << "Render done.\n";
	return 0;
}

#endif // CHAPTER_1