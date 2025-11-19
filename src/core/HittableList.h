#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "Hittable.h"
#include "HitPayload.h"
#include "Ray.h"

#include <memory>
#include <vector>

class hittable_list : public hittable
{
public:
	std::vector<std::shared_ptr<hittable>> hittables;

	void clear();

	void add(std::shared_ptr<hittable> _hittable);

	bool hit(const ray& r, interval t_min_max, hit_payload& pay) const override;
};

#endif // HITTABLE_LIST_H