#include <QDebug>
#include <QMouseEvent>
#include <QTime>
#include <QTimer>
#include <QVector3D>

#include "YSGrid3dFloat.h"
#include "YSGrid3dVector.h"
#include "YSHydro3d.h"
#include "YSTest.h"


//______________________________________________________________________________
YSTest::YSTest(QWidget *parent) :
    QGLWidget(parent), mRotationX(0.0), mRotationY(0.0)
{
    // ctor
    setWindowTitle(QString("Test GL"));
    int width = 500, height = 500;
    resize(width, height);

    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));

    // create the fluid

    unsigned int dimx = 130, dimy = 130, dimz = 4; // size of the grid
    mFluid = new YSHydro3d(dimx, dimy, dimz);

    // set the velocity on the grid "previous"
    QVector3D vL(0.0, 0.0, 0.99), vT(0.60, 0.0, 0.0); // longitudinal and transverse velocity in units of c
    mFluid->SetVelocity(vL, vT);

    // set the density on the grid "previous"

    mFluid->SetDensity();

    mTimer = new QTimer(this);
    connect(mTimer, SIGNAL(timeout()), this, SLOT(RefreshImage()));
    mTimer->start(1000);
}

//______________________________________________________________________________
YSTest::~YSTest()
{
    // dtor
    delete mFluid;
    delete mTimer;
}

