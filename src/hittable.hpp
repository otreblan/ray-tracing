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

#pragma once

#include <glm/geometric.hpp>

#include "ray.hpp"

struct hit_record
{
	glm::vec3 p;
	glm::vec3 normal;
	float t;
	bool front_face;
	inline void set_face_normal(const ray& r, const glm::vec3& outward_normal)
	{
		front_face = glm::dot(r.direction, outward_normal) < 0;
		normal = front_face ? outward_normal :-outward_normal;
	}
};

class hittable
{
public:
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};
