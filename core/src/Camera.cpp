#include "Camera.h"
#include "Utility.h"
#include "Material.h"
#include "Ray.h"

#include <chrono>
#include <thread>
#include <vector>

void camera::render_section(const hittable& scene, std::vector<std::vector<color>>& image, int x_start, int y_start, int x_end, int y_end)
{
	auto pixel_samples_scale = 1.0 / samples; // One division and multiple multiplications is better than many repeated divisions. 
	for (int j = y_start; j < y_end; j++)
	{
		for (int i = x_start; i < x_end; i++)
		{
			color avg_color = color();
			auto pixel_center = pixel_00_loc + (pixel_delta_u * i) + (pixel_delta_v * j);
			for (int k = 0; k < samples; k++)
			{
				auto uv_offset = (pixel_delta_u * (random_double() - 0.5)) + (pixel_delta_v * (random_double() - 0.5));
				auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
				auto ray_direction = pixel_center + uv_offset - ray_origin;
				ray r(ray_origin, ray_direction);
				avg_color += ray_color(r, 0, scene);
			}
			image[j][i] = avg_color * pixel_samples_scale;
		}
	}
	return;
}

void camera::render(const hittable& scene)
{
	auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
	defocus_disk_u = u * defocus_radius;
	defocus_disk_v = v * defocus_radius;

	auto start_time = std::chrono::system_clock::now();

	int pool_count = thread_count <= 0 ? std::max(1, static_cast<int>(std::thread::hardware_concurrency())) : std::min(thread_count, static_cast<int>(std::thread::hardware_concurrency()));
	std::clog << "Pool Count: " << pool_count << "\n" << std::flush;
	std::vector<std::thread> pools;

	std::vector<std::vector<color>> image(y_pixel_res, std::vector<color>(x_pixel_res));

	int columns = static_cast<int>(std::ceil(std::sqrt(pool_count)));
	int rows = static_cast<int>(std::ceil(pool_count / (double)columns));
	std::clog << "Section Columns: " << columns << ", Section Rows: " << rows << "\n" << std::flush;
	int x_pixel_batch_res = x_pixel_res / columns;
	int y_pixel_batch_res = y_pixel_res / rows;
	std::clog << "X-Pixel Batch Size: " << x_pixel_batch_res << "\nY-Pixel Batch Size: " << y_pixel_batch_res << "\n" << std::flush;

	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < columns; col++)
		{
			int x_start = col * x_pixel_batch_res;
			int y_start = row * y_pixel_batch_res;
			int x_end = x_start + x_pixel_batch_res;
			int y_end = y_start + y_pixel_batch_res;
			std::clog << "Rendering Section: [" << x_start << ", " << y_start << "] to [" << x_end << ", " << y_end << "]\n" << std::flush;
			pools.emplace_back(std::thread(&camera::render_section, this, std::ref(scene), std::ref(image), x_start, y_start, x_end, y_end));
		}
	}

	for (int p = 0; p < pools.size(); p++)
	{
		pools[p].join();
		std::clog << "Finished Thread " << p + 1 << "\n" << std::flush;
	}

	std::cout << "P3\n" << x_pixel_res << ' ' << y_pixel_res << "\n255\n";
	for (std::vector<color>& row : image)
	{
		for (color& pixel : row)
		{
			write_color(std::cout, pixel);
		}
	}

	std::clog << "\nRender Took " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start_time).count() << " ms\n";
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
		ray scattered;
		color attenuation;
		if (payload.mat->scatter(in_ray, payload, attenuation, scattered))
		{
			return attenuation * ray_color(scattered, bounce + 1, scene);
		}
		return color();
	}
	// Sky
	vec3 unit_direction = vec3::unit(in_ray.direction());
	auto a = 0.5 * (unit_direction.z() + 1.0);
	return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

vec3 camera::defocus_disk_sample() const
{
	auto point = vec3::random_in_unit_disk();
	return center + (point[0] * defocus_disk_u) + (point[1] * defocus_disk_v);
}