//______________________________________________________________________________
void YSTest::initializeGL()
{
    // (https://www.opengl.org/sdk/docs/man2/xhtml/glShadeModel.xml)

    //    initialize openGL parameters
    //    Pixels can be drawn using a function that blends the incoming (source) RGBA
    //    values with the RGBA values that are already in the frame buffer (the destination values).

    glEnable     (GL_BLEND);                                  // enables blending
    glBlendFunc  (GL_SRC0_ALPHA, GL_ONE_MINUS_SRC_ALPHA);     // defines the blend function
    glShadeModel (GL_SMOOTH);                                 // specifies the shading technique
    glClearColor (0.0f, 0.0f, 0.0f, 0.0f);                    // specifies the red, green, blue, and alpha values used when the color buffers are cleared
    glClearDepth (1.0f);                                      // specifies the depth value used when the depth buffer is cleared
    glEnable     (GL_DEPTH_TEST);                             // to do depth comparisons and update the depth buffer
    glEnable     (GL_CULL_FACE);
    glDepthFunc  (GL_LEQUAL);                                 // specifies the depth comparison function: Passes if the incoming depth value is less than or equal to the stored depth value
    glHint       (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // the most correct, or highest quality, option should be chosen

}

//______________________________________________________________________________
void YSTest::mouseMoveEvent(QMouseEvent *event)
{
    GLfloat dx = (GLfloat) (event->x() - mLastPos.x()) / width();
    GLfloat dy = (GLfloat) (event->y() - mLastPos.y()) / height();
    if (event->buttons() & Qt::LeftButton) {
        mRotationX += 180 * dy;
        mRotationY += 180 * dx;
        updateGL();
    } else if (event->buttons() & Qt::RightButton) {
        mRotationX += 180 * dy;
        mRotationY += 180 * dx;
        updateGL();
    }
    mLastPos = event->pos();
}

//______________________________________________________________________________
void YSTest::mousePressEvent(QMouseEvent *event)
{
    // stores the position of the mouse
    mLastPos = event->pos();
}

//______________________________________________________________________________
void YSTest::paintGL()
{
    // draws stuff on the screen

    // clear opengl buffer
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


//    glTranslatef(0.0, 0.0, -10.0);

    glRotatef(mRotationX,1.0,0.0,0.0);
    // rotation about Y axis
    glRotatef(mRotationY,0.0,1.0,0.0);

    DisplayPixels(); // to be changed to current

}

//______________________________________________________________________________
void YSTest::resizeGL(int width, int height)
{
    // resize the openGL window
    if (height == 0)
        height = 1;
    glViewport(0, 0, width, height); // set position and size of the viewport
    glMatrixMode(GL_PROJECTION);     // applies subsequent matrix operations to the projection matrix stack
    glLoadIdentity();                // replace the projection matrix with the identity matrix

//    GLfloat x = (GLfloat)width / height;
//    glFrustum(-x, x, -1.0, 1.0, 4.0, 15.0);

    glMatrixMode(GL_MODELVIEW);      // applies subsequent matrix operations to the modelview matrix stack
    glLoadIdentity();                // replace the modelview matrix with the identity matrix
}

//______________________________________________________________________________
void YSTest::RefreshImage()
{
    // Displays the density grid

    qDebug() << "YSTest::RefreshImage";

    unsigned int remainingTime = mTimer->remainingTime();
    static unsigned int framebuffer = 1;
    if (remainingTime > 0)
        framebuffer++;
    else {
        qreal fps = framebuffer * 1000. / remainingTime;
        framebuffer = 0;
        mTimer->start();
    }

    mFluid->Step(mFluid->GetVelocity(YSHydro3d::kCURRENT), mFluid->GetVelocity(YSHydro3d::kPREVIOUS));

    mFluid->Step(mFluid->GetDensity(YSHydro3d::kCURRENT),  mFluid->GetDensity(YSHydro3d::kPREVIOUS), mFluid->GetVelocity(YSHydro3d::kCURRENT));

    mFluid->GetVelocity(YSHydro3d::kPREVIOUS)->Clear();
    mFluid->GetDensity(YSHydro3d::kPREVIOUS)->Clear();

    mFluid->GetVelocity(YSHydro3d::kPREVIOUS)->Add(mFluid->GetVelocity(YSHydro3d::kSOURCE));
    mFluid->GetDensity(YSHydro3d::kPREVIOUS)->Add(mFluid->GetDensity(YSHydro3d::kSOURCE));

    updateGL();
}

//______________________________________________________________________________
void YSTest::DisplayPixels()
{
    if (mDisplayOpt == kDENSITY || mDisplayOpt == kBOTH)
     // density
        DisplayPixelsDensity(mFluid->GetDensity(YSHydro3d::kCURRENT));

    if (mDisplayOpt == kVELOCITY || mDisplayOpt == kBOTH) {
        // velocity
        const unsigned int size  = 5;
        YSGrid3dVector *reducedVelGrid = new YSGrid3dVector(mFluid->GetVelocity(YSHydro3d::kCURRENT)->DimX() / size,
                                                            mFluid->GetVelocity(YSHydro3d::kCURRENT)->DimY() / size,
                                                            mFluid->GetVelocity(YSHydro3d::kCURRENT)->DimZ() / size);
        mFluid->GetVelocity(YSHydro3d::kCURRENT)->Resize(reducedVelGrid, size);
        DisplayPixelsVelocity(reducedVelGrid);

    }
}

//______________________________________________________________________________
void YSTest::DisplayPixelsDensity(YSGrid3dFloat *density)
{
    // Display a set of squares which represent the density
    // of particules on the volume stored in the density grid. More
    // white square is the more particles are. We use transparency
    // to make the gradient.

   const unsigned int x = density->DimX();
   const unsigned int y = density->DimY();
   const unsigned int z = density->DimZ();

   // draw a cube as 6 faces (squares) for each cell of the grid
   qreal densityMax = density->GetMax();

   for(unsigned int index = 0; index < x; index++) {
       for(unsigned int indey = 0; indey < y; indey++) {
           for(unsigned int indez = 0; indez < z; indez++) {
               if (density->Get(index, indey, indez) >  0.0) {
                   SetColor(density->Get(index, indey, indez), densityMax);

                   // define 6 faces of the cube
                   glBegin(GL_QUADS);    //delimit the vertices of a primitive or a group of like primitives
                   // front
                   glVertex3f(-1.0 + (index + 1.0)  * 2.0 / x, -1.0 + (indey + 1.0) * 2.0 / y, -1.0 + (indez + 1.0) * 2.0 / z);
                   if (index < x - 1)
                       SetColor(density->Get(index + 1.0, indey, indez), densityMax);
                   else
                       SetColor(density->Get(index, indey, indez), densityMax);
                   glVertex3f(-1.0 + index          * 2.0 / x, -1.0 + (indey + 1.0) * 2.0 / y, -1.0 + (indez + 1.0) * 2.0 / z);
                   if (index < x -1 && indey < y - 1)
                       SetColor(density->Get(index + 1.0, indey + 1.0, indez), densityMax);
                   else
                       SetColor(density->Get(index, indey, indez), densityMax);
                   glVertex3f(-1.0 + index          * 2.0 / x, -1.0 + indey         * 2.0 / y, -1.0 + (indez + 1.0) * 2.0 / z);
                   if (indey < y -1)
                       SetColor(density->Get(index, indey + 1.0, indez), densityMax);
                   else
                       SetColor(density->Get(index, indey, indez), densityMax);
                   glVertex3f(-1.0 + (index + 1.0)  * 2.0 / x, -1.0 + indey       * 2.0 / y, -1.0 + (indez + 1.0) * 2.0 / z);
                   // back
                   glVertex3f(-1.0 + (index + 1.0)  * 2.0 / x, -1.0 + indey * 2.0 / y, -1.0 + indez  * 2.0 / z);
                   if (index < x - 1)
                       SetColor(density->Get(index + 1.0, indey, indez), densityMax);
                   else
                       SetColor(density->Get(index, indey, indez), densityMax);
                   glVertex3f(-1.0 + index          * 2.0 / x, -1.0 + indey  * 2.0 / y, -1.0 + indez  * 2.0 / z);
                   if (index < x -1 && indey < y - 1)
                       SetColor(density->Get(index + 1.0, indey + 1.0, indez), densityMax);
                   else
                       SetColor(density->Get(index, indey, indez), densityMax);
                   glVertex3f(-1.0 + index         * 2.0 / x, -1.0 + (indey + 1)        * 2.0 / y, -1.0 + indez  * 2.0 / z);
                   if (indey < y -1)
                       SetColor(density->Get(index, indey + 1.0, indez), densityMax);
                   else
                       SetColor(density->Get(index, indey, indez), densityMax);
                   glVertex3f(-1.0 + (index + 1.0)  * 2.0 / x, -1.0 + (indey + 1) * 2.0 / y,       -1.0 + indez  * 2.0 / z);
                   // right
                   glVertex3f(-1.0 + (index + 1.0) * 2.0 / x,        -1.0 + (indey + 1.0) * 2.0 / y, -1.0 + (indez + 1)   * 2.0 / z);
                   if (index < x - 1)
                       SetColor(density->Get(index + 1.0, indey, indez), densityMax);
                   else
                       SetColor(density->Get(index, indey, indez), densityMax);
                   glVertex3f(-1.0 + (index + 1.0) * 2.0 / x,        -1.0 + indey * 2.0 / y,         -1.0 + (indez + 1.0) * 2.0 / z);
                   if (index < x -1 && indez < z - 1)
                       SetColor(density->Get(index + 1.0, indey, indez + 1.0), densityMax);
                   else
                       SetColor(density->Get(index, indey, indez), densityMax);
                   glVertex3f(-1.0 + (index + 1.0) * 2.0 / x,        -1.0 + indey * 2.0 / y,         -1.0 + indez         * 2.0 / z);
                   if (indez < z - 1)
                       SetColor(density->Get(index, indey, indez + 1.0), densityMax);
                   else
                       SetColor(density->Get(index, indey, indez), densityMax);
                   glVertex3f(-1.0 + (index + 1.0) * 2.0 / x,        -1.0 + (indey + 1) * 2.0 / y,   -1.0 + indez         * 2.0 / z);
//                    left
                   glVertex3f(-1.0 + index * 2.0 / x, -1.0 + (indey + 1.0) * 2.0 / y, -1.0 + (indez + 1.0) * 2.0 / z);
                   if (indey < y - 1)
                       SetColor(density->Get(index, indey + 1.0, indez), densityMax);
                   else
                       SetColor(density->Get(index, indey, indez), densityMax);
                   glVertex3f(-1.0 + index * 2.0 / x, -1.0 + (indey + 1.0) * 2.0 / y, -1.0 + indez     * 2.0 / z);
                   if (indey < y -1 && indez < z - 1)
                       SetColor(density->Get(index, indey + 1.0, indez + 1.0), densityMax);
                   else
                       SetColor(density->Get(index, indey, indez), densityMax);
                   glVertex3f(-1.0 + index * 2.0 / x, -1.0 + indey * 2.0 / y,       -1.0 + indez       * 2.0 / z);
                   if (indey < z - 1)
                       SetColor(density->Get(index, indey, indez + 1.0), densityMax);
                   else
                       SetColor(density->Get(index, indey, indez), densityMax);
                   glVertex3f(-1.0 + index * 2.0 / x, -1.0 + indey * 2.0 / y,       -1.0 + (indez + 1) * 2.0 / z);
                   // top
                   glVertex3f(-1.0 + (index + 1.0) * 2.0 / x, -1.0 + (indey + 1.0) * 2.0 / y, -1.0 + indez         * 2.0 / z);
                   if (index < x - 1)
                       SetColor(density->Get(index + 1.0, indey, indez), densityMax);
                   else
                       SetColor(density->Get(index, indey, indez), densityMax);
                   glVertex3f(-1.0 + index  * 2.0 / x,        -1.0 + (indey + 1.0) * 2.0 / y, -1.0 + indez         * 2.0 / z);
                   if (index < x -1 && indez < z - 1)
                       SetColor(density->Get(index + 1.0, indey, indez + 1.0), densityMax);
                   else
                       SetColor(density->Get(index, indey, indez), densityMax);
                   glVertex3f(-1.0 + index  * 2.0 / x,        -1.0 + (indey + 1.0) * 2.0 / y, -1.0 + (indez + 1.0) * 2.0 / z);
                   if (indey < z -1)
                       SetColor(density->Get(index, indey, indez + 1.0), densityMax);
                   else
                       SetColor(density->Get(index, indey, indez), densityMax);
                   glVertex3f(-1.0 + (index + 1.0) * 2.0 / x, -1.0 + (indey + 1.0) * 2.0 / y, -1.0 + (indez + 1.0) * 2.0 / z);
                   // bottom
                   glVertex3f(-1.0 + (index + 1.0)  * 2.0 / x, -1.0 + indey * 2.0 / y, -1.0 + (indez + 1.0) * 2.0 / z);
                   if (index < x - 1)
                       SetColor(density->Get(index + 1.0, indey, indez), densityMax);
                   else
                       SetColor(density->Get(index, indey, indez), densityMax);
                   glVertex3f(-1.0 + index          * 2.0 / x, -1.0 + indey * 2.0 / y, -1.0 + (indez + 1.0) * 2.0 / z);
                   if (index < x -1 && indez < z - 1)
                       SetColor(density->Get(index + 1.0, indey, indez + 1.0), densityMax);
                   else
                       SetColor(density->Get(index, indey, indez), densityMax);
                   glVertex3f(-1.0 + index         * 2.0 / x, -1.0 + indey * 2.0 / y, -1.0 + indez          * 2.0 / z);
                   if (indey < z -1)
                       SetColor(density->Get(index, indey, indez + 1.0), densityMax);
                   else
                       SetColor(density->Get(index, indey, indez), densityMax);
                   glVertex3f(-1.0 + (index + 1.0) * 2.0 / x, -1.0 + indey * 2.0 / y, -1.0 + indez          * 2.0 / z);
                   glEnd();
               }
           }
       }
   }
   glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

//______________________________________________________________________________
void YSTest::DisplayPixelsVelocity(YSGrid3dVector *velocity)
{
    // Display a set of vectors which origin is situated at
    // of cells uniformly distributed on the window. The coordinates
    // are stored in a 3D vector

   const unsigned int x = velocity->DimX();
   const unsigned int y = velocity->DimY();
   const unsigned int z = velocity->DimZ();

   for (unsigned int index = 0; index < x; index++) {
       for (unsigned int indey = 0; indey < y; indey++) {
           for (unsigned int indez = 0; indez < z; indez++)  {
               glBegin(GL_LINES);
               glColor3f(0.0f, 0.2f, 1.0f);
               // vector
               glVertex3f(-1.0 + (1.0 + index * 2.0) * 1.0 / x,
                          -1.0 + (1.0 + indey * 2.0) * 1.0 / y,
                          -1.0 + (1.0 + indez * 2.0) * 1.0 / z);
               QVector3D vec = velocity->Get(index, indey, indez);
               glVertex3f(-1.0 + (1.0 + index * 2.0) * 1.0 / x + vec.x(),
                          -1.0 + (1.0 + indey * 2.0) * 1.0 / y + vec.y(),
                          -1.0 + (1.0 + indez * 2.0) * 1.0 / z + vec.z());
               glColor3f(1.0f, 1.0f, 1.0f);
               glEnd();
               // origine point
               glBegin(GL_POINTS);
               glColor3f(0.0f, 1.0f, 0.0f);
               glVertex3f(-1.0 + (1.0 + index * 2.0) * 1.0 / x,
                          -1.0 + (1.0 + indey * 2.0) * 1.0 / y,
                          -1.0 + (1.0 + indez * 2.0) * 1.0 / z);
               glEnd();
           }
       }
   }
   // display the grid

   glBegin(GL_LINES);    // Treats each pair of vertices as an independent line segmen
   glColor3f(1.0f, 0.0f, 0.0f);
   for (unsigned int index = 0; index <= x; index++) {
       for (unsigned int indey = 0; indey <= y; indey++) {
           for (unsigned int indez = 0; indez <= z; indez++)  {

               glVertex3f(1.0 - index * 2.0 / x, -1.0, 1 - indez * 2.0 / z);
               glVertex3f(1.0 - index * 2.0 / x,  1.0, 1 - indez * 2.0 / z);

               glVertex3f(-1.0, 1 - indey * 2.0 / y, 1 - indez * 2.0 / z);
               glVertex3f( 1.0, 1 - indey * 2.0 / y, 1 - indez * 2.0 / z);


               glVertex3f(1.0 - index * 2.0 / x,  1 - indey * 2.0 / y,   1.0);
               glVertex3f(1.0 - index * 2.0 / x,  1 - indey * 2.0 / y, -1.0);
           }
       }
   }
   glColor3f(1.0f, 1.0f, 1.0f);
   glEnd();
}

//______________________________________________________________________________
void YSTest::SetColor(qreal density, qreal max)
{
    // set the color according to density value
    const qreal t1 = max / 4.0;
    const qreal t2 = t1 + max / 4.0;
    const qreal t3 = t2 + max / 4.0;

    // red
    if ( density < t1 )
        glColor4f(CLAMP(density, 0., t1), 0., 0., density);
    // yellow
    else if ( density < t2 )
        glColor4f(1.0, CLAMP(density, t1, t2) - t1, 0.0, 1.0);
    // white
    else if ( density < t3 )
        glColor4f(1.0, 1.0, CLAMP(density, t2, t3) - t2, 1.0);
    else
        glColor4f(1.0, 1.0, 1.0, 1.0);
}
