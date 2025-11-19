#include "HitPayload.h"

void hit_payload::set_face_normal(const ray& r, const vec3& outward_normal)
{
	// Textbook says this should only be called with normals that are unit length.
	//front_face = dot(r.direction(), outward_normal) < 0;
	//norm = front_face ? outward_normal : -outward_normal;
	norm = outward_normal;
}