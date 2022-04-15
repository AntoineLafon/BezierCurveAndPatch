#include "MeshTriangle.h"

MeshTriangle::MeshTriangle(Mesh *mesh, MeshVertex* v1, MeshVertex* v2, MeshVertex* v3)
{
	_mesh = mesh;
	if (mesh != nullptr)
		mesh->pushTriangle(this);

	MeshHalfEdge *v1v2 = new MeshHalfEdge(mesh, v1, this);
	MeshHalfEdge *v2v3 = new MeshHalfEdge(mesh, v2, this);
	MeshHalfEdge *v3v1 = new MeshHalfEdge(mesh, v3, this);

	v1v2->setNext(v2v3);
	v2v3->setNext(v3v1);
	v3v1->setNext(v1v2);

	_halfEdge = v1v2;

}

MeshTriangle::~MeshTriangle()
{
	delete getHalfEdge()->getNext()->getNext();
	delete getHalfEdge()->getNext();
	delete getHalfEdge();
}

//compute the normal of the surface which will serve to compute the normal the vertices
void MeshTriangle::computeNormal(){
	glm::vec3 v1 = _halfEdge->getorigin()->getCoord();
	glm::vec3 v2 = _halfEdge->getNext()->getorigin()->getCoord();
	glm::vec3 v3 = _halfEdge->getNext()->getNext()->getorigin()->getCoord();

	glm::vec3 ab = v1 - v2;
	glm::vec3 ac = v3 - v2;

	_normal = glm::normalize(glm::cross(ab, ac));
}

MeshHalfEdge* MeshTriangle::getHalfEdge()
{
	return _halfEdge;
}
