#include "BezierPatchHandler.h"

BezierPatchHandler::BezierPatchHandler(int width, int height): Handler(width, height), _width(width), _height(height)
{
	initializeOpenGLFunctions();
	_bezierPatch = new BezierPatchObject();
	_camera = new Camera(_width, _height, glm::vec3(0.0f, 0.0f, 2.0f));
	_shaderCurve = new ShaderProgram("bezierSurfaceVertex.glsl", "fragment.glsl");
	_shaderControlPoly = new ShaderProgram("vertexControlPoly.glsl", "fragmentControlPoly.glsl");
}

void BezierPatchHandler::draw()
{
	if (this->_wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	_bezierPatch->drawCurve(_shaderCurve, _camera);
	_bezierPatch->drawControlPoly(_shaderControlPoly, _camera);
}

void BezierPatchHandler::resize(int width, int height)
{
	_width = width;
	_height = height;
	_camera->resize((float)width, (float)height);
}

void BezierPatchHandler::mouseMoveEvent(QMouseEvent* event)
{
	_camera->mouseMoveEvent(MouseButton::RightClick, event->x(), event->y());
}

void BezierPatchHandler::mousePressEvent(QMouseEvent* event)
{
	_camera->mousePressEvent(MouseButton::RightClick, event->x(), event->y());
}

void BezierPatchHandler::mouseReleaseEvent(QMouseEvent* event)
{
	_camera->mouseReleaseEvent(MouseButton::RightClick, event->x(), event->y());
}

void BezierPatchHandler::wheelEvent(QWheelEvent* event)
{
	_camera->wheelEvent(event->angleDelta().y(), event->angleDelta().x());
}

void BezierPatchHandler::setBezierPatchColorMode(int mode)
{
	_bezierPatch->setColorMode(mode);
}

void BezierPatchHandler::setBezierPatchNumber(int number)
{
	_bezierPatch->regeneratePatch(number);
}
