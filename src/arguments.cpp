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

#include <cstdlib>
#include <getopt.h>
#include <iostream>

#include "arguments.hpp"

void arguments::usage(int exit_code) const
{
	std::cout
		<< "Usage: " << argv[0] << " [OPTION]...\n"
		<< "\t-h, --help                 Show this help.\n"
		<< "\t-w, --image-width=N        Image width in pixels.\n"
		<< "\t-H, --image-heigth=N       Images height in pixels.\n"
		<< "\t-s, --samples-per-pixel=N  Ray samples per pixel.\n"
		<< "\t-d, --max-depth=N          Max ray depth.\n"
		<< "\t-f, --vfov=N               Vertical FOV in degrees.\n"
		;

	exit(exit_code);
}

arguments::arguments(int argc, char** argv):
	argc(argc),
	argv(argv)
{
	int c;

	static const char shortopts[] = "hw:H:s:d:f:";
	static const option options[] =
	{
		{"help",              no_argument,       nullptr, 'h'},
		{"image-width",       required_argument, nullptr, 'w'},
		{"image-height",      required_argument, nullptr, 'H'},
		{"samples-per-pixel", required_argument, nullptr, 's'},
		{"max-depth",         required_argument, nullptr, 'd'},
		{"vfov",              required_argument, nullptr, 'f'},
		{nullptr,             0,                 nullptr, 0},
	};

	while((c = getopt_long(argc, argv, shortopts, options, nullptr)) != -1)
	{
		switch(c)
		{
			case 'h':
				usage(EXIT_SUCCESS);
				break;

			case 'w':
				image_width = atoi(optarg);
				break;

			case 'H':
				image_height = atoi(optarg);
				break;

			case 's':
				samples_per_pixel = atoi(optarg);
				break;

			case 'd':
				max_depth = atoi(optarg);
				break;

			case 'f':
				vfov = atof(optarg);
				break;

			case '?':
			default:
				usage(EXIT_FAILURE);
		}
	}

	for(int i = optind; i < argc; i++)
		scene = argv[i];
}
