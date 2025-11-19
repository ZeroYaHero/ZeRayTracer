#ifndef CAMERA_H
#define CAMERA_H

#include "Vec3.h"
#include "Color.h"
#include "Hittable.h"
#include "Ray.h"

enum DiffuseRenderModel {
	DEBUG_NORMAL,
	RANDOM,
	LAMBERTIAN
};

class camera {

private:
	int x_aspect;
	int y_aspect;
	int x_pixel_res;
	int y_pixel_res;
	double focal_length_cm;
	vec3 center;
	vec3 pixel_center;
	vec3 pixel_delta_u;
	vec3 pixel_delta_v;
	vec3 pixel_00_loc;
	color ray_color(const ray& ray, int bounce, const hittable& world);

public:
	DiffuseRenderModel diffuse_render_type = LAMBERTIAN;
	double reflectance = 0.5;
	int samples = 10;
	int max_bounces = 50;

	camera(int x_aspect, int y_aspect, int x_pixel_res, double focal_length_cm, double viewport_height_cm, vec3&& center, vec3&& unit_dir) :
		x_aspect(x_aspect), y_aspect(y_aspect), x_pixel_res(x_pixel_res), focal_length_cm(focal_length_cm), center(center)
	{
		auto aspect_ratio = double(x_aspect) / y_aspect;
		
		y_pixel_res = std::max(int((double)(x_pixel_res) / x_aspect * y_aspect), 1);
		auto viewport_width_cm = viewport_height_cm * (double(x_pixel_res) / y_pixel_res);
		
		auto viewport_u = vec3(0, viewport_width_cm, 0);
		auto viewport_v = vec3(0, 0, -viewport_height_cm);
		pixel_delta_u = viewport_u / x_pixel_res;
		pixel_delta_v = viewport_v / y_pixel_res;
		pixel_00_loc = center + (unit_dir * focal_length_cm) - (viewport_u + viewport_v + pixel_delta_u + pixel_delta_v) * 0.5;
	}

	void render(const hittable& scene);
};

#endif // CAMERA_H