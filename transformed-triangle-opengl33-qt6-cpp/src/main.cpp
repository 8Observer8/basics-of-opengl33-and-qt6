#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::ApplicationAttribute::AA_UseDesktopOpenGL);
    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setMajorVersion(3);
    format.setMinorVersion(3);
    format.setSamples(4);

    MainWindow w;
    w.setFormat(format);
    w.setGeometry(300, 100, 600, 600);
    w.show();

    return a.exec();
}
