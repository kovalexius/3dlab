#include <string>
#include <iostream>
#include <cstdlib>

#include <QResizeEvent>

#include "file_data.h"
#include "glvoxel.h"
#include "octree_data.h"
#include "octree_utils.h"
#include "../../glExt/gl_helpers.h"


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
    m_voxProgram = 0;

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
    
    auto buf = read_data_file("box.dat");

    m_shape_data = std::move(ShapeData(buf));
    /*
    const Vector3D& origin = shape_data.getOrigin();
    uint64_t num = shape_data.getVoxNumber();
    float vox_metre = shape_data.getVoxMetre();
    float width = shape_data.getWidth();
    float height = shape_data.getHeight();
    float depth = shape_data.getDepth();
    std::cout << "orig.x=" << origin.x << " orig.y=" << origin.y << " orig.z=" << origin.z << " num of voxels=" << num <<
                " vox_metre=" << vox_metre << " width=" << width << " height=" << height << " depth=" << depth << std::endl;
    int h = OctreeUtils::getMaxDepthOctreeByData( shape_data );
    Octree octree( width, height, depth, h );
    */
    auto octree = OctreeUtils::createOctree(m_shape_data);
    m_xRot = 0.0;
    m_yRot = 0.0;
    m_R = 15;
    m_xMov = 0.0;
    m_yMov = 0.0;
    m_shift = Vector3D(0, 0, 0);
}

void GLVoxel::initShader()
{
    if (m_voxProgram)
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
    m_voxProgram = glCreateProgram();
    glAttachShader(m_voxProgram, vShader);
    glAttachShader(m_voxProgram, fShader);

    glLinkProgram(m_voxProgram);

    programLog(m_voxProgram);
    // ! Проверяем статус сборки
    checkOpenGLerror();
}

// ! Освобождение шейдеров
void GLVoxel::freeShader()
{
    glUseProgram(0);
    glDeleteProgram(m_voxProgram);
}

void GLVoxel::renderFrame()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*
    //glUseProgram(m_voxProgram);
    glBegin(GL_QUADS);
    glVertex2f(-0.9f, -0.9f);
    glVertex2f(0.9f, -0.9f);
    glVertex2f(0.9f, 0.9f);
    glVertex2f(-0.9f, 0.9f);
    glEnd();
    glUseProgram(0);
    /**/
    
    
    glPointSize(2.5);
    uint64_t vox_number = m_shape_data.getVoxNumber();
    glBegin(GL_POINTS);
    for( uint64_t i = 0; i < vox_number; i++ )
    {
        Color col;
        const Vector3D& vec = m_shape_data.getVoxel(i, col.color);
        //std::cout << "r=" << col.r << " g=" << col.g << " b=" << col.b << " a=" << col.a << " x=" << vec.x << " y=" << vec.y << " z=" << vec.z << std::endl;
        glColor4b(col.r, col.g, col.b, col.a);
        glVertex3f(vec.m_x, vec.m_y, vec.m_z);
    }
    glEnd();

    glMatrixMode(GL_PROJECTION);                    //
    glLoadIdentity();                               //	Установка произвольной перспективной
    glFrustum(-1.1, 1.1, -1.0, 1.0, 0.5, 20);       //	проекции
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    calculateCamera();
    gluLookAt(m_pCamera.m_x,
                m_pCamera.m_y,
                m_pCamera.m_z,
                m_tCamera.m_x,
                m_tCamera.m_y,
                m_tCamera.m_z,
                m_upCamera.m_x,
                m_upCamera.m_y,
                m_upCamera.m_z);	                    // Установка камеры

    updateGL();
}

void GLVoxel::mouseMoveEvent(QMouseEvent *event)
{
    if (event->modifiers()&Qt::ShiftModifier)
    {
        if (m_xRot>-6.28 || m_xRot<6.28)
            m_xRot += -(float)(event->x() - m_Pos.x())*0.0017444;
        else
            m_xRot = (float)6.28;
        if (m_yRot>-6.28 || m_yRot<6.28)
            m_yRot += (float)(event->y() - m_Pos.y())*0.0017444;
        else
            m_yRot = (float)6.28;
        GetXYZ();

        setCursor(Qt::SizeAllCursor);
    }
    if (event->modifiers()&Qt::AltModifier)
    {
        m_xMov = (float)(-event->x() + m_Pos.x()) / 4;
        m_yMov = (float)(event->y() - m_Pos.y()) / 4;
        GetDXYZ();
        m_xMov = 0;
        m_yMov = 0;

        setCursor(Qt::ClosedHandCursor);
    }
    m_Pos = event->pos();
}

void GLVoxel::wheelEvent(QWheelEvent *e)
{
    e->delta()>0 ? m_R += m_R*0.05f : m_R -= m_R*0.05f;
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

    m_pCamera = m_position + m_shift;
    m_tCamera = m_shift;
    m_upCamera = m_up;
}

void GLVoxel::GetXYZ( )
{
    m_position.m_y = sin(m_yRot)*m_R;
    m_position.m_z = cos(m_xRot)*cos(m_yRot)*m_R;
    m_position.m_x = sin(m_xRot)*cos(m_yRot)*m_R;

    m_up.m_y = cos(-m_yRot);
    m_up.m_x = sin(m_xRot)*sin(-m_yRot);
    m_up.m_z = cos(-m_xRot)*sin(-m_yRot);
}

void GLVoxel::GetDXYZ( )
{
    m_shift.m_x += cos(m_xRot)*m_xMov + sin(m_xRot)*sin(-m_yRot)*m_yMov;
    m_shift.m_z += sin(-m_xRot)*m_xMov + sin(-m_yRot)*cos(m_xRot)*m_yMov;
    m_shift.m_y += cos(m_yRot)*m_yMov;
}