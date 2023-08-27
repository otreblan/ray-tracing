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

#include "ray.hpp"

ray::ray(){}

ray::ray(RTCRay _ray):
	_ray(_ray)
{}

ray::ray(glm::vec3 origin, glm::vec3 direction)
{
	set_origin(origin);
	_ray.tnear = 0;

	set_direction(direction);
	_ray.tfar = std::numeric_limits<float>::infinity();

	_ray.mask  = -1;
	_ray.flags = 0;
}

RTCRay& ray::get()
{
	return _ray;
}

const RTCRay& ray::get() const
{
	return _ray;
}

glm::vec3 ray::at(float t) const
{
	return get_origin() + t*get_direction();
}

glm::vec3 ray::get_origin() const
{
	return {_ray.org_x, _ray.org_y, _ray.org_z};
}

glm::vec3 ray::get_direction() const
{
	return {_ray.dir_x, _ray.dir_y, _ray.dir_z};
}

void ray::set_origin(glm::vec3 origin)
{
	_ray.org_x = origin.x;
	_ray.org_y = origin.y;
	_ray.org_z = origin.z;
}

void ray::set_direction(glm::vec3 direction)
{
	_ray.dir_x = direction.x;
	_ray.dir_y = direction.y;
	_ray.dir_z = direction.z;
}
