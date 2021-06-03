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

#include <fmt/core.h>

int main()
{
	// Image
	const int image_width = 256;
	const int image_height = 256;

	// Render
	fmt::print("P3\n{} {}\n255\n", image_width, image_height);

	for (int j = image_height-1; j >= 0; --j)
	{
		for (int i = 0; i < image_width; ++i)
		{
			auto r = double(i) / (image_width-1);
			auto g = double(j) / (image_height-1);
			auto b = 0.25;

			int ir = static_cast<int>(255.999 * r);
			int ig = static_cast<int>(255.999 * g);
			int ib = static_cast<int>(255.999 * b);

			fmt::print("{} {} {}\n", ir, ig, ib);
		}
	}
}
