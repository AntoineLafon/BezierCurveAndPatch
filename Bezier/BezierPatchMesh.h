#pragma once
#include "Mesh/Mesh.h"
#include <iostream>

/*
* This class only generate a plane, the bezier patch calculation
* is done by the class BezierSurfaceTexture which do parallel calculation
* using compute shaders
*/


class BezierPatchMesh :
    public Mesh
{
public:
		
	BezierPatchMesh(unsigned int patchDimension, unsigned int controlPointDimension);
    ~BezierPatchMesh();
    void generatePlane(int nbPoints);
	void randomize();
	std::vector<glm::vec4>* getControlPoints();
	void setControlPoints(std::vector<glm::vec4> newControlPoints){ _controlPoints = newControlPoints; }
	unsigned int getPatchimension() { return _patchDimension; }
	unsigned int getControlPointDimension() { return _controlPointDimension; }

private:
    std::vector<glm::vec4> _controlPoints;
	unsigned int _patchDimension, _controlPointDimension;
};


