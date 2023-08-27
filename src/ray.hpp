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

#include "embree.hpp"

#include <glm/vec3.hpp>

class ray
{
private:
	RTCRay _ray;

public:
	ray();

	ray(RTCRay _ray);

	ray(glm::vec3 origin, glm::vec3 direction);

	RTCRay& get();
	const RTCRay& get() const;

	glm::vec3 at(float t) const;

	glm::vec3 get_origin() const;
	glm::vec3 get_direction() const;

	void set_origin(glm::vec3 origin);
	void set_direction(glm::vec3 direction);
};
