#include "ChapterInterface.h"

#ifdef CHAPTER_4

#include "Color.h"
#include "Ray.h"

color viewport_camera_ray_color(const ray& ray)
{
	// What is probably going to happen here is we find the intersection points and we get the closest one (as mentioned in bullet points 2 & 3 in notes in Main.cpp).
	vec3 unit_direction = unit(ray.direction());
	auto a = 0.5 * (unit_direction.z() + 1.0); // Again, another difference from the source since we are using UE coordinate system.
	return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0); // Linear scaling (mix/lerp).
}

int init_chapter()
{
	// Have an aspect ratio and a width: and you can calculate the height.
	unsigned char x_aspect = 16;
	unsigned char y_aspect = 9;
	auto aspect_ratio = double(x_aspect) / y_aspect;
	int image_pixel_width = 1280;

	int image_pixel_height = int((double)(image_pixel_width) / x_aspect * y_aspect);
	image_pixel_height = image_pixel_height < 1 ? 1 : image_pixel_height; // Can't have no rows of pixels!

	// Next we need the "viewport camera" center position. Which the textbook refers to as the "eye point"
	// - This is the source where all rays will originate from. 
	// - The vector from the eye point is orthogonal to the plane of the viewport.
	// - The distance between the viewport and the eye point is often referred to as the "focal length"
	// To make sure that our virtual 3d viewport is the same aspect ratio as the result/rendered image:
	// - We have to make sure the source positions for each of the pixels are equally spaced. Distance between two adjacent pixels is called "pixel spacing"
	// - We assume (based on the standard) that pixels are squares.
	// (Viewports will have their *own* measurements for size based on your virtual units, but it should relate to the aspect ratio ofc).

	auto viewport_height = 200.0; // I am going to go with CM units. I like metric, Unreal Engine uses it, and I want to "mimic the real world."

	auto viewport_width = viewport_height * (double(image_pixel_width) / image_pixel_height);
	// ^ The textbook does it this way, which is weird. We just calculated image_pixel_width/pixel_height...thats the aspect ratio!
	//	 auto viewport_width = viewport_height * aspect_ratio; // Alternative
	//	 Though, the textbook talks about how technically that is the ideal aspect ratio...not always perfect given the pixel values and rounding...
	//	 So we use the **IMAGE** aspect ratio for out viewport proportions. 

	auto focal_length = 100.0;
	vec3 camera_center(0.0);

	// In our virtual world our coordinates/directions may not match that of UV (e.g., down in UV may be a different axis/direction in our coordinate)
	// So instead, we simply just define two vectors.
	auto viewport_u = vec3(0, viewport_width, 0);	// One that points from the top left corner to top right.
	auto viewport_v = vec3(0, 0, -viewport_height); // And one that points from the top left corner to the bottom left.
	// These are different from the textbook, since I decided on using UE coordinate system. 
	// These are the vectors we can use to get to any pixel in the viewport, but it comes easier when we get the delta vector for each pixel.

	// These vectors length is equal to the "pixel spacing"
	auto pixel_delta_u = viewport_u / image_pixel_width;
	auto pixel_delta_v = viewport_v / image_pixel_height;

	// Now, the top left corner isn't quite the center/origin of the pixel! It's the corner. 
	// So we just need to calculate the upper left:
	auto viewport_upper_left = camera_center - vec3(focal_length, 0, 0) - (viewport_u / 2) - (viewport_v / 2);
	// Then we calculate the actual position of the pixel (multiply pixel delta by 0.5 to get half delta for center)
	auto pixel_00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v); // Pixel origin position in 3D space!!!

	std::cout << "P3\n" << image_pixel_width << ' ' << image_pixel_height << "\n255\n";
	for (int j = 0; j < image_pixel_height; j++)
	{
		std::clog << "\rCurrent Row: " << j << ", Remaining: " << (image_pixel_height - j) << ' ' << std::flush;
		for (int i = 0; i < image_pixel_width; i++)
		{
			auto pixel_center = pixel_00_loc + (pixel_delta_u * i) + (pixel_delta_v * j);
			auto ray_direction = pixel_center - camera_center;	// With the current camera_center being 0,0,0 this does not really do much.
			ray r(camera_center, ray_direction);				// Ray direction is not normalized, but it doesn't really need to be at this step (micro optimization that actually duplicates call, see viewport_camera_ray_color).
			color pixel_color = viewport_camera_ray_color(r);
			write_color(std::cout, pixel_color);
		}
	}
	std::clog << "\nRender Finished.\n";
	return 0;
}

#endif // CHAPTER_4