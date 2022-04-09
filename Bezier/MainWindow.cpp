#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void MainWindow::RadioButtonClicked() {
	QRadioButton *radioButton = qobject_cast<QRadioButton *>(sender());
	std::cout << "Radio button clicked: " << radioButton->text().toStdString() << std::endl;
}

void MainWindow::curveMeshToggleButton() {
	QRadioButton* radioButton = qobject_cast<QRadioButton*>(sender());
	QSlider* lengthSlider = ui.tabWidget->findChild<QSlider*>("lengthSlider");
	QSlider* numberSlider = ui.tabWidget->findChild<QSlider*>("numberSlider");
	QLabel* numberText = ui.tabWidget->findChild<QLabel*>("numberText");	
	QLabel* lengthText = ui.tabWidget->findChild<QLabel*>("lengthText");
	if (radioButton->text() == "Segment Length") {
		numberSlider->setEnabled(false);
		numberText->setEnabled(false);
		lengthSlider->setEnabled(true);
		lengthText->setEnabled(true);	
	}else if(radioButton->text() == "Segment Number") {
		lengthSlider->setEnabled(false);
		lengthText->setEnabled(false);
		numberSlider->setEnabled(true);
		numberText->setEnabled(true);
	}
}

void MainWindow::curveMeshSlider() {
	QSlider* slider = qobject_cast<QSlider*>(sender());
	
	if (slider->objectName() == "lengthSlider") {
		QLabel* label = ui.tabWidget->findChild<QLabel*>("lengthText");
		label->setText(QString::number((float) slider->value() / 100.0f));
	}else if(slider->objectName() == "numberSlider") {
		QLabel* label = ui.tabWidget->findChild<QLabel*>("numberText");
		label->setText(QString::number(slider->value()));
	}
}
