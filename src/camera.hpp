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

#include <fmt/format.h>
#include <glm/vec3.hpp>

#include "ray.hpp"

class hittable;
struct aiCamera;

class camera
{
private:
	int   image_width;
	int   image_height;
	float aspect_ratio;

	int samples_per_pixel;
	int max_depth;

	float vfov;         // Vertical view angle (field of view)
	glm::vec3 lookfrom; // Point camera is looking from
	glm::vec3 lookat;   // Point camera is looking at
	glm::vec3 vup;      // Camera-relative "up" direction

	glm::vec3 background;

	glm::vec3 center;         // Camera center
	glm::vec3 pixel00_loc;    // Location of pixel 0, 0
	glm::vec3 pixel_delta_u;  // Offset to pixel to the right
	glm::vec3 pixel_delta_v;  // Offset to pixel below
	glm::vec3 u, v, w;        // Camera frame basis vectors

	glm::vec3 ray_color(const ray& r, const hittable& world, int depth);

	ray get_ray(int i, int j) const;

	glm::vec3 pixel_sample_square() const;

public:
	camera(
		int image_width,
		int image_height,
		int samples_per_pixel,
		int max_depth,
		float vfov,
		glm::vec3 lookfrom,
		glm::vec3 lookat,
		glm::vec3 vup,
		glm::vec3 background
	);

	camera(int image_width, int image_height, int samples_per_pixel, int max_depth, const aiCamera& c, glm::vec3 background);

	void render(const hittable& world);
};

class sampled_color
{
private:
	const glm::vec3& pixel_color;
	int samples_per_pixel;

public:
	sampled_color(const glm::vec3& pixel_color, int samples_per_pixel):
		pixel_color(pixel_color),
		samples_per_pixel(samples_per_pixel)
	{};

	friend struct fmt::formatter<sampled_color>;
};
