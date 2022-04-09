#pragma once

#include <QOpenGLWidget>
#include "ui_OpenGLWidget.h"
#include "BezierCurveHandler.h"
#include "BezierPatchHandler.h"
#include "Handler.h"

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_4_Core
{
	Q_OBJECT

public:
	OpenGLWidget(QWidget *parent = Q_NULLPTR);
	~OpenGLWidget();

	void setHandler();

protected:

	void paintGL() override;
	void initializeGL() override;
	void resizeGL(int width, int height) override;

	void mouseMoveEvent(QMouseEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;

private:
	int _mode;
	Ui::OpenGLWidget ui;
	Handler *_handler;
	//using HandlerConstructor = std::function<Handler*(int, int)>;
	//std::vector<HandlerConstructor> _handlerConstructors;
	BezierPatchHandler *_bezierPatchHandler;
	BezierCurveHandler *_bezierCurveHandler;

public slots:
	//bezier curve slots
	void setBezierCurveColorMode();
	void setBezierCurveMeshMode();
	void setBezierCurveSegmentLength(int n);
	void setBezierCurveSegmentNumber(int n);

	//bezier patch slots
	void setBezierPatchColorMode();
	void setBezierPatchMeshNumber();
	void randomize();

	void wireFrame(bool checked);
	void setBezierMode(int mode);
};
