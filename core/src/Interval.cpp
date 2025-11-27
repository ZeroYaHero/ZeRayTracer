#include "Interval.h"

double interval::size() const {
	return max - min;
}

bool interval::contains(double t) const
{
	return min <= t && t <= max;
}

bool interval::surrounds(double t) const
{
	return min < t && t < max;
}

double interval::clamp(double t) const
{
	if (t > max) return max;
	if (t < min) return min;
	return t;
}

const interval interval::nothing = interval(+infinity, -infinity);
const interval interval::everything = interval(-infinity, +infinity);