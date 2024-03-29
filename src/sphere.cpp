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

#include "sphere.hpp"

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/compatibility.hpp>

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
	glm::vec3 oc = r.get_origin() - center;

	float a      = glm::dot(r.get_direction(), r.get_direction());
	float half_b = glm::dot(oc, r.get_direction());
	float c      = glm::dot(oc, oc) - radius*radius;

	float discriminant = half_b*half_b - a*c;

	if(discriminant < 0.f)
		return false;

	float sqrtd = sqrtf(discriminant);

	// Find the nearest root that lies in the acceptable range.
	float root = (-half_b - sqrtd) / a;
	if(root < t_min || t_max < root)
	{
		root = (-half_b + sqrtd) / a;
		if(root < t_min || t_max < root)
			return false;
	}

	rec.t = root;
	rec.p = r.at(rec.t);

	glm::vec3 outward_normal = (rec.p - center) / radius;

	rec.normal = glm::faceforward(outward_normal, outward_normal, r.get_direction());
	rec.front_face = rec.normal == outward_normal;
	rec.mat_ptr = mat_ptr;

	return true;
}
