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

#include "camera.hpp"
#include "hittable.hpp"

#include <filesystem>
#include <vector>

class arguments;
struct aiScene;

class scene
{
private:
	std::vector<camera> cameras;

	void import_cameras(const aiScene& ai_scene,
		int image_width,
		int image_height,
		int samples_per_pixel,
		int max_depth,
		glm::vec3 background
	);

public:
	scene(const arguments& args);
	scene(const std::filesystem::path& file,
		int image_width,
		int image_height,
		int samples_per_pixel,
		int max_depth,
		glm::vec3 background
	);

};
