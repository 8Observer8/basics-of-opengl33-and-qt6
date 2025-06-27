#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
 
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
 
class MainWindow : public QOpenGLWindow, protected QOpenGLFunctions
{
    Q_OBJECT
 
public:
    MainWindow();
    ~MainWindow();
 
private:
    QOpenGLShaderProgram *m_program = nullptr;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;
 
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
};
#endif // MAINWINDOW_H
