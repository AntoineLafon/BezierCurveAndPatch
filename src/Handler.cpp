#include "Handler.h"

Handler::Handler(int width, int height)
{
}

void Handler::draw()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	if (_wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Handler::resize(int width, int height)
{
}

void Handler::mouseMoveEvent(QMouseEvent* event)
{
}

void Handler::mousePressEvent(QMouseEvent* event)
{
}

void Handler::mouseReleaseEvent(QMouseEvent* event)
{
}

void Handler::wheelEvent(QWheelEvent* event)
{
}

void Handler::wireFrame(bool checked)
{
	_wireframe = checked;
}

void Handler::controlPoints(bool checked)
{
	_controlPoints = checked;
}
