#include "Mesh.h"
#include <iostream>


Mesh::Mesh()
{
}

Mesh::~Mesh()
{
	for(MeshVertex *vertex: _vertexList)
	{
		delete vertex;
	}

	for(MeshTriangle *triangle: _triangleList)
	{
		delete triangle;
	}
}

void Mesh::pushVertex(MeshVertex* vertex)
{
	_vertexList.push_back(vertex);
}

void Mesh::pushTriangle(MeshTriangle* triangle)
{
	_triangleList.push_back(triangle);
}

void Mesh::pushHalfEdge(MeshHalfEdge* halfEdge)
{
	_halfEdgeList.push_back(halfEdge);
}

MeshVertex* Mesh::addVertex()
{
	MeshVertex* vertex = new MeshVertex(this);
	return vertex;
}

MeshTriangle* Mesh::addTriangle(MeshVertex* v1, MeshVertex* v2, MeshVertex* v3)
{
	MeshTriangle* triangle = new MeshTriangle(this, v1, v2, v3);
	return triangle;
}

MeshHalfEdge* Mesh::addHalfEdge(MeshHalfEdge* halfEdge)
{
	return nullptr;
}


void Mesh::addQuad(MeshVertex* v1, MeshVertex* v2, MeshVertex* v3, MeshVertex* v4)
{
	addTriangle(v1, v2, v3);
	addTriangle(v3, v4, v1);
}


std::vector<MeshVertex*>* Mesh::getVertexList()
{
	return &_vertexList;
}

std::vector<MeshHalfEdge*>* Mesh::getHalfEdgeList()
{
	return &_halfEdgeList;
}

std::vector<MeshTriangle*>* Mesh::getTriangleList()
{
	return &_triangleList;
}

std::vector<unsigned int> *Mesh::getIndexList()
{
	if(_index.empty())
		for (MeshTriangle* triangle : _triangleList) {
			MeshHalfEdge* he = triangle->getHalfEdge();
			_index.push_back(he->getorigin()->getNumber());
			he = he->getNext();
			_index.push_back(he->getorigin()->getNumber());
			he = he->getNext();
			_index.push_back(he->getorigin()->getNumber());
		}
	return &_index;
}

int Mesh::getVertexCount()
{
	return _vertexList.size();
}

void Mesh::clear()
{
	for (MeshVertex* vertex : _vertexList)
	{
		delete vertex;
	}
	for (MeshTriangle* triangle : _triangleList)
	{
		delete triangle;
	}
	_vertexList.clear();
	_triangleList.clear();
	_index.clear();
}

void Mesh::computeNormal(){
	for(MeshTriangle *triangle : _triangleList){
		triangle->computeNormal();
	}

	for(MeshVertex *vertex : _vertexList){
		vertex->computeNormal();
	}
}
