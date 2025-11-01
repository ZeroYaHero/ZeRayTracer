#include "ChapterInterface.h"

#ifdef CHAPTER_3

#include "Vec3.h"
#include "Color.h"

int init_chapter()
{
	// Image
	int image_width = 256;
	int image_height = 256;

	// Render Text File
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = 0; j < image_height; j++)			// We loop through each row
	{
		std::clog << "\rCurrent Row: " << j << ", Remaining: " << (image_height - j) << ' ' << std::flush;
		for (int i = 0; i < image_width; i++)		// So we can write each column of that row first. (Technically Top-Down then Left-Right, but you can think of it as filling row L-R then going T-D).
		{
			auto pixel_color = color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.0);
			write_color(std::cout, pixel_color);
		}
	}
	std::clog << "\nRender Finished.\n";
	return 0;
}

#endif // CHAPTER_3