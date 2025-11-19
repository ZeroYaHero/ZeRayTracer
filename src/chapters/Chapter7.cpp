#include "ChapterInterface.h"

#ifdef CHAPTER_7

#include "Color.h"
#include "Ray.h"
#include "Sphere.h"
#include "HittableList.h"
#include "HitPayload.h"
#include "Camera.h"
#include "Utility.h"

#include <memory>

int init_chapter()
{
	// Camera 
	camera cam(16, 9, 1280, 100.0, 200.0, vec3(), vec3(1, 0, 0)); // These values are not dynamic/mutable as some calculations need to be done.
	// These values are since no calculations need to be done
	cam.samples = 4;
	cam.max_bounces = 32;
	cam.diffuse_render_type = LAMBERTIAN;
	cam.reflectance = 0.3;

	// World
	hittable_list scene;
	scene.add(std::make_shared<sphere>(vec3(200.0, 0, 0), 100.0));
	scene.add(std::make_shared<sphere>(vec3(0, 0, -20100.0), 20000.0));

	// Render
	cam.render(scene);
	return 0;
}

#endif // CHAPTER_7