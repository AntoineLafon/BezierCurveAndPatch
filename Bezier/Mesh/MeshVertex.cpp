#include "MeshVertex.h"

MeshVertex::MeshVertex(Mesh *mesh)
{
	_mesh = mesh;
	_number = 0;
	if (mesh != nullptr) {
		_number = mesh->getVertexCount();
		mesh->pushVertex(this);
	}

	_halfEdge = nullptr;

	_attribute.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)); //coordinate
	_attribute.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)); //color
	_attribute.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)); //normal
	_attribute.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)); //texture
}

MeshVertex::~MeshVertex()
{

}

int MeshVertex::getTriangleNumber(){
	MeshHalfEdge *temp = _halfEdge;
	int s = 0;
	while(temp!=nullptr){
		s++;
		temp = temp->getNeighbor();
	}
	return s;
}

std::vector<MeshTriangle*> MeshVertex::getConnectedTriangles(){
	std::vector<MeshTriangle*> triangles;
	MeshHalfEdge *temp = _halfEdge;
	while(temp!=nullptr){
		triangles.push_back(temp->getTriangle());
		temp = temp->getNeighbor();
	}
	return triangles;
}

void MeshVertex::computeNormal(){
	std::vector<MeshTriangle*> triangles = getConnectedTriangles();
	glm::vec3 normal = glm::vec3(0.0f, 0.0f, 0.0f);
	for(MeshTriangle *triangle : triangles){
		normal += triangle->getNormal();
	}
	normal/=triangles.size();
	glm::normalize(normal);
	setNormal(normal);
}

MeshHalfEdge* MeshVertex::getHalfEdge()
{
	return _halfEdge;
}

void MeshVertex::setHalfEdge(MeshHalfEdge* halfEdge)
{
	_halfEdge = halfEdge;
}

Mesh* MeshVertex::getMesh()
{
	return _mesh;
}

void MeshVertex::setMesh(Mesh* mesh)
{
	_mesh = mesh;
}

glm::vec3 MeshVertex::getCoord()
{
	return glm::vec3(_attribute[VERTEX_COORD]);
}

void MeshVertex::setCoord(glm::vec3 coord)
{
	_attribute[VERTEX_COORD] = glm::vec4(coord, 0.0f);
}

glm::vec4 MeshVertex::getColor()
{
	return _attribute[VERTEX_COLOR];
}

void MeshVertex::setColor(glm::vec4 color)
{
	_attribute[VERTEX_COLOR] = color;
}

glm::vec3 MeshVertex::getNormal()
{
	return glm::vec3(_attribute[VERTEX_NORM]);
}

void MeshVertex::setNormal(glm::vec3 normal)
{
	_attribute[VERTEX_NORM] = glm::vec4(normal, 0.0f);
}

glm::vec2 MeshVertex::getTextureCoord()
{
	return glm::vec2(_attribute[VERTEX_TEX]);
}

void MeshVertex::setTextureCoord(glm::vec2 texCoord)
{
	_attribute[VERTEX_TEX] = glm::vec4(texCoord, 0.0f, 0.0f);
}

glm::vec4 MeshVertex::getAttrib(unsigned int attrib)
{
	return glm::vec4(_attribute[attrib]);
}

int MeshVertex::getNumber()
{
	return _number;
}

void MeshVertex::setNumber(int n)
{
	_number = n;
}
