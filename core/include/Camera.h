#ifndef CAMERA_H
#define CAMERA_H

#include "Vec3.h"
#include "Color.h"
#include "Hittable.h"
#include "Ray.h"
#include "Utility.h"

class camera {

private:
	int x_aspect;
	int y_aspect;
	int x_pixel_res;
	int y_pixel_res;
	double focus_dist;
	vec3 center;
	vec3 pixel_center;
	vec3 pixel_delta_u;
	vec3 pixel_delta_v;
	vec3 pixel_00_loc;
	vec3 u;
	vec3 v;
	vec3 w;
	vec3 defocus_disk_u;
	vec3 defocus_disk_v;

	color ray_color(const ray& ray, int bounce, const hittable& world);

	vec3 defocus_disk_sample() const;

public:
	int defocus_angle;
	int samples = 10;
	int max_bounces = 50;
	int thread_count = 0;

	camera(int x_aspect, int y_aspect, int x_pixel_res, double focus_dist, double fov, vec3&& center, vec3&& unit_dir, vec3&& vup) :
		x_aspect(x_aspect), y_aspect(y_aspect), x_pixel_res(x_pixel_res), focus_dist(focus_dist), center(center)
	{
		auto aspect_ratio = double(x_aspect) / y_aspect;
		y_pixel_res = std::max(int((double)(x_pixel_res) / x_aspect * y_aspect), 1);

		auto theta = degrees_to_radians(fov);
		auto h = std::tan(theta / 2); 
		auto viewport_height_cm = 2 * h * focus_dist;
		auto viewport_width_cm = viewport_height_cm * (double(x_pixel_res) / y_pixel_res);

		u = vec3::cross(vup, unit_dir); // Cross product here is a vector that shoots to the side (u), because w (unit dir) and v (up dir) are not orthogonal but they aren't parallel either.
		v = vec3::cross(unit_dir, u);	// Now we have forward vector (w or the unit_dir) and a side vector (u), so another cross product results in a relative up vector.
		
		auto viewport_u = u * viewport_width_cm;
		auto viewport_v = v * -viewport_height_cm;
		pixel_delta_u = viewport_u / x_pixel_res;
		pixel_delta_v = viewport_v / y_pixel_res;
		pixel_00_loc = center + (unit_dir * focus_dist) - (viewport_u + viewport_v + pixel_delta_u + pixel_delta_v) * 0.5;
	}

	void render(const hittable& scene);

	void render_section(const hittable& scene, std::vector<std::vector<color>>& image, int x_start, int y_start, int x_end, int y_end);
};

#endif // CAMERA_H