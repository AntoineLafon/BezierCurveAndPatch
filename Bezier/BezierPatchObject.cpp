#include "BezierPatchObject.h"

BezierPatchObject::BezierPatchObject()
{
	start = std::chrono::system_clock::now();
	unsigned int patchDimension = 1000;
	unsigned int controlDimension = 7;
	initializeOpenGLFunctions();
	_bezierPatchMesh = new BezierPatchMesh(patchDimension, controlDimension);
	_bezierSurfaceTexture = new BezierSurfaceTexture();
	_bezierSurfaceTexture->setBezierSize(patchDimension);
	_bezierSurfaceTexture->setControlPoint(controlDimension, _bezierPatchMesh->getControlPoints());
	_bezierSurfaceTexture->computeBezierPoints();
	_bezierSurfaceTexture->computeNormal();

	_lightPos[0] = glm::vec3(5.0f, 5.0f, 5.0f);
	_lightPos[1] = glm::vec3(5.0f, 5.0f, 0.0f);
	_lightPos[2] = glm::vec3(-5.0f, 5.0f, 0.0f);

	genBezierPatchBuffers();
	genControlPolyBuffers();
	updateBezierPatchBuffers();
	updateControlPolyBuffers();

	regeneratePatch(10);
	
	//_bezierSurfaceTexture->debug();
}

void BezierPatchObject::drawCurve(ShaderProgram* shaderProgram, Camera* camera)
{
	glBindVertexArray(_bezierVAO);
	shaderProgram->use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _bezierSurfaceTexture->getBezierTexture());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _bezierSurfaceTexture->getNormalTexture());
	sendLights(shaderProgram);
	shaderProgram->setInt("bezierTexture", 0);
	shaderProgram->setInt("normalTexture", 1);
	shaderProgram->setInt("mode", _colorMode);
	shaderProgram->setMat4("projection", camera->getProjection());
	shaderProgram->setMat4("view", camera->getView());
	shaderProgram->setVec3("cameraPosition", camera->getPosition());
	glDrawElements(GL_TRIANGLES, _nbBezierIndices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void BezierPatchObject::drawControlPoly(ShaderProgram* shaderProgram, Camera* camera)
{
	glBindVertexArray(_controlVAO);
	shaderProgram->use();
	shaderProgram->setMat4("projection", camera->getProjection());
	shaderProgram->setMat4("view", camera->getView());
	glPointSize(8);
	glDrawArrays(GL_POINTS, 0, _bezierPatchMesh->getControlPoints()->size());
	glBindVertexArray(0);	
}

void BezierPatchObject::regeneratePatch(int newSize)
{
	_bezierPatchMesh->generatePlane(newSize);
	_bezierSurfaceTexture->setBezierSize(newSize);
	_bezierSurfaceTexture->computeBezierPoints();
	_bezierSurfaceTexture->computeNormal();
	updateBezierPatchBuffers();	
}

void BezierPatchObject::randomize()
{
	_bezierPatchMesh->randomize();
	updateControlPolyBuffers();
	_bezierSurfaceTexture->setControlPoint(_bezierPatchMesh->getControlPointDimension(), _bezierPatchMesh->getControlPoints());
	_bezierSurfaceTexture->computeBezierPoints();
	_bezierSurfaceTexture->computeNormal();

}

void BezierPatchObject::sendLights(ShaderProgram* shaderProgram)
{
	for (int i = 0; i < 3; i++) {
		shaderProgram->setVec3("lightPosition[" + std::to_string(i) + "]", _lightPos[i]);
	}
}

void BezierPatchObject::genBezierPatchBuffers()
{
	glGenBuffers(1, &_bezierVBO); //vertex buffer object
	glGenBuffers(1, &_bezierTBO); //texture buffer object
	glGenBuffers(1, &_bezierEBO); //element buffer object
	glGenVertexArrays(1, &_bezierVAO); //vertex array object

	glBindVertexArray(_bezierVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _bezierVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _bezierTBO);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bezierEBO);
	glBindVertexArray(0);
}

void BezierPatchObject::genControlPolyBuffers()
{
	glGenBuffers(1, &_controlVBO);
	glGenVertexArrays(1, &_controlVAO);

	glBindVertexArray(_controlVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _controlVBO);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void BezierPatchObject::updateBezierPatchBuffers()
{
	std::vector<MeshVertex*>* vertices = _bezierPatchMesh->getVertexList();
	std::vector<glm::vec3> data;
	std::vector<glm::vec2> uv;
	for (MeshVertex* v : *vertices) {
		data.push_back(v->getAttrib(VERTEX_COORD));
		uv.push_back(glm::vec2(v->getAttrib(VERTEX_TEX)));
	}
	std::vector<unsigned int> *index = _bezierPatchMesh->getIndexList();
	_nbBezierIndices = index->size();

	glBindBuffer(GL_ARRAY_BUFFER, _bezierVBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, _bezierTBO);
	glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof(glm::vec2), uv.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bezierEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index->size() * sizeof(unsigned int), index->data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
}

void BezierPatchObject::updateControlPolyBuffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, _controlVBO);
	glBufferData(GL_ARRAY_BUFFER, _bezierPatchMesh->getControlPoints()->size() * sizeof(glm::vec4), _bezierPatchMesh->getControlPoints()->data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BezierPatchObject::animate()
{
	n.clear();
	int dimension = _bezierPatchMesh->getControlPointDimension();
	for(int i = -(dimension / 2); i < glm::ceil((float)dimension / 2.0f); i++) {
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		float ms = elapsed_seconds.count();
		float value = 0.5f * glm::cos((ms + (i * 1.0f)));
		for(int j = -(dimension / 2); j < glm::ceil((float)dimension / 2.0f); j++) {
			n.push_back(glm::vec4((float)i / dimension, value , (float)j / dimension, 1.0f));
		}
	}
	_bezierPatchMesh->setControlPoints(n);
	updateControlPolyBuffers();
	_bezierSurfaceTexture->setControlPoint(_bezierPatchMesh->getControlPointDimension(), &n);
	_bezierSurfaceTexture->computeBezierPoints();
	_bezierSurfaceTexture->computeNormal();		
}
