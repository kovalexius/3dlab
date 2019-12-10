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
    GLuint voxProgram;

public slots:
    void renderFrame();
    void StartRender();

private:
    ShapeData shape_data;
    float	R;			//	Дистанция до центра обзора
    float	xRot;	//	Угол поворота в плоскости XZ в радианах
    float	yRot;	//	Угол поворота в плоскости YZ в радианах
    float	xMov;	// Временное смещение
    float	yMov;	// визуального обзора (Нажатие Alt)
    Vector3D pCamera;		//Где камера
    Vector3D tCamera;		//Куда смотрит
    Vector3D upCamera;		//Куда смотрит верх камеры
    Vector3D up;	// Текущий вектор верха камеры
    Vector3D position;	// Текущая позиция камеры
    Vector3D shift; // Смещение камеры в боки
    QPoint mPos;
    void GetXYZ( );
    void GetDXYZ( );
    void calculateCamera( );
    virtual void mouseMoveEvent(QMouseEvent *event) override;       // Если двинули мышкой
    virtual void wheelEvent(QWheelEvent *e) override;
    virtual void keyReleaseEvent(QKeyEvent * event) override;
};

#endif