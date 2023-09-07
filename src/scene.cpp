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

scene::scene(RTCDevice device, const arguments& args):
	scene(
		device,
		args.scene,
		args.image_width,
		args.image_height,
		args.samples_per_pixel,
		args.max_depth,
		glm::vec3(0.01f)
	)
{}

scene::scene(RTCDevice device,
	const std::filesystem::path& file,
	int image_width,
	int image_height,
	int samples_per_pixel,
	int max_depth,
	glm::vec3 background
):
	rtc_scene(rtcNewScene(device))
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
	import_meshes(*ai_scene, device);
	// TODO: Import materials

	rtcCommitScene(rtc_scene);
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

void scene::import_meshes(const aiScene& ai_scene, RTCDevice device)
{
	for(size_t i = 0; i < ai_scene.mNumMeshes; i++)
	{
		const aiMesh& mesh = *ai_scene.mMeshes[i];

		RTCGeometry rtc_geom = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_TRIANGLE);

		import_vertices(mesh, rtc_geom);
		import_indices(mesh, rtc_geom);

		rtcCommitGeometry(rtc_geom);

		// TODO: Assign id
		unsigned id = rtcAttachGeometry(rtc_scene, rtc_geom);

		rtcReleaseGeometry(rtc_geom);
	}
}

void scene::import_vertices(const aiMesh& mesh, RTCGeometry rtc_geom)
{
	float* verts = (float*)rtcSetNewGeometryBuffer(
		rtc_geom,
		RTC_BUFFER_TYPE_VERTEX,
		0,
		RTC_FORMAT_FLOAT3,
		3*sizeof(float),
		mesh.mNumVertices
	);

	if(verts == nullptr)
		return;

	for(size_t i = 0; i < mesh.mNumVertices; i++)
	{
		const auto& vert = mesh.mVertices[i];

		verts[3*i] = vert.x;
		verts[3*i+1] = vert.y;
		verts[3*i+2] = vert.z;
	}
}

void scene::import_indices(const aiMesh& mesh, RTCGeometry rtc_geom)
{
	unsigned* indices = (unsigned*)rtcSetNewGeometryBuffer(
		rtc_geom,
		RTC_BUFFER_TYPE_INDEX,
		0,
		RTC_FORMAT_UINT3,
		3*sizeof(unsigned),
		mesh.mNumFaces
	);

	if(indices == nullptr)
		return;

	for(size_t i = 0; i < mesh.mNumFaces; i++)
	{
		const auto& face = mesh.mFaces[i];
		assert(face.mNumIndices == 3);

		indices[3*i] = face.mIndices[0];
		indices[3*i+1] = face.mIndices[1];
		indices[3*i+2] = face.mIndices[2];
	}
}

scene::~scene()
{
	rtcReleaseScene(rtc_scene);
}
