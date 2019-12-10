#include <string>
#include <iostream>
#include <cstdlib>
//#include <conio.h>

#include <QResizeEvent>

#include "file_data.h"
#include "glvoxel.h"
#include "octree_data.h"

void checkOpenGLerror()
{
    GLenum errCode;
    if ((errCode = glGetError()) != GL_NO_ERROR)
        std::cout << "OpenGl error! - " << gluErrorString(errCode) << std::endl;
}

//! Функция печати лога шейдера
void shaderLog(unsigned int shader)
{
    int   infologLen = 0;
    int   charsWritten = 0;
    char *infoLog;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLen);

    if (infologLen > 1)
    {
        infoLog = new char[infologLen];
        if (infoLog == NULL)
        {
            std::cout << "ERROR: Could not allocate InfoLog buffer\n" << std::endl;
        }
        glGetShaderInfoLog(shader, infologLen, &charsWritten, infoLog);
        std::cout << "InfoLog: " << infoLog << std::endl;
        delete[] infoLog;
    }
}

//! Функция печати лога шейдера
void programLog(unsigned int prog)
{
    int   infologLen = 0;
    int   charsWritten = 0;
    char *infoLog;

    glGetProgramiv( prog, GL_INFO_LOG_LENGTH, &infologLen);

    if (infologLen > 1)
    {
        infoLog = new char[infologLen];
        if (infoLog == NULL)
        {
            std::cout << "ERROR: Could not allocate InfoLog buffer" << std::endl;
        }
        glGetProgramInfoLog( prog, infologLen, &charsWritten, infoLog);
        std::cout << "InfoLog: " << infoLog << std::endl;
        delete[] infoLog;
    }
}

GLVoxel::GLVoxel(QWidget *parent)
{
    voxProgram = 0;

    QGLFormat glFormat;
    glFormat.setRgba(true);
    glFormat.setRedBufferSize(8);
    glFormat.setGreenBufferSize(8);
    glFormat.setBlueBufferSize(8);
    glFormat.setAlphaBufferSize(8);
    glFormat.setProfile(QGLFormat::OpenGLContextProfile::CompatibilityProfile);
    ::QGLWidget(glFormat, parent);

    timerFreqFps = new QTimer(this);
    connect(timerFreqFps, SIGNAL(timeout()), this, SLOT(renderFrame()));
}

void GLVoxel::resizeEvent(QResizeEvent * event)
{
    glViewport(0, 0, event->size().width(), event->size().height());
}

void GLVoxel::initializeGL()
{
    glViewport(0, 0, this->size().width(), this->size().height());
}

void GLVoxel::StartRender()
{
    makeCurrent();                      // Чтобы glNewList работал
    setFocusPolicy(Qt::StrongFocus);    // Установка политики фокусировки на виджет
    setMouseTracking(true);             // Включение режима mouse трекинга при котором виджет получает сигнал движения мышки даже когда ни одна кнопка мышки не нажата

#ifdef OGL_EXT
    Init_ShaderObjects();
#endif
    
    initShader();

    timerFreqFps->setInterval(10);
    timerFreqFps->start();
    
    ///*
    int size;
    char *buf = read_data_file( "box.dat", size );
    shape_data = std::move( ShapeData( size, buf ) );
    const Vector3D &origin = shape_data.getOrigin();
    uint64_t num = shape_data.getVoxNumber();
    float vox_metre = shape_data.getVoxMetre();
    float width = shape_data.getWidth();
    float height = shape_data.getHeight();
    float depth = shape_data.getDepth();
    std::cout << "orig.x=" << origin.x << " orig.y=" << origin.y << " orig.z=" << origin.z << " num of voxels=" << num <<
                " vox_metre=" << vox_metre << " width=" << width << " height=" << height << " depth=" << depth << std::endl;
    int h = OctreeUtils::getMaxDepthOctreeByData( shape_data );
    Octree octree( width, height, depth, h );
    xRot = 0.0;
    yRot = 0.0;
    R = 15;
    xMov = 0.0;
    yMov = 0.0;
    shift = Vector3D(0, 0, 0);
    /**/
}

