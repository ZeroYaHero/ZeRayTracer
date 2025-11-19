#include "HittableList.h"

bool hittable_list::hit(const ray& r, interval t_min_max, hit_payload& pay) const
{
	hit_payload temp;
	double closest = t_min_max.max;
	bool found = false;

	for (const auto& _hittable : hittables)
	{
		if (_hittable->hit(r, interval(t_min_max.min, closest), temp))
		{
			found = true;
			closest = temp.t;
			pay = temp;
		}
	}
	return found;
}

void hittable_list::clear()
{
	hittables.clear();
}

void hittable_list::add(std::shared_ptr<hittable> _hittable)
{
	hittables.push_back(_hittable);
}