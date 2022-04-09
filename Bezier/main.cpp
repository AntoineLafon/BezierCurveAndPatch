#include "MainWindow.h"
#include <QtWidgets/QApplication>

struct Vertex {
    glm::vec3 pos;
    //glm::vec3 normal;
    //glm::vec2 texCoords;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
