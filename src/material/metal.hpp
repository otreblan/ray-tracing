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

#include "material.hpp"

#include <glm/vec3.hpp>

#include <cmath>

class metal: public material
{
public:
	glm::vec3 albedo;
	float fuzz;

	metal(glm::vec3 albedo, float f):
		albedo(albedo),
		fuzz(std::min(f, 1.f))
	{};

	bool scatter(
		const ray& r_in,
		const hit_record& rec,
		glm::vec3& attenutation,
		ray& scattered
	) const override;

	virtual ~metal() = default;
};
