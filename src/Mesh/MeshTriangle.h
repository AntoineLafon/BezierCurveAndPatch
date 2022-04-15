#pragma once

#include <glm/glm.hpp>

#include "Mesh.h"
#include "MeshHalfEdge.h"
#include "MeshVertex.h"

class MeshTriangle
{
public:

	MeshTriangle(Mesh *mesh, MeshVertex* v1, MeshVertex* v2, MeshVertex* v3);
	~MeshTriangle();
	void computeNormal();
	glm::vec3 getNormal(){ return _normal; }
	MeshHalfEdge* getHalfEdge();


private:

	Mesh* _mesh;
	MeshHalfEdge* _halfEdge;
	glm::vec3 _normal;

};
