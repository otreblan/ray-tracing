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

#include <memory>

#include <glm/geometric.hpp>

#include "embree.hpp"
#include "ray.hpp"

class material;

struct hit_record
{
private:
	RTCRayHit rayHit;
	// TODO: Wrap embree's rayhit

public:
	glm::vec3 p;
	glm::vec3 normal;
	std::shared_ptr<material> mat_ptr;
	float t;
	bool front_face;

	float get_u() const {return rayHit.hit.u;}
	float get_v() const {return rayHit.hit.v;}
	glm::vec3 get_p() const
	{
		// TODO: Evaluate orig.at(tfar)
		return p;
	}

	hit_record(const ray& r)
	{
		rayHit.ray = r.get();

		rayHit.hit.geomID    = RTC_INVALID_GEOMETRY_ID;
		rayHit.hit.instID[0] = RTC_INVALID_GEOMETRY_ID;
	}

	RTCRayHit& get()
	{
		return rayHit;
	}

	const RTCRayHit& get() const
	{
		return rayHit;
	}

	glm::vec3 get_normal(RTCScene scene) const
	{
		glm::vec3 norm;

		rtcInterpolate0(rtcGetGeometry(scene, rayHit.hit.geomID), rayHit.hit.primID, rayHit.hit.u, rayHit.hit.v, RTC_BUFFER_TYPE_VERTEX_ATTRIBUTE, 0, &norm.x, 3);

		return glm::normalize(norm);
	}

	glm::vec3 get_origin() const
	{
		return {rayHit.ray.org_x, rayHit.ray.org_y, rayHit.ray.org_z};
	}

	glm::vec3 get_direction() const
	{
		return {rayHit.ray.dir_x, rayHit.ray.dir_y, rayHit.ray.dir_z};
	}
};

class hittable
{
public:
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;

	virtual ~hittable() = default;
};
