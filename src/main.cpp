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

#include <cmath>
#include <iostream>
#include <unistd.h>

#include <fmt/core.h>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/compatibility.hpp>

#include "print.hpp"
#include "ray.hpp"

bool hit_sphere(const glm::vec3& center, float radius, const ray& r)
{
	glm::vec3 oc = r.origin - center;
	float a = glm::dot(r.direction, r.direction);
	float b = 2.f * glm::dot(oc, r.direction);
	float c = glm::dot(oc, oc) - radius*radius;
	return b*b - 4.f*a*c > 0;
}

glm::vec3 ray_color(const ray& r)
{
	if(hit_sphere(glm::vec3(0.f, 0.f ,-1.f), 0.5f, r))
		return glm::vec3(1.f, 0.f ,0.f);

	glm::vec3 unit_direction = glm::normalize(r.direction);
	float t = 0.5f*(unit_direction.y + 1);
	return glm::lerp(glm::vec3(1, 1, 1), glm::vec3(0.5f, 0.7f, 1.f), t);
}

int main()
{
	bool stdout_tty = isatty(STDOUT_FILENO);

	// Image
	const float aspect_ratio = 16.f/9.f;
	const int image_width = 400;
	const int image_height = image_width/aspect_ratio;

	// Camera
	float viewport_height = 2.f;
	float viewport_width = aspect_ratio*viewport_height;
	float focal_length = 1.f;

	glm::vec3 origin(0.f, 0.f, 0.f);
	glm::vec3 horizontal(viewport_width, 0.f, 0.f);
	glm::vec3 vertical(0.f, viewport_height, 0.f);
	glm::vec3 lower_left_corner =
		origin -
		horizontal/2.f -
		vertical/2.f -
		glm::vec3(0.f, 0.f, focal_length)
	;

	// Render
	fmt::print("P3\n{} {}\n255\n", image_width, image_height);

	for (int j = image_height-1; j >= 0; --j)
	{
		if(!stdout_tty)
			fmt::print(stderr, "\rScanlines ramaining: {} ", j);

		for (int i = 0; i < image_width; ++i)
		{
			float u = ((float)i)/(image_width-1);
			float v = ((float)j)/(image_height-1);

			ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);

			fmt::print("{}\n", ray_color(r));
		}
	}
}
