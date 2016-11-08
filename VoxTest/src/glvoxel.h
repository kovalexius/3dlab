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
    float	R;			//	��������� �� ������ ������
    float	xRot;	//	���� �������� � ��������� XZ � ��������
    float	yRot;	//	���� �������� � ��������� YZ � ��������
    float	xMov;	// ��������� ��������
    float	yMov;	// ����������� ������ (������� Alt)
    Vector3D pCamera;		//��� ������
    Vector3D tCamera;		//���� �������
    Vector3D upCamera;		//���� ������� ���� ������
    Vector3D up;	// ������� ������ ����� ������
    Vector3D position;	// ������� ������� ������
    Vector3D shift; // �������� ������ � ����
    QPoint mPos;
    void GetXYZ( );
    void GetDXYZ( );
    void calculateCamera( );
    virtual void mouseMoveEvent(QMouseEvent *event) override;       // ���� ������� ������
    virtual void wheelEvent(QWheelEvent *e) override;
    virtual void keyReleaseEvent(QKeyEvent * event) override;
};

#endif