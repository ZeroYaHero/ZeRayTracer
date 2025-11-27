#ifndef INTERVAL_H
#define INTERVAL_H

#include "Utility.h"

class interval
{
public:
	double min;
	double max;

	interval() {}
	interval(double min, double max) : min(min), max(max) {}
	
	double size() const;
	bool contains(double t) const;
	bool surrounds(double t) const;
	double clamp(double  t) const;

	static const interval nothing;
	static const interval everything;
};

#endif // INTERVAL_H