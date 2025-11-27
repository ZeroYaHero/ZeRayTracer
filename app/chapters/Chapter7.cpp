#include "ChapterInterface.h"

#ifdef CHAPTER_7

#include "Color.h"
#include "Ray.h"
#include "Sphere.h"
#include "HittableList.h"
#include "HitPayload.h"
#include "Camera.h"
#include "Utility.h"
#include "Material.h"

#include <memory>

int init_chapter()
{
	// Materials
	auto red_lambertian =	std::make_shared<material>(colors::RED,		LAMBERTIAN);
	auto blue_lambertian =	std::make_shared<material>(colors::BLUE,	LAMBERTIAN);

	auto normals =			std::make_shared<material>(colors::BLACK,	LAMBERTIAN);
	normals->normal_colors = true; // I know this is not *actual* normals.

	auto silver =			std::make_shared<material>(colors::GREY,	METAL);
	silver->set_metal_fuzzy_factor(0.3);

	auto dialectric_outer = std::make_shared<material>(colors::WHITE,	DIALECTRIC);
	dialectric_outer->set_dialectric_refractive_index(1.5);

	auto dialectric_inner = std::make_shared<material>(colors::WHITE,	DIALECTRIC);
	dialectric_inner->set_dialectric_refractive_index(1.0 / 1.5);
	// So, since we are using spheres the refraction can get confusing. Remember refraction index depends on the medium it exists in.
	// Instead, to demonstrate the refraction the textbook suggests pretending the scene is in "Water" and the bubble is actually an "Air" bubble.
	// ~A dialectric sphere in air never has TIR due to symmetry

	// World
	hittable_list scene;

	auto front_center =			std::make_shared<sphere>(vec3(240, 0, 0),			100,		red_lambertian);
	auto left_center_outer =	std::make_shared<sphere>(vec3(200, -200, 0),		100,		dialectric_outer);
	auto left_center_inner =	std::make_shared<sphere>(vec3(200, -200, 0),		80,			dialectric_inner);
	auto right_center =			std::make_shared<sphere>(vec3(200, 200, 0),			100,		silver);
	auto world =				std::make_shared<sphere>(vec3(200, 0, -20100.0),	20000.0,	blue_lambertian);

	// Camera 
	vec3 center(-500.0,-500.0,750.0);
	vec3 lookat(240,0,0);
	vec3 lookdir = vec3::unit(lookat - center);
	vec3 vup(0, 0, 1);
	double fov = 20;
	camera cam(16, 9, 1280, 1150.0, fov, std::move(center), std::move(lookdir), std::move(vup));	// These values are not dynamic/mutable as some calculations need to be done.
	cam.samples = 24;																						// These values are [dynamic] since no calculations need to be done
	cam.max_bounces = 64;
	cam.defocus_angle = 10;

	scene.add(front_center);
	scene.add(left_center_outer);
	scene.add(left_center_inner);
	scene.add(right_center);
	scene.add(world);

	// Render
	cam.render(scene);
	return 0;
}

#endif // CHAPTER_7