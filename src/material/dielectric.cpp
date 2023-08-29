// Ray tracing
// Copyright © 2021 otreblan
//
// ray-tracing is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// ray-tracing is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with ray-tracing.  If not, see <http://www.gnu.org/licenses/>.

#include "dielectric.hpp"

#include "../hittable.hpp"
#include "../ray.hpp"
#include "../rtweekend.hpp"

bool dielectric::scatter(const ray& r_in, const hit_record& rec, glm::vec3& attenutation, ray& scattered) const
{
	attenutation = glm::vec3(1.f, 1.f, 1.f);
	float refraction_ratio = rec.front_face ? (1.f/ir) : ir;

	glm::vec3 unit_direction = glm::normalize(r_in.get_direction());
	glm::vec3 direction;

	float cos_theta = fminf(dot(-unit_direction, rec.normal), 1.f);
	float sin_theta = sqrt(1.f - cos_theta*cos_theta);

	bool cannot_refract = refraction_ratio * sin_theta > 1.f;

	if(cannot_refract || reflectance(cos_theta, refraction_ratio) > random_float())
	{
		direction = glm::reflect(unit_direction, rec.normal);
	}
	else
	{
		direction = glm::refract(unit_direction, rec.normal, refraction_ratio);
	}

	scattered = ray(rec.p, direction);
	return true;
}

double dielectric::reflectance(float cosine, float ref_idx)
{
	// Use Schlick's approximation for reflectance.
	float r0 = (1-ref_idx) / (1+ref_idx);
	r0 = r0*r0;
	return r0 + (1-r0)*pow((1 - cosine),5);
}
