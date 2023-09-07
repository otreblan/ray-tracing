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
#include "material.hpp"
#include "mesh.hpp"
#include "rtweekend.hpp"
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
	rtcSetSceneBuildQuality(rtc_scene, RTCBuildQuality::RTC_BUILD_QUALITY_HIGH);
	Assimp::Importer importer;

	const aiScene* ai_scene = importer.ReadFile(
		file,
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_GenNormals |
		aiProcess_PreTransformVertices // TODO: Apply transforms to every node
	);

	if(ai_scene == nullptr)
	{
		std::cerr << importer.GetErrorString() << '\n';
		exit(EXIT_FAILURE);
	}

	import_cameras(*ai_scene, image_width, image_height, samples_per_pixel, max_depth, background);
	import_materials(*ai_scene);
	import_meshes(*ai_scene, device);

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
		fmt::print(stderr, "Importing camera {}.\n", camera.mName.C_Str());

		auto* node = ai_scene.mRootNode->FindNode(camera.mName);
		auto transformation = to_glm(node->mParent->mTransformation)*to_glm(node->mTransformation);

		//aiMatrix4x4 mat;
		//camera.GetCameraMatrix(mat);

		//auto position = mat*camera.mPosition;
		//auto position2 = to_glm(node->mTransformation)*glm::vec4(to_glm(camera.mPosition),1);

		cameras.emplace_back(
			image_width,
			image_height,
			samples_per_pixel,
			max_depth,
			camera,
			background,
			glm::mat4(1)
		);
	}
}

void scene::import_materials(const aiScene& ai_scene)
{
	for(size_t i = 0; i < ai_scene.mNumMaterials; i++)
	{
		const auto& material = *ai_scene.mMaterials[i];
		fmt::print(stderr, "Importing material {}.\n", material.GetName().C_Str());

		aiColor3D emission;
		material.Get(AI_MATKEY_COLOR_EMISSIVE, emission);

		if(!emission.IsBlack())
		{
			materials.emplace_back(std::make_shared<diffuse_light>(to_glm(emission)));
		}
		else
		{
			aiColor3D diffuse;
			material.Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
			materials.emplace_back(std::make_shared<lambertian>(to_glm(diffuse)));
		}
		// TODO: Import metal and dielectric
	}
}

void scene::import_meshes(const aiScene& ai_scene, RTCDevice device)
{
	for(size_t i = 0; i < ai_scene.mNumMeshes; i++)
	{
		const aiMesh& ai_mesh = *ai_scene.mMeshes[i];
		fmt::print(stderr, "Importing mesh {}.\n", ai_mesh.mName.C_Str());

		RTCGeometry rtc_geom = rtcNewGeometry(device, RTC_GEOMETRY_TYPE_TRIANGLE);

		auto* node = ai_scene.mRootNode->FindNode(ai_mesh.mName);
		auto transformation = node->mParent->mTransformation*node->mTransformation;

		import_vertices(ai_mesh, rtc_geom);
		import_indices(ai_mesh, rtc_geom);

		// TODO: Set transformation

		rtcCommitGeometry(rtc_geom);

		unsigned id = rtcAttachGeometry(rtc_scene, rtc_geom);
		void* geo_ptr = geometry.emplace_back(std::make_unique<mesh>(id, materials.at(ai_mesh.mMaterialIndex))).get();
		rtcSetGeometryUserData(rtc_geom, geo_ptr);

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

void scene::render()
{
	cameras.begin()->render(*this);
}