void GLVoxel::initShader()
{
    if (voxProgram)
        freeShader();

    GLuint vShader;
    GLuint fShader;

    GLchar *quad = filetobuf("vox.vert");
    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, (const GLchar**)&quad, NULL);
    glCompileShader(vShader);
    shaderLog(vShader);

    GLchar *vox = filetobuf("vox.frag");
    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, (const GLchar**)&vox, NULL);
    glCompileShader(fShader);
    shaderLog(fShader);

    // ! Создаем программу и прикрепляем шейдеры к ней
    voxProgram = glCreateProgram();
    glAttachShader(voxProgram, vShader);
    glAttachShader(voxProgram, fShader);

    glLinkProgram(voxProgram);

    programLog(voxProgram);
    // ! Проверяем статус сборки
    checkOpenGLerror();
}

// ! Освобождение шейдеров
void GLVoxel::freeShader()
{
    glUseProgram(0);
    glDeleteProgram(voxProgram);
}

void GLVoxel::renderFrame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*
    glUseProgram( voxProgram );
    glBegin(GL_QUADS);
    glVertex2f(-0.9f, -0.9f);
    glVertex2f(0.9f, -0.9f);
    glVertex2f(0.9f, 0.9f);
    glVertex2f(-0.9f, 0.9f);
    glEnd();
    glUseProgram(0);
    /**/
    
    ///*
    glMatrixMode(GL_PROJECTION);                    //
    glLoadIdentity();                               //	Установка произвольной перспективной
    glFrustum(-1.1, 1.1, -1.0, 1.0, 0.5, 20);	//	проекции
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    calculateCamera();
    gluLookAt(pCamera.x, pCamera.y, pCamera.z, tCamera.x, tCamera.y, tCamera.z, upCamera.x, upCamera.y, upCamera.z);	// Установка камеры
    glPointSize(2.5);
    uint64_t vox_number = shape_data.getVoxNumber();
    glBegin(GL_POINTS);
    for( uint64_t i = 0; i < vox_number; i++ )
    {
        Color col;
        const Vector3D &vec = shape_data.getVoxel( i, col.color );
        //std::cout << "r=" << col.r << " g=" << col.g << " b=" << col.b << " a=" << col.a << std::endl;
        glColor4b( col.r, col.g, col.b, col.a );
        glVertex3f( vec.x, vec.y, vec.z );
    }
    glEnd();
    //getch();
    /**/

    updateGL();
}

void GLVoxel::mouseMoveEvent(QMouseEvent *event)
{
    if (event->modifiers()&Qt::ShiftModifier)
    {
        if (xRot>-6.28 || xRot<6.28)
            xRot += -(float)(event->x() - mPos.x())*0.0017444;
        else
            xRot = (float)6.28;
        if (yRot>-6.28 || yRot<6.28)
            yRot += (float)(event->y() - mPos.y())*0.0017444;
        else
            yRot = (float)6.28;
        GetXYZ();

        setCursor(Qt::SizeAllCursor);
    }
    if (event->modifiers()&Qt::AltModifier)
    {
        xMov = (float)(-event->x() + mPos.x()) / 4;
        yMov = (float)(event->y() - mPos.y()) / 4;
        GetDXYZ();
        xMov = 0;
        yMov = 0;

        setCursor(Qt::ClosedHandCursor);
    }
    mPos = event->pos();
}

void GLVoxel::wheelEvent(QWheelEvent *e)
{
    e->delta()>0 ? R += R*0.05f : R -= R*0.05f;
    calculateCamera();
}

void GLVoxel::keyReleaseEvent(QKeyEvent * event)
{
    setCursor(Qt::ArrowCursor);
}


void GLVoxel::calculateCamera( )
{
    GetXYZ( );
    GetDXYZ( );

    pCamera = position + shift;
    tCamera = shift;
    upCamera = up;
}

void GLVoxel::GetXYZ( )
{
    position.y = sin(yRot)*R;
    position.z = cos(xRot)*cos(yRot)*R;
    position.x = sin(xRot)*cos(yRot)*R;

    up.y = cos(-yRot);
    up.x = sin(xRot)*sin(-yRot);
    up.z = cos(-xRot)*sin(-yRot);
}

void GLVoxel::GetDXYZ( )
{
    shift.x += cos(xRot)*xMov + sin(xRot)*sin(-yRot)*yMov;
    shift.z += sin(-xRot)*xMov + sin(-yRot)*cos(xRot)*yMov;
    shift.y += cos(yRot)*yMov;
}