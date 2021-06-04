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

#include <glm/vec3.hpp>

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

glm::vec3 random_vec3()
{
	return {random_float(), random_float(), random_float()};
}

glm::vec3 random_vec3(float _min, float _max)
{
	return {
		random_float(_min, _max),
		random_float(_min, _max),
		random_float(_min, _max)
	};
}
