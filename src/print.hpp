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

#include <string_view>

#include <fmt/format.h>
#include <glm/vec3.hpp>

template<>
struct fmt::formatter<glm::vec3>: fmt::formatter<int>
{
	template <typename FormatContext>
	auto format(const glm::vec3& v, FormatContext& ctx)
	{
		return format_to(ctx.out(),
			"{} {} {}",
			(int)(255.999f*v.x),
			(int)(255.999f*v.y),
			(int)(255.999f*v.z)
		);
	}
};
