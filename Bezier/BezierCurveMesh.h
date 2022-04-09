#pragma once
#include "Mesh/Mesh.h"

class BezierCurveMesh :
    public Mesh
{
	
public:
	BezierCurveMesh();

    void generateMeshFromDistance(float distance); //generate a mesh givin the distance beetween each segment
    void generateMeshFromNumber(int number); //genertae a mesh givin a number of segment
    void regenerateMesh(); //regenerate the mesh with the same parameters used previously (used when a point is added)

    void pushControlPoint(glm::vec2 controlPoint);
    std::vector<glm::vec2>* getControlPoint() { return &_controlPoint; }

	float getSegmentDistance() { return _segmentDistance; }
	int getSegmentNumber() { return _segmentNumber; }

private:
    int _mode;
    float _segmentDistance;
    int _segmentNumber;
    glm::vec2 getBezierPoint(float t, int start, int stop);
    glm::vec2 findPointAtDistance(glm::vec2 point, float *t, float distance); //find the point at a distance from an other point using dichotomie
    std::vector<glm::vec2> _controlPoint;
};

