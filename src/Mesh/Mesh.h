#pragma once
#include <vector>

class Mesh;
class MeshTriangle;
class MeshVertex;
class MeshHalfEdge;

#include "MeshVertex.h"
#include "MeshTriangle.h"
#include "MeshHalfEdge.h"

class Mesh
{

public:

	Mesh();
	~Mesh();
	void pushVertex(MeshVertex* vertex);
	void pushTriangle(MeshTriangle *triangle);
	void pushHalfEdge(MeshHalfEdge* halfEdge);

	MeshVertex* addVertex();
	MeshTriangle* addTriangle(MeshVertex* v1, MeshVertex* v2, MeshVertex* v3);
	MeshHalfEdge* addHalfEdge(MeshHalfEdge *halfEdge);
	void addQuad(MeshVertex* v1, MeshVertex* v2, MeshVertex* v3, MeshVertex* v4);

	std::vector<MeshVertex*> *getVertexList();
	std::vector<MeshHalfEdge*> *getHalfEdgeList();
	std::vector<MeshTriangle*> *getTriangleList();
	std::vector<unsigned int> *getIndexList();

	void clear();
	void computeNormal();
	int getVertexCount();

private:

	std::vector<MeshVertex*> _vertexList;
	std::vector<MeshHalfEdge*> _halfEdgeList;
	std::vector<MeshTriangle*> _triangleList;
	std::vector<unsigned int> _index;
};
