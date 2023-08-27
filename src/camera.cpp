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

#include <glm/gtx/compatibility.hpp>

#include "camera.hpp"
#include "hittable.hpp"
#include "material.hpp"
#include "rtweekend.hpp"
#include "print.hpp"

glm::vec3 camera::ray_color(const ray& r, const hittable& world, int depth)
{
	hit_record rec;

	if(depth <= 0)
		return glm::vec3(0.f);

	if(world.hit(r, 0.001f, HUGE_VALF, rec))
	{
		ray scattered;
		glm::vec3 attenuation;

		if(rec.mat_ptr && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return attenuation * ray_color(scattered, world, depth-1);

		return glm::vec3(0.f);
	}

	// Background
	glm::vec3 unit_direction = glm::normalize(r.get_direction());
	float t = 0.5f*(unit_direction.y + 1.f);
	return glm::lerp(glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.5f, 0.7f, 1.f), t);
}

ray camera::get_ray(int i, int j) const
{
	// Get a randomly sampled camera ray for the pixel at location i,j.
	glm::vec3 pixel_center = pixel00_loc + ((float)i * pixel_delta_u) + ((float)j * pixel_delta_v);
	glm::vec3 pixel_sample = pixel_center + pixel_sample_square();

	glm::vec3 ray_origin = center;
	glm::vec3 ray_direction = pixel_sample - ray_origin;

	return ray(ray_origin, ray_direction);
}

glm::vec3 camera::pixel_sample_square() const
{
	// Returns a random point in the square surrounding a pixel at the origin.
	float px = -0.5f + random_float();
	float py = -0.5f + random_float();
	return (px * pixel_delta_u) + (py * pixel_delta_v);
}

void camera::render(const hittable& world)
{
	bool stdout_tty = isatty(STDOUT_FILENO);

	// Render
	fmt::print("P3\n{} {}\n255\n", image_width, image_height);

	for (int j = 0; j < image_height; j++)
	{
		if(!stdout_tty)
			fmt::print(stderr, "\rRemaining scanlines: {} ", image_height-j);

		for (int i = 0; i < image_width; ++i)
		{
			glm::vec3 pixel_color(0.f);

			for(int s = 0; s < samples_per_pixel; s++)
			{
				ray r = get_ray(i, j);
				pixel_color += ray_color(r, world, max_depth);
			}

			fmt::print("{}\n", sampled_color(pixel_color, samples_per_pixel));
		}
	}

	if(!stdout_tty)
		fmt::print(stderr, "\n");
}

camera::camera(
		int image_width,
		int image_height,
		int samples_per_pixel,
		int max_depth,
		float vfov,
		glm::vec3 lookfrom,
		glm::vec3 lookat,
		glm::vec3 vup
		):
	image_width(image_width),
	image_height(image_height),
	aspect_ratio((float)image_width/image_height),
	samples_per_pixel(samples_per_pixel),
	max_depth(max_depth),
	vfov(vfov),
	lookfrom(lookfrom),
	lookat(lookat),
	vup(vup),
	center(lookfrom)
{
	// Determine viewport dimensions.
	float focal_length = (lookfrom-lookat).length();
	float theta = degrees_to_radians(vfov);
	float h = tan(theta/2);
	float viewport_height = 2.f * h * focal_length;
	float viewport_width = viewport_height * (float)image_width/image_height;

	// Calculate the u,v,w unit basis vectors for the camera coordinate frame.
	w = glm::normalize(lookfrom - lookat);
	u = glm::normalize(glm::cross(vup, w));
	v = cross(w, u);

	// Calculate the vectors across the horizontal and down the vertical viewport edges.
	glm::vec3 viewport_u(viewport_width*u);
	glm::vec3 viewport_v(viewport_height*-v);

	// Calculate the horizontal and vertical delta vectors from pixel to pixel.
	pixel_delta_u = viewport_u / (float)image_width;
	pixel_delta_v = viewport_v / (float)image_height;

	// Calculate the location of the upper left pixel.
	glm::vec3 viewport_upper_left(center - focal_length*w - viewport_u/2.f - viewport_v/2.f);
	pixel00_loc = viewport_upper_left + 0.5f * (pixel_delta_u + pixel_delta_v);
}
