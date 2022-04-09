#include "BezierCurveObject.h"

BezierCurveObject::BezierCurveObject()
{
	initializeOpenGLFunctions();
	_bezierCurveMesh = new BezierCurveMesh();
	_number = 10;
	_distance = 0.1f;
	_lightPos[0] = glm::vec3(5.0f, 5.0f, 5.0f);
	_lightPos[1] = glm::vec3(5.0f, 5.0f, 0.0f);
	_lightPos[2] = glm::vec3(-5.0f, 5.0f, 0.0f);

	genControlPolyBuffers();
	genBezierCurveBuffers();
	
	updateBezierCurveBuffers();
	updateControlPolyBuffers();
}

void BezierCurveObject::drawCurve(ShaderProgram* shaderProgram, Camera* camera)
{
	shaderProgram->use();
	shaderProgram->setInt("mode", _colorMode);
	shaderProgram->setMat4("projection", camera->getProjection());
	shaderProgram->setMat4("view", camera->getView());
	shaderProgram->setVec3("cameraPosition", camera->getPosition());
	sendLights(shaderProgram);
	glBindVertexArray(_bezierVAO);
	glDrawElements(GL_TRIANGLES, _nbBezierIndices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void BezierCurveObject::drawControlPoly(ShaderProgram* shaderProgram, Camera* camera)
{
	shaderProgram->use();
	shaderProgram->setMat4("projection", camera->getProjection());
	shaderProgram->setMat4("view", camera->getView());
	glBindVertexArray(_controlVAO);
	glDrawArrays(GL_LINE_STRIP, 0, _bezierCurveMesh->getControlPoint()->size());
	glPointSize(6);
	glDrawArrays(GL_POINTS, 0, _bezierCurveMesh->getControlPoint()->size());
	glBindVertexArray(0);
}

void BezierCurveObject::regenerateDistanceMesh(float distance)
{
	_bezierCurveMesh->generateMeshFromDistance(distance);
	_distance = distance;
	updateBezierCurveBuffers();
}

void BezierCurveObject::regenerateNumberMesh(int number)
{
	_bezierCurveMesh->generateMeshFromNumber(number);
	_number = number;
	updateBezierCurveBuffers();
}

void BezierCurveObject::genBezierCurveBuffers()
{
	glGenBuffers(1, &_bezierVBO);
	glGenBuffers(1, &_bezierEBO);
	glGenBuffers(1, &_bezierNBO);
	glGenBuffers(1, &_bezierTBO);
	glGenVertexArrays(1, &_bezierVAO);	

	glBindVertexArray(_bezierVAO);
		glBindBuffer(GL_ARRAY_BUFFER, _bezierVBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		
		glBindBuffer(GL_ARRAY_BUFFER, _bezierNBO);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, _bezierTBO);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(2);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bezierEBO);
	glBindVertexArray(0);
	
}

void BezierCurveObject::genControlPolyBuffers()
{
	glGenBuffers(1, &_controlVBO);
	glGenBuffers(1, &_controlEBO);
	glGenVertexArrays(1, &_controlVAO);

	glBindVertexArray(_controlVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _controlVBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _controlEBO);
	glBindVertexArray(0);
}

void BezierCurveObject::updateBezierCurveBuffers()
{
	std::vector<MeshVertex*>* vertices = _bezierCurveMesh->getVertexList();
	std::vector<glm::vec3> data;
	std::vector<glm::vec4> normals;
	std::vector<glm::vec2> texCoords;
	for (MeshVertex* v : *vertices) {
		data.push_back(v->getAttrib(VERTEX_COORD));
		normals.push_back(v->getAttrib(VERTEX_NORM));
		texCoords.push_back(v->getAttrib(VERTEX_TEX));
	}

	std::vector<unsigned int> index;
	for (MeshTriangle* triangle : *_bezierCurveMesh->getTriangleList()) {
		MeshHalfEdge* he = triangle->getHalfEdge();
		index.push_back(he->getorigin()->getNumber());
		he = he->getNext();
		index.push_back(he->getorigin()->getNumber());
		he = he->getNext();
		index.push_back(he->getorigin()->getNumber());
	}
	_nbBezierIndices = index.size();

	glBindBuffer(GL_ARRAY_BUFFER, _bezierVBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, _bezierNBO);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec4), normals.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, _bezierTBO);
	glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(glm::vec2), texCoords.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bezierEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(unsigned int), index.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void BezierCurveObject::updateControlPolyBuffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, _controlVBO);
	glBufferData(GL_ARRAY_BUFFER, _bezierCurveMesh->getControlPoint()->size() * sizeof(glm::vec2), _bezierCurveMesh->getControlPoint()->data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BezierCurveObject::sendLights(ShaderProgram* shaderProgram)
{
	for (int i = 0; i < 3; i++) {
		shaderProgram->setVec3("lightPosition[" + std::to_string(i) + "]", _lightPos[i]);
	}
}