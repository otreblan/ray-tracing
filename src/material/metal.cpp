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

#include "metal.hpp"

#include "../hittable.hpp"
#include "../ray.hpp"
#include "../rtweekend.hpp"

bool metal::scatter(const ray& r_in, const hit_record& rec, glm::vec3& attenutation, ray& scattered) const
{
	glm::vec3 reflected = glm::reflect(glm::normalize(r_in.direction), rec.normal);
	scattered = ray(rec.p, reflected + fuzz*glm::ballRand(1.f));
	attenutation = albedo;

	return glm::dot(scattered.direction, rec.normal) > 0.f;
}
