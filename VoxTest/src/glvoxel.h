#ifndef GLVOXEL_H
#define GLVOXEL_H

#include <QGLWidget>
#include <QtCore>

#include "glExtInit.h"

#include "generate_shapes.h"

class GLVoxel : public QGLWidget
{
    Q_OBJECT
public:
    GLVoxel(QWidget *parent = 0);

protected:
    virtual void resizeEvent(QResizeEvent * event) override;
    virtual void initializeGL() override;

    void initShader();
    void freeShader();

private:
    QTimer *timerFreqFps;
    GLuint m_voxProgram;

public slots:
    void renderFrame();
    void StartRender();

private:
    ShapeData m_shape_data;
    float	m_R;			//	Дистанция до центра обзора
    float	m_xRot;	//	Угол поворота в плоскости XZ в радианах
    float	m_yRot;	//	Угол поворота в плоскости YZ в радианах
    float	m_xMov;	// Временное смещение
    float	m_yMov;	// визуального обзора (Нажатие Alt)
    Vector3D m_pCamera;		//Где камера
    Vector3D m_tCamera;		//Куда смотрит
    Vector3D m_upCamera;	//Куда смотрит верх камеры
    Vector3D m_up;	        // Текущий вектор верха камеры
    Vector3D m_position;	    // Текущая позиция камеры
    Vector3D m_shift;         // Смещение камеры в боки
    QPoint m_Pos;
    void GetXYZ( );
    void GetDXYZ( );
    void calculateCamera( );
    virtual void mouseMoveEvent(QMouseEvent *event) override;       // Если двинули мышкой
    virtual void wheelEvent(QWheelEvent *e) override;
    virtual void keyReleaseEvent(QKeyEvent * event) override;
};

#endif