#pragma once
#include "ray.h"
#include "hitable.h"
#include <random>

class material 
{
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;

};

//0 1 random real generator
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0, 1);//uniform distribution between 0 and 1

vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		p = 2.0 * vec3(dis(gen), dis(gen), dis(gen)) - vec3(1, 1, 1);
	} while (p.squared_length() >= 1.0f);
	return p;
}

vec3 reflect(const vec3& v, const vec3& n) {
	return v - 2 * dot(v, n) * n;
}