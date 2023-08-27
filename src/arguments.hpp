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

#include <utility>

class arguments
{
private:
	int    argc;
	char** argv;

	/// Prints this program usage and then exits.
	[[noreturn]]
	void usage(int exit_code) const;

	int image_width       = 400;
	int image_height      = 225;
	int samples_per_pixel = 100;
	int max_depth         = 50;

public:
	int   get_image_width()       const {return image_width;}
	int   get_image_height()      const {return image_height;}
	float get_aspect_ratio()      const {return (float)image_width/image_height;}
	int   get_samples_per_pixel() const {return samples_per_pixel;}
	int   get_max_depth()         const {return max_depth;}

	arguments(int argc, char** argv);
};
