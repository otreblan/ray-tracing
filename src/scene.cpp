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

#include "arguments.hpp"
#include "scene.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <iostream>

scene::scene(const arguments& args):
	scene(
		args.scene,
		args.image_width,
		args.image_height,
		args.samples_per_pixel,
		args.max_depth,
		glm::vec3(0.01f)
	)
{}

scene::scene(const std::filesystem::path& file,
	int image_width,
	int image_height,
	int samples_per_pixel,
	int max_depth,
	glm::vec3 background
)
{
	Assimp::Importer importer;

	const aiScene* ai_scene = importer.ReadFile(
		file,
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_GenNormals
	);

	if(ai_scene == nullptr)
	{
		std::cerr << importer.GetErrorString() << '\n';
		exit(EXIT_FAILURE);
	}

	import_cameras(*ai_scene, image_width, image_height, samples_per_pixel, max_depth, background);
	// TODO: Import meshes
	// TODO: Import material
}

void scene::import_cameras(const aiScene& ai_scene,
	int image_width,
	int image_height,
	int samples_per_pixel,
	int max_depth,
	glm::vec3 background
)
{
	for(size_t i = 0; i < ai_scene.mNumCameras; i++)
	{
		const aiCamera& camera = *ai_scene.mCameras[i];

		cameras.emplace_back(image_width, image_height, samples_per_pixel, max_depth, camera, background);
	}
}
