#include "OpenGLWidget.h"
#include <QRadioButton>
#include <QSlider>
#include <QSpinBox>

OpenGLWidget::OpenGLWidget(QWidget *parent)
	: QOpenGLWidget(parent)
{
	ui.setupUi(this);
	_mode = 0;
}

OpenGLWidget::~OpenGLWidget()
{
}

void OpenGLWidget::setHandler()
{
}

void OpenGLWidget::paintGL()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	_handler->draw();
}

void OpenGLWidget::initializeGL()
{
	initializeOpenGLFunctions();	
	_bezierPatchHandler = new BezierPatchHandler(this->width(), this->height());
	_bezierCurveHandler = new BezierCurveHandler(this->width(), this->height());
	_handler = _bezierCurveHandler;
	update();
}

void OpenGLWidget::resizeGL(int width, int height)
{
	_handler->resize(width, height);
	glViewport(0, 0, width, height);
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent* event)
{
	_handler->mouseMoveEvent(event);
	update();
}

void OpenGLWidget::mousePressEvent(QMouseEvent* event)
{
	_handler->mousePressEvent(event);
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent* event)
{
	_handler->mouseReleaseEvent(event);
}

void OpenGLWidget::wheelEvent(QWheelEvent* event)
{
	_handler->wheelEvent(event);
	update();
}

void OpenGLWidget::setBezierCurveColorMode()
{	
	QRadioButton* radioButton = qobject_cast<QRadioButton*>(sender());
	if (radioButton->text() == "Normal Color") {
		_bezierCurveHandler->setBezierCurveColorMode(0);
	}else if (radioButton->text() == "Position Color"){
		_bezierCurveHandler->setBezierCurveColorMode(1);
	}
	else if (radioButton->text() == "UV Color") {
		_bezierCurveHandler->setBezierCurveColorMode(2);
	}
	update();
}



void OpenGLWidget::setBezierCurveMeshMode()
{
	QRadioButton* radioButton = qobject_cast<QRadioButton*>(sender());
	if(radioButton->text() == "Segment Number")
		_bezierCurveHandler->setBezierCurveMeshMode(0);
	else
		_bezierCurveHandler->setBezierCurveMeshMode(1);
	update();
}

void OpenGLWidget::setBezierCurveSegmentLength(int n)
{
	QSlider* slider = qobject_cast<QSlider*>(sender());
	_bezierCurveHandler->regenerateDistanceMesh((float)n / (float)slider->maximum());
	update();
}

void OpenGLWidget::setBezierCurveSegmentNumber(int n)
{
	_bezierCurveHandler->regenerateNumberMesh(n);
	update();
}

void OpenGLWidget::setBezierPatchColorMode()
{
	QRadioButton* radioButton = qobject_cast<QRadioButton*>(sender());
	if (radioButton->text() == "Normal Color") {
		_bezierPatchHandler->setBezierPatchColorMode(0);
	}
	else if (radioButton->text() == "Position Color") {
		_bezierPatchHandler->setBezierPatchColorMode(1);
	}
	else if (radioButton->text() == "UV Color") {
		_bezierPatchHandler->setBezierPatchColorMode(2);
	}
	update();	
}

void OpenGLWidget::setBezierPatchMeshNumber()
{
	QSpinBox *spinBox = this->parentWidget()->findChild<QSpinBox*>("spinBox");
	_bezierPatchHandler->setBezierPatchNumber(spinBox->value());
	update();
}

void OpenGLWidget::randomize()
{
	_bezierPatchHandler->randomize();
	update();
}

void OpenGLWidget::wireFrame(bool checked)
{
	_handler->wireFrame(checked);
	update();
}

void OpenGLWidget::setBezierMode(int mode)
{
	if (mode == 1) {
		_handler = _bezierCurveHandler;
	}
	else {
		_handler = _bezierPatchHandler;
	}
	update();	
}
