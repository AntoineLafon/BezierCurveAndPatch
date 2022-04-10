#include "BezierPatchMesh.h"

BezierPatchMesh::BezierPatchMesh(unsigned int patchDimension, unsigned int controlPointDimension)
{
	_patchDimension = patchDimension;
	_controlPointDimension = controlPointDimension;
	for (int i = -(_controlPointDimension/2); i < glm::ceil((float)_controlPointDimension /2.0); i++) {
		for(int j = -(_controlPointDimension / 2); j < glm::ceil((float)_controlPointDimension / 2.0); j++){
			glm::vec4 position = glm::vec4( (float)i / (float)_controlPointDimension, 0, (float)j / (float)_controlPointDimension, 1.0f);
			_controlPoints.push_back(position);
		}
	}
	
	//place the middle point bellow the others to form a well
	_controlPoints[(_controlPointDimension * _controlPointDimension) / 2].y = -4.5f;

	generatePlane(_patchDimension);	
}


BezierPatchMesh::~BezierPatchMesh()
{
}


void BezierPatchMesh::generatePlane(int nbPoints)
{
	this->clear();
	_patchDimension = nbPoints;
	MeshVertex* current, * last;
	std::vector<MeshVertex*> temp;
	for (int i = 0; i < nbPoints; i++) {
		for (int j = 0; j < nbPoints; j++) {
			current = addVertex();
			float x = (float)i / (float)(nbPoints - 1);
			float y = (float)j / (float)(nbPoints - 1);
			current->setCoord(glm::vec3(i, 0.0f, j));
			current->setTextureCoord(glm::vec2(x, y));
			if (i != 0 && j != 0) {
				addQuad(current, temp[j], temp[j - 1], last);
				temp[j - 1] = last;
			}
			if (i == 0) {
				temp.push_back(current);
			}
			last = current;
		}
		temp[temp.size() - 1] = last;
		if (i % 100 == 0)
			std::cout << (float)i / (float)nbPoints << std::endl;
	}
}

void BezierPatchMesh::randomize()
{
	_controlPoints.clear();
	for (int i = -(_controlPointDimension / 2); i < glm::ceil((float)_controlPointDimension / 2.0); i++) {
		for (int j = -(_controlPointDimension / 2); j < glm::ceil((float)_controlPointDimension / 2.0); j++) {
			float randomY = (float)rand() / (float)RAND_MAX;
			glm::vec4 position = glm::vec4( (float)i / (float)_controlPointDimension, randomY * 2.0f - 1.0f, (float)j / (float)_controlPointDimension, 1.0f);
			_controlPoints.push_back(position);
		}
	}
}


std::vector<glm::vec4> *BezierPatchMesh::getControlPoints()
{
   return &_controlPoints;
}