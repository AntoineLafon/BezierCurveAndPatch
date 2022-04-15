#pragma once
#include "Mesh.h"
#include "MeshTriangle.h"
#include "MeshVertex.h"

class MeshHalfEdge
{

public:

	MeshHalfEdge(Mesh* mesh, MeshVertex* origin, MeshTriangle* triangle);
	~MeshHalfEdge();
		
	MeshVertex* getorigin();
	void setOrigin(MeshVertex* origin);

	MeshTriangle* getTriangle();
	void setTriangle(MeshTriangle* triangle);

	MeshHalfEdge* getNext();
	void setNext(MeshHalfEdge* next);

	MeshHalfEdge* getNeighbor();
	void setNeighbor(MeshHalfEdge *halfEdge);

private:

	Mesh* _mesh;
	MeshTriangle* _triangle;
	MeshHalfEdge* _next;

	//link to a halfedge belonging to the neighbor triangle
	MeshHalfEdge* _neighbor;
	MeshVertex* _origin;
};
