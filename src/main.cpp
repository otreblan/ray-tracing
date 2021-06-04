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

#include <iostream>
#include <unistd.h>

#include <fmt/core.h>
#include <glm/vec3.hpp>

#include "print.hpp"

int main()
{
	// Image
	const int image_width = 256;
	const int image_height = 256;

	bool stdout_tty = isatty(STDOUT_FILENO);

	// Render
	fmt::print("P3\n{} {}\n255\n", image_width, image_height);

	for (int j = image_height-1; j >= 0; --j)
	{
		if(!stdout_tty)
			fmt::print(stderr, "\rScanlines ramaining: {} ", j);

		for (int i = 0; i < image_width; ++i)
		{
			glm::vec3 pixel_color(
				((float)i)/(image_width-1),
				((float)j)/(image_height-1),
				0.25f
			);

			fmt::print("{}\n", pixel_color);
		}
	}
}
