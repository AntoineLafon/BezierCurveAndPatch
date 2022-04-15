#pragma once
#include "ShaderProgram.h"
#include "glm/glm.hpp"
#include "BezierCurveMesh.h"
#include "Camera.h"

class BezierCurveObject : protected QOpenGLFunctions_4_4_Core
{
public:
	BezierCurveObject();
	void drawCurve(ShaderProgram *shaderProgram, Camera *camera);
	void drawControlPoly(ShaderProgram *shaderProgram, Camera *camera);

	//functions used by QT for interactions
	void regenerateDistanceMesh(float distance);
	void regenerateNumberMesh(int number);
	void setColorMode(int mode) { _colorMode = mode; }
	void randomize();
	
	float getDistance(){ return _distance; }
	int getNumber(){ return _number; }
	

private:
	//buffers generations and updating
	void genBezierCurveBuffers();
	void genControlPolyBuffers();
	void updateBezierCurveBuffers();
	void updateControlPolyBuffers();
	
	void sendLights(ShaderProgram* shaderProgram);

	BezierCurveMesh* _bezierCurveMesh;
	glm::vec3 _lightPos[3];
	int _nbBezierIndices;
	int _colorMode = 1;
	int _number;
	float _distance;
	unsigned int _bezierVAO, _bezierVBO, _bezierTBO, _bezierNBO, _bezierEBO;
	unsigned int _controlVAO, _controlVBO, _controlEBO;
	
};

