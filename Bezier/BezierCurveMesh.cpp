#include "BezierCurveMesh.h"

BezierCurveMesh::BezierCurveMesh()
{
	_controlPoint.push_back(glm::vec2(-1.0f, -1.0f));
	_controlPoint.push_back(glm::vec2(-1.0f, 1.0f));
	_controlPoint.push_back(glm::vec2(1.0f, -1.0f));
	_controlPoint.push_back(glm::vec2(1.0f, 1.0f));
	generateMeshFromNumber(10);
}

void BezierCurveMesh::generateMeshFromDistance(float distance)
{
	_mode = 1;
	_segmentDistance = distance;
	this->clear();
	MeshVertex *currentBack, *currentFront;
	glm::vec2 position = getBezierPoint(0.0f, 0, _controlPoint.size() - 1);
	MeshVertex *previousBack = addVertex();
	MeshVertex *previousFront = addVertex();
	previousBack->setCoord(glm::vec4(position, -0.2f, 0.0f));
	previousFront->setCoord(glm::vec4(position, 0.2f, 0.0f));
	float i = 0.0f;
	while (i < 1.0f) {
		glm::vec2 newPosition = findPointAtDistance(position, &i, distance);
		position = newPosition;
		currentFront = addVertex();
		currentBack = addVertex();
		currentFront->setCoord(glm::vec4(position, 0.2f, 0.0f));
		currentBack->setCoord(glm::vec4(position, -0.2f, 0.0f));
		currentFront->setTextureCoord(glm::vec2(i, 0.0f));
		currentBack->setTextureCoord(glm::vec2(i, 1.0f));
		addQuad(currentFront, previousFront, previousBack, currentBack);
		previousBack = currentBack;
		previousFront = currentFront;
	}
	this->computeNormal();
}

void BezierCurveMesh::generateMeshFromNumber(int number)
{
	_mode = 0;
	_segmentNumber = number;
	this->clear();
	MeshVertex *previousFront, *previousBack;
	for (int i = 0; i <= number; i++) {
		MeshVertex* currentFront = addVertex();
		MeshVertex* currentBack = addVertex();
		glm::vec2 bezierPoint = getBezierPoint((float)i / (float)(number), 0, _controlPoint.size() - 1);
		currentFront->setCoord(glm::vec4(bezierPoint, 0.2f, 0.0));
		currentBack->setCoord(glm::vec4(bezierPoint, -0.2f, 0.0));
		currentFront->setTextureCoord(glm::vec2((float)i / (float)(number), 0.0f));
		currentBack->setTextureCoord(glm::vec2((float)i / (float)(number), 1.0f));
		if (i != 0) {
			addQuad(currentFront, previousFront, previousBack, currentBack);
		}
		previousFront = currentFront;
		previousBack = currentBack;
	}
	this->computeNormal();
}

void BezierCurveMesh::regenerateMesh()
{
	if(_mode == 0)
		generateMeshFromNumber(_segmentNumber);
	else
		generateMeshFromDistance(_segmentDistance);
}

void BezierCurveMesh::pushControlPoint(glm::vec2 controlPoint)
{
	_controlPoint.push_back(controlPoint);
}

void BezierCurveMesh::randomize()
{
	srand(time(NULL));
	for (int i = 0; i < _controlPoint.size(); i++) {
		_controlPoint[i].x = (float)(rand() % 1000) / 1000.0f * 2.0f - 1.0f;
		_controlPoint[i].y = (float)(rand() % 1000) / 1000.0f * 2.0f - 1.0f;
	}
	regenerateMesh();
}

glm::vec2 BezierCurveMesh::getBezierPoint(float t, int start, int stop)
{
	if (start == stop) return _controlPoint[start];
	glm::vec2 left = getBezierPoint(t, start, stop - 1);
	glm::vec2 right = getBezierPoint(t, start + 1, stop);
	return ((1 - t) * left) + (t * right);
}

glm::vec2 BezierCurveMesh::findPointAtDistance(glm::vec2 startPoint, float* t, float distance)
{
	//if the requested point is above t = 1.0 return the point at 1.0
	glm::vec2 endPoint = getBezierPoint(1.0f, 0, _controlPoint.size() - 1);
	if (glm::distance(startPoint, endPoint) < distance) {
		*t = 1.0f;
		return endPoint;
	}
		
	glm::vec2 point = startPoint;
	float actualDistance = 0.0f;
	float right = 5.0f;
	float left = *t;
	float middle = (left + right) / 2.0f;
	while (glm::abs(actualDistance - distance) > 0.00001f) {
		point = getBezierPoint(middle, 0, _controlPoint.size() - 1);
		actualDistance = glm::distance(point, startPoint);
		if (actualDistance > distance) {
			right = middle;
		}
		else {
			left = middle;
		}
		middle = (left + right) / 2.0f;
	}
	*t = middle;
	return point;
}
