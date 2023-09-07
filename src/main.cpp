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

#include <glm/gtx/rotate_vector.hpp>
#include <glm/vec3.hpp>

#include "arguments.hpp"
#include "rtweekend.hpp"
#include "scene.hpp"

int main(int argc, char** argv)
{
	RTCDevice device = rtcNewDevice(nullptr);

	if(!device)
		return EXIT_FAILURE;

	rtcSetDeviceErrorFunction(device, errorFunction, nullptr);

	arguments args(argc, argv);

	// TODO: Render from main_scene
	scene main_scene(device, args);

	main_scene.render();

	rtcReleaseDevice(device);
	return EXIT_SUCCESS;
}
