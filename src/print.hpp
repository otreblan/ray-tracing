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
#include <glm/common.hpp>
#include <glm/exponential.hpp>
#include <glm/vec3.hpp>

#include "camera.hpp"

template<>
struct fmt::formatter<glm::vec3>: fmt::formatter<int>
{
	template <typename FormatContext>
	auto format(const glm::vec3& v, FormatContext& ctx) const
	{
		return format_to(ctx.out(),
			"{} {} {}",
			(int)(255.999f*v.x),
			(int)(255.999f*v.y),
			(int)(255.999f*v.z)
		);
	}
};

template<>
struct fmt::formatter<sampled_color>: fmt::formatter<int>
{
	template <typename FormatContext>
	auto format(const sampled_color& c, FormatContext& ctx) const
	{
		float scale = 1.f/c.samples_per_pixel;

		auto color = glm::clamp(
			glm::sqrt(c.pixel_color*scale),
			{0.f, 0.f, 0.f},
			{0.999f, 0.999f, 0.999f}
		);

		return format_to(ctx.out(),
			"{} {} {}",
			(int)(256*color.x),
			(int)(256*color.y),
			(int)(256*color.z)
		);
	}
};
