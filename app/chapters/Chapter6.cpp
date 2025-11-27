#include "ChapterInterface.h"

#ifdef CHAPTER_6

#include "Color.h"
#include "Ray.h"
#include "Sphere.h"
#include "HittableList.h"
#include "HitPayload.h"
#include "Utility.h"

#include <memory>

// Deprecated for chapters onwards
double hit_sphere(const vec3& center, double radius, const ray& r)
{

	auto oc = center - r.origin();
	auto a = dot(r.direction(), r.direction());
	auto b = -2.0 * dot(r.direction(), oc);
	//auto b = dot(r.direction(), oc); // Can simplify by cancelling the 2
	auto c = dot(oc, oc) - (radius * radius);
	auto discriminant = (b * b) - (4 * a * c);

	if (discriminant < 0)
	{
		return -1.0;
	}
	else
	{
		return (-b - std::sqrt(discriminant)) / (2.0 * a); // ^
		//return (-b - std::sqrt(discriminant)) / a;
	}
}

color ray_color(const ray& ray, const hittable& world)
{
	//vec3 sphere_center(200.0, 0, 0);
	//auto sphere_radius = 100.0;
	//auto t = hit_sphere(sphere_center, sphere_radius, ray);
	//if (t > 0.0)
	//{
	//	vec3 unit_outward_normal_vector = unit(ray.at(t) - sphere_center); // Inward would be the opposite... Remember (destination - source)
	//	//std::clog << "Outward Normal Vector X Component: " << unit_outward_normal_vector.x() << std::flush;
	//	//return 0.5 * color(unit_outward_normal_vector.y() + 1, unit_outward_normal_vector.z() + 1, unit_outward_normal_vector.x() + 1); // Think: -1 to 1...add 1 = 0 to 2...Multiply by 0.5 = 0 to 1
	//	return 0.5 * color(unit_outward_normal_vector.y() + 1, unit_outward_normal_vector.z() + 1, -unit_outward_normal_vector.x() + 1); // Just make this ABS. I realized that because we are now facing in the positive X direction the outward normals are technically negative.
	//	// This was a pain in the ass. To get the proper coloring I needed to just change the coordinates for the proper directions. I guess I now see the benefit for why they used the method they do lol.
	//	// ^ This might need to be changed because of different coordinate system. 
	//	//return color(1.0, 0.0, 0.0);
	//}
	hit_payload payload;
	if (world.hit(ray, interval(0, infinity), payload))
	{
		//if()
		if (dot(ray.direction(), payload.norm) < 0)
		{
			vec3 vis_norm = vec3(payload.norm.y(), payload.norm.z(), std::abs(payload.norm.x()));
			color temp = 0.5 * (vis_norm + color(1, 1, 1));
			return temp;
		}
	}
	vec3 unit_direction = unit(ray.direction());
	auto a = 0.5 * (unit_direction.z() + 1.0);
	return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int init_chapter()
{
	unsigned char x_aspect = 16;
	unsigned char y_aspect = 9;
	auto aspect_ratio = double(x_aspect) / y_aspect;
	int image_pixel_width = 1280;

	int image_pixel_height = int((double)(image_pixel_width) / x_aspect * y_aspect);
	image_pixel_height = image_pixel_height < 1 ? 1 : image_pixel_height;

	// World

	hittable_list world;

	world.add(std::make_shared<sphere>(vec3(200.0, 0, 0), 100.0));
	world.add(std::make_shared<sphere>(vec3(0, 0, -20100.0), 20000.0));

	auto viewport_height = 200.0;
	auto viewport_width = viewport_height * (double(image_pixel_width) / image_pixel_height);

	auto focal_length = 100.0;
	vec3 camera_center(0.0);

	auto viewport_u = vec3(0, viewport_width, 0);
	auto viewport_v = vec3(0, 0, -viewport_height);
	auto pixel_delta_u = viewport_u / image_pixel_width;
	auto pixel_delta_v = viewport_v / image_pixel_height;

	auto viewport_upper_left = camera_center + vec3(focal_length, 0, 0) - (viewport_u / 2) - (viewport_v / 2);
	auto pixel_00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v); // HUGE issue that I noticed I had in Chapters

	std::cout << "P3\n" << image_pixel_width << ' ' << image_pixel_height << "\n255\n";
	for (int j = 0; j < image_pixel_height; j++)
	{
		std::clog << "\rCurrent Row: " << j << ", Remaining: " << (image_pixel_height - j) << ' ' << std::flush;
		for (int i = 0; i < image_pixel_width; i++)
		{
			auto pixel_center = pixel_00_loc + (pixel_delta_u * i) + (pixel_delta_v * j);
			auto ray_direction = pixel_center - camera_center;
			ray r(camera_center, ray_direction);
			color pixel_color = ray_color(r, world);
			write_color(std::cout, pixel_color);
		}
	}
	std::clog << "\nRender Finished.\n";
	return 0;
}

#endif // CHAPTER_6