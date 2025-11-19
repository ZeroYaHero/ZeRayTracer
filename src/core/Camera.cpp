#include "Camera.h"
#include "Utility.h"

#include <chrono>

void camera::render(const hittable& scene)
{
	auto pixel_samples_scale = 1.0 / samples; // One division and multiple multiplications is better than many repeated divisions. 
	auto start_time = std::chrono::system_clock::now();
	std::cout << "P3\n" << x_pixel_res << ' ' << y_pixel_res << "\n255\n";
	for (int j = 0; j < y_pixel_res; j++)
	{
		std::clog << "\rCurrent Row: " << j << ", Remaining: " << (y_pixel_res - j) << ' ' << std::flush;
		for (int i = 0; i < x_pixel_res; i++)
		{
			color avg_color = color();
			auto pixel_center = pixel_00_loc + (pixel_delta_u * i) + (pixel_delta_v * j);
			for (int k = 0; k < samples; k++)
			{
				auto uv_offset = (pixel_delta_u * (random_double() - 0.5)) + (pixel_delta_v * (random_double() - 0.5));
				auto ray_direction = pixel_center + uv_offset - center;
				ray r(center, ray_direction);
				avg_color += ray_color(r, 0, scene);
			}
			write_color(std::cout, avg_color * pixel_samples_scale);
		}
	}
	std::clog << "\nRender Took " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start_time).count() << " ms\n";
	return;
}

color camera::ray_color(const ray& in_ray, int bounce, const hittable& scene)
{
	if (bounce > max_bounces)
	{
		return color(0, 0, 0);
	}
	hit_payload payload;
	if (scene.hit(in_ray, interval(0.001, infinity), payload)) // Interval for shadow acne due to floating point sometimes being below surface.
	{
		if (vec3::dot(in_ray.direction(), payload.norm) < 0)
		{
			// Admittedly, this switch case for every ray (pixel_count * samples) is not ideal. You would want to have this done way earlier.
			switch (diffuse_render_type)
			{
				// Normal colors
				case DEBUG_NORMAL:
				{
					vec3 vis_norm = vec3(payload.norm.y(), payload.norm.z(), std::abs(payload.norm.x()));
					return 0.5 * (vis_norm + color(1, 1, 1));
				}
				break;
				// Chapter 9 Random Diffuse Reflection
				case RANDOM:
				{
					vec3 random_bounce = vec3::random_unit();
					if (vec3::dot(random_bounce, payload.norm) < 0.0)
					{
						random_bounce = -random_bounce;
					}
					return 0.5 * ray_color(ray(payload.loc, random_bounce), bounce + 1, scene);
				}
					break;
				// Chapter 9 Lambertian Reflection 
				case LAMBERTIAN:
				{
					vec3 dir = payload.norm + vec3::random_unit();
					return 0.5 * ray_color(ray(payload.loc, dir), bounce + 1, scene);
					break;
				}
			}
		}
	}
	vec3 unit_direction = vec3::unit(in_ray.direction());
	auto a = 0.5 * (unit_direction.z() + 1.0);
	return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}