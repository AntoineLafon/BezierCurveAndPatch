#pragma once
#include <QMouseEvent>
#include <QOpenGLFunctions_4_4_Core>

class Handler : public QOpenGLFunctions_4_4_Core
{
public:
	explicit Handler(int width, int height);

	virtual void draw();
	virtual void resize(int width, int height);

	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void wheelEvent(QWheelEvent* event);
	void wireFrame(bool checked);
	void controlPoints(bool checked);

protected:
	bool _wireframe = false;
	bool _controlPoints = false;
	int _width, _height;
};

