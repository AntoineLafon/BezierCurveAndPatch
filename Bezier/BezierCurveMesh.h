#pragma once
#include "Mesh/Mesh.h"
#include <chrono>
#include <ctime>
#include <iostream>

class BezierCurveMesh :
    public Mesh
{
public:
	BezierCurveMesh();

	//two different mesh generation
    void generateMeshFromDistance(float distance);
    void generateMeshFromNumber(int number);
	
    //regenerate the mesh with the same parameters previously used
    void regenerateMesh();

    void pushControlPoint(glm::vec2 controlPoint); 
    void randomize(); 
	
	//getters
    std::vector<glm::vec2>* getControlPoint() { return &_controlPoint; }
	float getSegmentDistance() { return _segmentDistance; }
	int getSegmentNumber() { return _segmentNumber; }

private:
	
    //recursive function to get a point on the bezier curve
    glm::vec2 getBezierPoint(float t, int start, int stop); 
	
    //find the point at a distance from an other point using dichotomie
    glm::vec2 findPointAtDistance(glm::vec2 point, float *t, float distance); 

    std::vector<glm::vec2> _controlPoint;
    int _mode;//0 = number, 1 = distance
    float _segmentDistance;
    int _segmentNumber;
};

