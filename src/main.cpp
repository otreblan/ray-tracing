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

#include <glm/vec3.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "arguments.hpp"
#include "camera.hpp"
#include "hittable_list.hpp"
#include "material.hpp"
#include "sphere.hpp"
#include "rtweekend.hpp"

int main(int argc, char** argv)
{
	arguments args(argc, argv);

	// World
	hittable_list world;

	auto material_ground = std::make_shared<lambertian>(glm::vec3(0.8f, 0.8f, 0.f));
	auto material_center = std::make_shared<lambertian>(glm::vec3(0.1f, 0.2f, 0.5f));
	auto material_left = std::make_shared<dielectric>(1.5f);
	auto material_right = std::make_shared<metal>(glm::vec3(0.8f, 0.6f, 0.2f), 0.f);
	auto material_light = std::make_shared<diffuse_light>(glm::vec3(1.f));

	world.add<sphere>(glm::vec3(0.f,  -100.5f, -1.f), 100.f, material_ground);
	world.add<sphere>(glm::vec3(0.f,  0.f,     -1.f), 0.5f, material_center);
	world.add<sphere>(glm::vec3(-1.f, 0.f,     -1.f), 0.5f, material_left);
	world.add<sphere>(glm::vec3(-1.f, 0.f,     -1.f), -0.4f, material_left);
	world.add<sphere>(glm::vec3(1.f,  0.f,     -1.f), 0.5f, material_right);
	world.add<sphere>(glm::vec3(0.f,  1.f,     -1.f), 0.5f, material_light);

	int n = 50;
	for(int i = 0; i < n; i++)
	{
		glm::vec3 pos(0,0,3);
		pos = glm::rotateY(pos, std::lerp(0.f, degrees_to_radians(360), (float)i/n));

		world.add<sphere>(glm::vec3(0,1,-1)+pos, 0.1f, material_light);
	}

	camera cam(
		args.image_width,
		args.image_height,
		args.samples_per_pixel,
		args.max_depth,
		args.vfov,
		{-2, 2, 1},
		{0,  0, -1},
		{0,  1, 0},
		glm::vec3(0.01f)
	);

	cam.render(world);

	return EXIT_SUCCESS;
}
