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

#include "mesh.hpp"

mesh::mesh(unsigned id, std::shared_ptr<material> m):
	id(id),
	mat_ptr(m)
{}

bool mesh::hit(const ray&, float, float, hit_record& rec) const
{
	// TODO: refactor this
	rec.mat_ptr = mat_ptr;
	rec.t = rec.get().ray.tfar;
	rec.p = ray(rec.get().ray).at(rec.t);
	//rec.normal = rec.get_normal();

	rec.front_face = glm::dot(rec.get_direction(), rec.normal) < 0;
	rec.normal = rec.front_face ? rec.normal : -rec.normal;

	return true;
}
