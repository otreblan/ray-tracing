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

#include <random>

#include <assimp/matrix4x4.h>
#include <assimp/vector3.h>
#include <glm/gtc/random.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/vec3.hpp>

#include "embree.hpp"

void errorFunction(void* userPtr, enum RTCError error, const char* str);

inline glm::vec3 to_glm(aiVector3D v)
{
	return {v.x, v.y, v.z};
}

inline glm::mat4 to_glm(aiMatrix4x4 m)
{
	glm::mat4 _m;

	for(size_t i = 0; i < 4; i++)
	{
		for(size_t j = 0; j < 4; j++)
		{
			_m[i][j] = m[i][j];
		}
	}

	return glm::transpose(_m);
}

inline glm::vec3 transform(glm::mat4 transformation, glm::vec3 v, float w = 1.f)
{
	glm::vec4 v4(v, w);

	v4 = transformation*v4;

	return v4;
}

inline float random_float()
{
	static std::uniform_real_distribution<float> distribution(0.f, 1.f);
	static std::mt19937 generator;
	return distribution(generator);
}

inline float random_float(float _min, float _max)
{
	return std::lerp(_min, _max, random_float());
}

inline glm::vec3 random_vec3()
{
	return {random_float(), random_float(), random_float()};
}

inline glm::vec3 random_vec3(float _min, float _max)
{
	return {
		random_float(_min, _max),
		random_float(_min, _max),
		random_float(_min, _max)
	};
}

inline glm::vec3 random_in_hemisphere(const glm::vec3& normal)
{
	glm::vec3 in_ball = glm::ballRand(1.f);
	if(glm::dot(in_ball, normal) > 0.f)
		return in_ball;
	else
		return -in_ball;
}

constexpr bool near_zero(const glm::vec3& v)
{
	constexpr float s = 1e-8f;
	return glm::all(glm::lessThan(glm::abs(v), glm::vec3(s)));
}

constexpr float degrees_to_radians(float degrees)
{
	return degrees * std::numbers::pi_v<float>/180;
}
