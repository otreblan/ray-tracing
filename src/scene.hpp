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
#include <memory>
#include <vector>

#include <embree4/rtcore.h>

class arguments;
struct aiScene;
struct aiMesh;

class scene
{
private:
	RTCScene rtc_scene;

	std::vector<camera> cameras;
	std::vector<std::unique_ptr<hittable>> geometry;

	void import_cameras(const aiScene& ai_scene,
		int image_width,
		int image_height,
		int samples_per_pixel,
		int max_depth,
		glm::vec3 background
	);

	void import_meshes(const aiScene& ai_scene, RTCDevice device);
	void import_vertices(const aiMesh& mesh, RTCGeometry rtc_geom);
	void import_indices(const aiMesh& mesh, RTCGeometry rtc_geom);

public:
	scene(RTCDevice device, const arguments& args);
	scene(RTCDevice device,
		const std::filesystem::path& file,
		int image_width,
		int image_height,
		int samples_per_pixel,
		int max_depth,
		glm::vec3 background
	);

	~scene();
};
