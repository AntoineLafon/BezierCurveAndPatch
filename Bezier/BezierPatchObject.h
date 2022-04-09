#pragma once
#include "ShaderProgram.h"
#include "glm/glm.hpp"
#include "BezierPatchMesh.h"
#include "Camera.h"
#include "BezierSurfaceTexture.h"

class BezierPatchObject : protected QOpenGLFunctions_4_4_Core
{
public:
	BezierPatchObject();
	void drawCurve(ShaderProgram* shaderProgram, Camera* camera);
	void drawControlPoly(ShaderProgram* shaderProgram, Camera* camera);
	void regeneratePatch(int newSize);

	void setColorMode(int mode) { _colorMode = mode; }
	void randomize();

private:

	void sendLights(ShaderProgram* shaderProgram);
	void genBezierPatchBuffers();
	void genControlPolyBuffers();
	void updateBezierPatchBuffers();
	void updateControlPolyBuffers();

	BezierPatchMesh* _bezierPatchMesh;
	BezierSurfaceTexture *_bezierSurfaceTexture;
	int _nbBezierIndices;
	int _colorMode = 1;
	glm::vec3 _lightPos[3];
	
	unsigned int _bezierVAO, _bezierVBO, _bezierEBO, _bezierTBO;
	unsigned int _controlVAO, _controlVBO;
	
	

};
