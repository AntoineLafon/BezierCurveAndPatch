#pragma once
#include "ShaderProgram.h"
#include "glm/glm.hpp"
#include "BezierCurveMesh.h"
#include "Camera.h"
#include <QtGui/qevent.h>
#include "BezierCurveObject.h"
#include "Handler.h"

class BezierCurveHandler : public Handler
{
public:
	explicit BezierCurveHandler(int width, int height);
	
	void draw() override;
	void resize(int width, int height) override;

	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;

	void setBezierCurveColorMode(int mode);
	void setBezierCurveMeshMode(int mode);
	void regenerateDistanceMesh(float distance);
	void regenerateNumberMesh(int number);
	void randomize();
	
private:
	BezierCurveObject* _bezierCurve;
	Camera* _camera;
	ShaderProgram* _shaderCurve, *_shaderControlPoly;
	int _width, _height;
	
};

