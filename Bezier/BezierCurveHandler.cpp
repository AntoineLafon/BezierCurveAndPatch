#include "BezierCurveHandler.h"

BezierCurveHandler::BezierCurveHandler(int width, int height) : Handler(width, height), _width(width), _height(height)
{
	initializeOpenGLFunctions();	
	_bezierCurve = new BezierCurveObject();
	_camera = new Camera(_width, _height, glm::vec3(0.0f, 0.0f, 5.0f));
	_shaderCurve = new ShaderProgram("vertexBezierCurve.glsl", "fragmentBezierCurve.glsl");
	_shaderControlPoly = new ShaderProgram("vertexControlPoly.glsl", "fragmentControlPoly.glsl");
}

void BezierCurveHandler::draw()
{	
	if (this->_wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	_bezierCurve->drawCurve(_shaderCurve, _camera);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if(this->_controlPoints)
		_bezierCurve->drawControlPoly(_shaderControlPoly, _camera);
}

void BezierCurveHandler::resize(int width, int height)
{
	_width = width;
	_height = height;
	_camera->resize((float)width, (float)height);
}

void BezierCurveHandler::mouseMoveEvent(QMouseEvent* event)
{
	_camera->mouseMoveEvent(MouseButton::RightClick, event->x(), event->y());
}

void BezierCurveHandler::mousePressEvent(QMouseEvent* event)
{
	_camera->mousePressEvent(MouseButton::RightClick, event->x(), event->y());
}

void BezierCurveHandler::mouseReleaseEvent(QMouseEvent* event)
{
	_camera->mouseReleaseEvent(MouseButton::RightClick, event->x(), event->y());
}

void BezierCurveHandler::wheelEvent(QWheelEvent* event)
{
	_camera->wheelEvent(event->angleDelta().y(), event->angleDelta().x());
}

void BezierCurveHandler::setBezierCurveColorMode(int mode)
{
	_bezierCurve->setColorMode(mode);
}

void BezierCurveHandler::setBezierCurveMeshMode(int mode)
{
	if (mode == 0) {
		_bezierCurve->regenerateNumberMesh(_bezierCurve->getNumber());
	}
	else {
		_bezierCurve->regenerateDistanceMesh(_bezierCurve->getDistance());
	}
}

void BezierCurveHandler::regenerateDistanceMesh(float distance)
{
	_bezierCurve->regenerateDistanceMesh(distance);
}

void BezierCurveHandler::regenerateNumberMesh(int number)
{
	_bezierCurve->regenerateNumberMesh(number);
}

void BezierCurveHandler::randomize()
{
	_bezierCurve->randomize();
}

