#include "BezierPatchMesh.h"

BezierPatchMesh::BezierPatchMesh(int nbPoints)
{
	_nbPoints = nbPoints;
	for (int i = -(PATCH_SIZE/2); i < glm::ceil((float)PATCH_SIZE/2.0); i++) {
		for(int j = -(PATCH_SIZE / 2); j < glm::ceil((float)PATCH_SIZE / 2.0); j++){
			glm::vec4 position = glm::vec4( (float)i / (float)PATCH_SIZE, 0, (float)j / (float)PATCH_SIZE, 1.0f);
			_controlPoints.push_back(position);
		}
	}
	_controlPoints[24].y = -4.5f;

	generatePlane(_nbPoints);	
}


BezierPatchMesh::~BezierPatchMesh()
{
}


void BezierPatchMesh::generatePlane(int nbPoints)
{
	this->clear();
	_nbPoints = nbPoints;
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
	for (int i = -(PATCH_SIZE / 2); i < glm::ceil((float)PATCH_SIZE / 2.0); i++) {
		for (int j = -(PATCH_SIZE / 2); j < glm::ceil((float)PATCH_SIZE / 2.0); j++) {
			float randomY = (float)rand() / (float)RAND_MAX;
			glm::vec4 position = glm::vec4( (float)i / (float)PATCH_SIZE, randomY, (float)j / (float)PATCH_SIZE, 1.0f);
			_controlPoints.push_back(position);
		}
	}
}


std::vector<glm::vec4> *BezierPatchMesh::getControlPoints()
{
   return &_controlPoints;
}