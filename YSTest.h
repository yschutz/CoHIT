#ifndef YSTEST_H
#define YSTEST_H

#include <QGLWidget>

#define CLAMP(v, a, b) (a + (v - a) / (b - a))

class QMouseEvent;
class QPoint;
class QTimer;

class YSGrid3dFloat;
class YSGrid3dVector;
class YSHydro3d;

class YSTest : public QGLWidget
{
    Q_OBJECT

public:
    explicit YSTest(QWidget *parent = NULL);
    virtual ~YSTest();

    void initializeGL();
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintGL();
    void resizeGL(int width, int height);

    enum YSDisplayOpt {
         kDENSITY, kVELOCITY, kBOTH
     };

     YSHydro3d   *GetFluid() const { return mFluid; }
     void        SetDisplayOpt(YSDisplayOpt opt) {mDisplayOpt = opt;}


public slots:
    void RefreshImage();

private:
    void DisplayPixels();
    void DisplayPixelsDensity(YSGrid3dFloat *density);
    void DisplayPixelsVelocity(YSGrid3dVector *velocity);
    void SetColor(qreal density, qreal max);

    YSDisplayOpt   mDisplayOpt;             // tells what to dispay
    YSHydro3d      *mFluid;                 // the Hydro fluid
    QPoint         mLastPos;                // the mouse position on click
    GLfloat        mRotationX, mRotationY;  // to rotate view with mouse
    QTimer         *mTimer;                 // timer for Hydro evolution

};

#endif // YSTEST_H
