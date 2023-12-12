#ifndef YUVRENDER_H
#define YUVRENDER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <vector>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)
QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)

class YuvRender : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    YuvRender(QWidget *parent =0);
    ~YuvRender();

public slots:
    void showYuv(std::vector<unsigned char> &data_y_, std::vector<unsigned char> &data_u_, std::vector<unsigned char> &data_v_, uint width, uint height);

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;

private:
    QOpenGLShaderProgram *program;
    QOpenGLBuffer vbo;
    GLuint textureUniformY;
    GLuint textureUniformU;
    GLuint textureUniformV;
    QOpenGLTexture *textureY = nullptr;
    QOpenGLTexture *textureU = nullptr;
    QOpenGLTexture *textureV = nullptr;
    GLuint idY = 0;
    GLuint idU = 0;
    GLuint idV = 0;
    uint32_t video_w = 0;
    uint32_t video_h = 0;
    std::vector<unsigned char> data_y;
    std::vector<unsigned char> data_u;
    std::vector<unsigned char> data_v;
};

#endif // YUVRENDER_H
