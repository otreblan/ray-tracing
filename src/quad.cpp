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

#include "quad.hpp"

quad::quad(glm::vec3 Q, glm::vec3 u, glm::vec3 v, std::shared_ptr<material> m):
	Q(std::move(Q)),
	u(std::move(u)),
	v(std::move(v)),
	mat_ptr(std::move(m)),
	normal(glm::normalize(glm::cross(u, v))),
	D(glm::dot(normal, Q))
{
	glm::vec3 n = glm::cross(u,v);

	w = n/glm::dot(n,n);
}

bool quad::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
	float denom = glm::dot(normal, r.get_direction());

	// No hit if the ray is parallel to the plane.
	if (fabs(denom) < 1e-8)
		return false;

	// Return false if the hit point parameter t is outside the ray interval.
	float t = (D - glm::dot(normal, r.get_origin())) / denom;
	if (!(t_min <= t && t <= t_max))
		return false;

	glm::vec3 intersection = r.at(t);

	if(!in_quad(intersection))
		return false;

	// Ray hits the 2D shape; set the rest of the hit record and return true.
	rec.t       = t;
	rec.p       = intersection;
	rec.mat_ptr = mat_ptr;
	rec.normal  = glm::faceforward(normal, normal, r.get_direction());

	return true;
}

bool quad::in_quad(glm::vec3 intersection) const
{
	glm::vec3 planar_hitpt_vector = intersection - Q;
	float alpha = glm::dot(w, glm::cross(planar_hitpt_vector, v));
	float beta  = glm::dot(w, glm::cross(u, planar_hitpt_vector));

	// TODO: UV mapping

	return 0 <= alpha && alpha <= 1 && 0 <= beta && beta <= 1;
}
