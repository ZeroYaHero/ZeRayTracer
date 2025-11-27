#include "Material.h"
#include "Utility.h"

bool material::scatter(const ray& ray_in, const hit_payload& payload, color& attenuation, ray& ray_out)
{
	if (normal_colors)
	{
		vec3 vis_norm = vec3(payload.norm.y(), payload.norm.z(), std::abs(payload.norm.x()));
		attenuation = 0.5 * (vis_norm + color(1.0, 1.0, 1.0));
	}
	else
	{
		attenuation = albedo;
	}
	// Admittedly, this switch case for every ray (pixel_count * samples) is not ideal. You would want to have this done way earlier.
	switch (mat_type)
	{
		case RANDOM_REFLECT:
		{
			vec3 random_bounce = vec3::random_unit();
			if (vec3::dot(random_bounce, payload.norm) < 0.0)
			{
				random_bounce = -random_bounce;
			}
			ray_out = ray(payload.loc, random_bounce);
			return true;
		}
		break;
		case LAMBERTIAN:
		{
			auto scatter_direction = payload.norm + vec3::random_unit();
			if (scatter_direction.almost_zero())
			{
				scatter_direction = payload.norm;
			}
			ray_out = ray(payload.loc, scatter_direction); // Here we can choose to absorb the ray by some probability, if we would like.
			return true;
		}
		break;
		case METAL:
		{
			auto scatter_direction = vec3::reflect(ray_in.direction(), payload.norm);
			auto fuzzy_offset = metal_fuzzy_factor * vec3::random_unit();
			scatter_direction = vec3::unit(scatter_direction) + fuzzy_offset;
			ray_out = ray(payload.loc, scatter_direction);
			return (vec3::dot(ray_out.direction(), payload.norm) > 0); // Make sure the fuzz offset doesn't point the ray back into the circle.
		}
		break;
		case DIALECTRIC:
		{
			//attenuation = color(1, 1, 1);
			vec3 ray_udir = vec3::unit(ray_in.direction());

			bool is_entering = (vec3::dot(ray_udir, payload.norm) < 0.0);
			double refraction_index = is_entering ? (1.0 / dialectric_refractive_index) : dialectric_refractive_index;
			vec3 corrected_norm = is_entering ? payload.norm : -payload.norm;

			double cos_theta = std::fmin(vec3::dot(-ray_udir, corrected_norm), 1.0);
			double sin_theta = std::sqrt(1 - cos_theta * cos_theta);

			bool cannot_refract = refraction_index * sin_theta > 1.0;
			vec3 ray_out_direction;

			if (cannot_refract || (reflectance(cos_theta, refraction_index) > random_double()))
			{
				ray_out_direction = vec3::reflect(ray_udir, corrected_norm);
			}
			else
			{
				ray_out_direction = vec3::refract(ray_udir, corrected_norm, refraction_index);
			}
			ray_out = ray(payload.loc, ray_out_direction);
			return true;
		}	
		break;
	}
	return false;
}

bool material::set_metal_fuzzy_factor(double in_metal_fuzzy_factor)
{
	if (mat_type != METAL) return false;
	metal_fuzzy_factor = in_metal_fuzzy_factor; 
	return true;
}

bool material::set_dialectric_refractive_index(double in_dialectric_refractive_index)
{
	if (mat_type != DIALECTRIC) return false;
	dialectric_refractive_index = in_dialectric_refractive_index;
	return true;
}