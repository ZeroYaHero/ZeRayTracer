#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"

class material
{
public:
	double m_roughness;
	double m_metallic;

	material(double m_roughness, double m_metallic) : m_roughness(m_roughness), m_metallic(m_metallic) {}
};

static const material grey_box;

#endif // MATERIAL_H