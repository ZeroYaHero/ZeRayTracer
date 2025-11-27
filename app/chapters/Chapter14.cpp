#include "ChapterInterface.h"

#ifdef CHAPTER_14

#include "Color.h"
#include "Ray.h"
#include "Sphere.h"
#include "HittableList.h"
#include "HitPayload.h"
#include "Camera.h"
#include "Material.h"
#include "Utility.h"

#include <memory>

int init_chapter()
{
	//std::srand(static_cast<unsigned int>(std::time(nullptr)));
	std::srand(17);

	// Materials
	auto red_lambertian =		std::make_shared<material>(colors::RED,		LAMBERTIAN);
	auto blue_lambertian =		std::make_shared<material>(colors::BLUE,	LAMBERTIAN);
	auto green_lambertian =		std::make_shared<material>(colors::GREEN,	LAMBERTIAN);
	auto purple_lambertian =	std::make_shared<material>(color(1, 0, 1),	LAMBERTIAN);
	auto yellow_lambertian =	std::make_shared<material>(color(1, 1, 0),	LAMBERTIAN);
	auto grey_lambertian =		std::make_shared<material>(colors::GREY,	LAMBERTIAN);
	std::shared_ptr<material> lambertians[] = {
		red_lambertian,
		blue_lambertian,
		green_lambertian,
		purple_lambertian,
		yellow_lambertian,
		grey_lambertian
	};

	auto normals =			std::make_shared<material>(colors::BLACK,	LAMBERTIAN);
	normals->normal_colors = true; // I know this is not *actual* normals.

	auto silver =			std::make_shared<material>(colors::GREY,	METAL);
	silver->set_metal_fuzzy_factor(0.0);

	auto dialectric_outer = std::make_shared<material>(colors::WHITE,	DIALECTRIC);
	dialectric_outer->set_dialectric_refractive_index(indexes::WATER);

	auto dialectric_inner = std::make_shared<material>(colors::WHITE,	DIALECTRIC);
	dialectric_inner->set_dialectric_refractive_index(indexes::AIR / indexes::WATER);

	// Scene
	auto front_center =			std::make_shared<sphere>(vec3(240, 0, 100),			100,		silver);
	auto left_center_outer =	std::make_shared<sphere>(vec3(200, -200, 100),		100,		dialectric_outer);
	auto left_center_inner =	std::make_shared<sphere>(vec3(200, -200, 100),		80,			dialectric_inner);
	auto right_center =			std::make_shared<sphere>(vec3(200, 200, 100),		100,		red_lambertian);
	auto world =				std::make_shared<sphere>(vec3(200, 0, -200000.0),	200000.0,	grey_lambertian);

	hittable_list scene;
	scene.add(front_center);
	scene.add(left_center_outer);
	scene.add(left_center_inner);
	scene.add(right_center);
	scene.add(world);
	for (int j = 0; j < 200; j++)
	{
		auto radius = random_double(20, 30);
		auto position = vec3::random_in_unit_disk() * 900.0 + vec3(240, 0, radius);
		if ((vec3(240, 0, 100) - position).length() > 250.0)
		{
			auto ball = std::make_shared<sphere>(position, radius, grey_lambertian);
			auto material_type = random_double(0, 1);
			// Lambertian
			if (material_type < 0.6)
			{
				auto material_index = (int)(random_double() * (sizeof(lambertians) / sizeof(lambertians[0])));
				ball->set_material(lambertians[material_index]);
			}
			// Metal
			else if (material_type < 0.75)
			{
				auto metal_mat = std::make_shared<material>(colors::GREY, METAL);
				metal_mat->set_metal_fuzzy_factor(random_double());
				ball->set_material(std::move(metal_mat));
			}
			// Dialectric
			else if (material_type < 0.9)
			{
				ball->set_material(dialectric_outer);
			}
			// Normals
			else
			{
				ball->set_material(normals);
			}
			scene.add(ball);
		}
	}

	// Camera 
	vec3 center(600.0,-500.0,200.0);
	vec3 lookat(240,0,0);
	vec3 lookdir = vec3::unit(lookat - center);
	vec3 vup(0, 0, 1);
	double fov = 50.0;
	camera cam(16, 9, 1280, (vec3(240, 0, 100) - center).length(), fov, std::move(center), std::move(lookdir), std::move(vup));	// These values are not dynamic/mutable as some calculations need to be done.
	cam.samples = 240;																				// These values are [dynamic] since no calculations need to be done
	cam.max_bounces = 64;
	cam.defocus_angle = 2.0;
	cam.thread_count = 0; // Uses max

	// Render
	cam.render(scene);
	return 0;
}

#endif // CHAPTER_14