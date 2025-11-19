#ifndef HITTABLE_H
#define HITTABLE_H

#include "HitPayload.h"
#include "Ray.h"
#include "Vec3.h"
#include "Interval.h"

// Notes:
// - Textbook mentions object is not great as it could be confused/collide with OO
// - It also notes how surface is not always the best example considering that not everything that a ray can collide with is a "surface" it could be a point cloud
class hittable
{
public:
	virtual ~hittable() = default;
	virtual bool hit(const ray& r, interval t_min_max, hit_payload& pay) const = 0;
};

#endif // HITTABLE_H