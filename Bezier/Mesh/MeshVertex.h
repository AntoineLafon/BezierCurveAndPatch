#pragma once
#include <vector>
#include "MeshHalfEdge.h"
#include <glm/glm.hpp>
#include "Mesh.h"


/*
Attributs
0 => Coord
1 => couleur
2 => normale
*/

#define VERTEX_COORD 0
#define VERTEX_COLOR 1
#define VERTEX_NORM 2
#define VERTEX_TEX 3


class MeshVertex
{
public:

	MeshVertex(Mesh *mesh);
	~MeshVertex();

	MeshHalfEdge* getHalfEdge();
	void setHalfEdge(MeshHalfEdge* halfEdge);

	Mesh* getMesh();
	void setMesh(Mesh* mesh);

	glm::vec3 getCoord();
	void setCoord(glm::vec3 coord);

	glm::vec4 getColor();
	void setColor(glm::vec4 color);

	glm::vec3 getNormal();
	void setNormal(glm::vec3 normal);
	
	glm::vec2 getTextureCoord();
	void setTextureCoord(glm::vec2 texCoord);

	glm::vec4 getAttrib(unsigned int attrib);

	int getTriangleNumber();


	std::vector<MeshTriangle*> getConnectedTriangles();

	int getNumber();
	void setNumber(int n);

	void computeNormal();

private:

	Mesh* _mesh;
	MeshHalfEdge* _halfEdge;
	std::vector<glm::vec4> _attribute;
	int _number;
};
