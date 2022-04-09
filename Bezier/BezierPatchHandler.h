#pragma once
#include "BezierCurveMesh.h"
#include "Camera.h"
#include <QtGui/qevent.h>
#include "BezierPatchObject.h"
#include "Handler.h"
class BezierPatchHandler : public Handler
{
public:
	explicit BezierPatchHandler(int width, int height);

	void draw() override;
	void resize(int width, int height) override;

	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;

	void setBezierPatchColorMode(int mode);
	void setBezierPatchNumber(int number);
	void randomize() { _bezierPatch->randomize(); }

private:
	BezierPatchObject* _bezierPatch;
	Camera* _camera;
	ShaderProgram* _shaderCurve, * _shaderControlPoly;
	int _width, _height;
};

