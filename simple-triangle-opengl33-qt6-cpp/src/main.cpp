#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::ApplicationAttribute::AA_UseDesktopOpenGL);
    QApplication a(argc, argv);
    MainWindow w;
    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setMajorVersion(3);
    format.setMinorVersion(3);
    w.setFormat(format);
    QSurfaceFormat::setDefaultFormat(format);
    w.setGeometry(300, 100, 350, 350);
    w.show();
    return a.exec();
}
