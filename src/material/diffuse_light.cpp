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

#include "diffuse_light.hpp"

#include "../hittable.hpp"
#include "../ray.hpp"
#include "../rtweekend.hpp"

diffuse_light::diffuse_light(glm::vec3 color):
	color(color)
{};

bool diffuse_light::scatter(const ray&, const hit_record&, glm::vec3&, ray&) const
{
	return false;
}

glm::vec3 diffuse_light::emitted(float, float, const glm::vec3&) const
{
	return color;
}
