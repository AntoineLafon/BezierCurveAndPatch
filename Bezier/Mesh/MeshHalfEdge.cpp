#include "MeshHalfEdge.h"

MeshHalfEdge::MeshHalfEdge(Mesh* mesh, MeshVertex* origin, MeshTriangle* triangle)
{
    _mesh = mesh;
    if (mesh != nullptr)
        mesh->pushHalfEdge(this);

    //create a link that relies all the triangles connected to the same point
    _origin = origin;
    _neighbor = nullptr;
    if (origin->getHalfEdge() == nullptr)
    {
        origin->setHalfEdge(this);
    }
    else
    {
        _neighbor = origin->getHalfEdge();
        origin->setHalfEdge(this);
    }


    _triangle = triangle;
    _next = nullptr;

}

MeshHalfEdge::~MeshHalfEdge()
{
}

MeshVertex* MeshHalfEdge::getorigin()
{
    return _origin;
}

void MeshHalfEdge::setOrigin(MeshVertex* origin)
{
    _origin = origin;
}

MeshTriangle* MeshHalfEdge::getTriangle()
{
    return _triangle;
}

void MeshHalfEdge::setTriangle(MeshTriangle* triangle)
{
    _triangle = triangle;
}

MeshHalfEdge* MeshHalfEdge::getNext()
{
    return _next;
}

void MeshHalfEdge::setNext(MeshHalfEdge* next)
{
    _next = next;
}

MeshHalfEdge* MeshHalfEdge::getNeighbor()
{
    return _neighbor;
}

void MeshHalfEdge::setNeighbor(MeshHalfEdge* halfEdge)
{
    _neighbor = halfEdge;
}
