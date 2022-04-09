#pragma once
#include "Mesh/Mesh.h"
#include <iostream>

#define PATCH_SIZE 7
class BezierPatchMesh :
    public Mesh
{
public:
		
	BezierPatchMesh(int nbPoints);
    ~BezierPatchMesh();
    void generatePlane(int nbPoints);
	void randomize();
	std::vector<glm::vec4>* getControlPoints();

private:
    std::vector<glm::vec4> _controlPoints;
	unsigned int _nbPoints;
};


