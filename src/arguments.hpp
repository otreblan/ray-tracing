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

#include <filesystem>
#include <utility>

class arguments
{
private:
	int    argc;
	char** argv;

	/// Prints this program usage and then exits.
	[[noreturn]]
	void usage(int exit_code) const;

public:
	int image_width       = 400;
	int image_height      = 225;
	int samples_per_pixel = 100;
	int max_depth         = 50;
	float vfov            = 90;

	std::filesystem::path scene;

	arguments(int argc, char** argv);
};
