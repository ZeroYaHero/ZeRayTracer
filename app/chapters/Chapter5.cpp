#include "ChapterInterface.h"

#ifdef CHAPTER_5

#include "Color.h"
#include "Ray.h"

bool static hit_sphere(const vec3& center, double radius, const ray& r)
{
	auto unit_d = unit(r.direction());
	auto vector_from_sphere_center = center - r.origin();

	// Equation to calculate if on surface (C - (Q + td)) dot (C - (Q + td)) = r^2
	// Essentially, we can rearrange the equation that determines if a point is on a sphere so that it takes a quadratic form. 
	// If you think about a quadratic equation (a parabola), it can only 0, 1, or 2 roots.
	// This is consistent with a ray going through a sphere, because it can either be at the very edge (1), miss (0), or go through it (2)
	// When we have a quadratic form/equation we can then use it for part of the formula that tells us how many roots there are
	// That is the discriminant: b^2 - 4ac
	auto a = dot(unit_d, unit_d);
	auto b = -2.0 * dot(unit_d, vector_from_sphere_center);
	auto c = dot(vector_from_sphere_center, vector_from_sphere_center) - (radius * radius);

	auto discriminant = (b * b) - (4 * a * c);
	return (discriminant >= 0);
}

static color viewport_camera_ray_color(const ray& ray)
{
	vec3 unit_direction = unit(ray.direction());
	vec3 sphere_center(200.0, 0, 0);
	auto sphere_radius = 50.0;
	if (hit_sphere(sphere_center, sphere_radius, ray))
	{
		return color(1.0, 0.0, 0.0);
	}
	else {
		auto a = 0.5 * (unit_direction.z() + 1.0);
		return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
	}
}

// Sphere calculation:
//	- Formula for a sphere x^2 + y^2 + z^2 = r^2
//	- How I understand this:
//		- If the length of each component added up is the length of the radius, then its on the surface (because regardless of the point on the surface the radius is the same)
//	- If the point is within the sphere, the LHS < r^2, if its outside then the LHS > r^2
//	- If we want the sphere to be at a different point, we need to subtract each component of the spheres origin by these x,y,z...Why?
//		- If you think about it, assuming the origin of the sphere is zero, then we are just getting the distance from the origin.
//		- Now we are doing the same, but subtracting the *new* sphere origin by the point, and this should get us the vector between them. If the vectors length is equal to the radius, then it is on the surface.

int init_chapter()
{
	unsigned char x_aspect = 16;
	unsigned char y_aspect = 9;
	auto aspect_ratio = double(x_aspect) / y_aspect;
	int image_pixel_width = 1280;

	int image_pixel_height = int((double)(image_pixel_width) / x_aspect * y_aspect);
	image_pixel_height = image_pixel_height < 1 ? 1 : image_pixel_height;


	auto viewport_height = 200.0;
	auto viewport_width = viewport_height * (double(image_pixel_width) / image_pixel_height);

	auto focal_length = 100.0;
	vec3 camera_center(0.0);

	auto viewport_u = vec3(0, viewport_width, 0);
	auto viewport_v = vec3(0, 0, -viewport_height);
	auto pixel_delta_u = viewport_u / image_pixel_width;
	auto pixel_delta_v = viewport_v / image_pixel_height;

	auto viewport_upper_left = camera_center - vec3(focal_length, 0, 0) - (viewport_u / 2) - (viewport_v / 2);
	auto pixel_00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

	std::cout << "P3\n" << image_pixel_width << ' ' << image_pixel_height << "\n255\n";
	for (int j = 0; j < image_pixel_height; j++)
	{
		std::clog << "\rCurrent Row: " << j << ", Remaining: " << (image_pixel_height - j) << ' ' << std::flush;
		for (int i = 0; i < image_pixel_width; i++)
		{
			auto pixel_center = pixel_00_loc + (pixel_delta_u * i) + (pixel_delta_v * j);
			auto ray_direction = pixel_center - camera_center;
			ray r(camera_center, ray_direction);
			color pixel_color = viewport_camera_ray_color(r);
			write_color(std::cout, pixel_color);
		}
	}
	std::clog << "\nRender Finished.\n";
	return 0;
}

#endif // CHAPTER_5