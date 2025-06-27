#include "mainwindow.h"
#include <QDebug>
#include <QtOpenGL>

MainWindow::MainWindow()
{
}

MainWindow::~MainWindow()
{
    m_vbo.destroy();
    m_vao.destroy();
    delete m_program;
}

void MainWindow::initializeGL()
{
    initializeOpenGLFunctions();

    static const char *vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec3 position;
        uniform mat4 uMvpMatrix;

        void main()
        {
            gl_Position = uMvpMatrix * vec4(position, 1.0);
        }
    )";

    static const char *fragmentShaderSource = R"(
        #version 330 core
        out vec4 fragColor;

        void main()
        {
            fragColor = vec4(0.0, 0.8, 0.0, 1.0);
        }
    )";

    glClearColor(0.2f, 0.2f, 0.2f, 1.f);

    // Compile and link shaders
    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceCode(QOpenGLShader::ShaderTypeBit::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::ShaderTypeBit::Fragment, fragmentShaderSource);
    m_program->link();

    float vertices[] = {
        0.f, 0.5f, 0.f,
        -0.5f, -0.5f, 0.f,
        0.5f, -0.5f, 0.f
    };

    // Setup VAO
    m_vao.create();
    m_vao.bind();

    // Setup VBO and upload data
    m_vbo.create();
    m_vbo.bind();
    m_vbo.allocate(vertices, sizeof(vertices));

    // Tell OpenGL how to interpret vertex data
    m_program->enableAttributeArray(0);
    m_program->setAttributeBuffer(0, GL_FLOAT, 0, 3);

    m_vbo.release();
    m_vao.release();

    m_viewMatrix.lookAt(QVector3D(0.f, 0.f, 1.f),
                        QVector3D(0.f, 0.f, 0.f),
                        QVector3D(0.f, 1.f, 0.f));

    m_uMvpMatrixLocation = m_program->uniformLocation("uMvpMatrix");

    qDebug("version %s", glGetString(GL_VERSION));

    // QObject::connect(this, &MainWindow::frameSwapped, [this]() { this->update(); });
}

void MainWindow::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)w, (GLint)h);
    m_projMatrix.setToIdentity();
    m_projMatrix.ortho(-50.f, 50.f, -50.f, 50.f, -1.f, 1.f);
    m_projViewMatrix = m_projMatrix * m_viewMatrix;
}

void MainWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();
    m_vao.bind();

    m_modelMatrix.setToIdentity();
    m_modelMatrix.translate(10.f, 30.f, 0.f);
    m_modelMatrix.rotate(20.f, QVector3D(0.f, 0.f, 1.f));
    m_modelMatrix.scale(25.f, 25.f, 1.f);

    m_mvpMatrix = m_projViewMatrix * m_modelMatrix;
    m_program->setUniformValue(m_uMvpMatrixLocation, m_mvpMatrix);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    m_vao.release();
    m_program->release();
}
