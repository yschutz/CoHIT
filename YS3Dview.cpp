//
//  YS3DView.cpp
//  GL view of a nucleus
//
//  Created by Yves Schutz on 15/12/13.
//  Copyright (c) 2013 Yves Schutz. All rights reserved.
//

#include "qglbuilder.h"
#include "qglsphere.h"
#include <QtOpenGL/QGLFramebufferObject>

#include <QDebug>
#include <QKeyEvent>
#include <QtMath>
#include <QPropertyAnimation>
#include <QUrl>
#include <QVector3D>

#include "YSCollision.h"
#include "YS3DView.h"
#include "YSImpactParameterSetter.h"
#include "YSNucleus.h"
#include "YSMenu.h"


//______________________________________________________________________________
YS3DView::YS3DView(YSMenu *parent, YSNucleus *nucleus)
    : QGLView(0), mb(0.0),
     mCollision(false), mCollDist(0.0), mFBO(NULL), mIps(NULL),
     mNanimation(NULL), mNpos(0.0), mParent(parent),
     mQanimation(NULL), mQpos(0.0)
{
   //ctor to draw one nucleus
    QGLBuilder builder;

    // the nucleus
    mNucleus1 = nucleus;
    builder.newSection(QGL::Faceted);
    builder << QGLSphere(mNucleus1->RadiusMean() * 2);
    mNucleusEnv = builder.currentNode();
    mNucleusEnv->setObjectName("nucleus");

    InitNucleonAndQuark(builder);

    mScene = builder.finalizedSceneNode();
    mScene->setParent(this);

    mInnerCamera = new QGLCamera(this);

}

//______________________________________________________________________________
YS3DView::YS3DView(YSMenu *parent, YSCollision *collision)
    : QGLView(0), mCollision(true),mCollDist(30.0), mNanimation(NULL),
       mParent(parent), mQanimation(NULL)
{
    // ctor to draw the collision
    QGLBuilder builder;

    // nucleus 1
    mNucleus1 = collision->Nucleus(1);
    builder.newSection(QGL::Faceted);
    builder << QGLSphere(mNucleus1->RadiusMean() * 2);
    mNucleusEnv = builder.currentNode();
    mNucleusEnv->setObjectName("nucleus1");

    // nucleus 2
    mNucleus2 = collision->Nucleus(2);
    builder.newSection(QGL::Faceted);
    builder << QGLSphere(mNucleus1->RadiusMean() * 2);
    mNucleusEnv = builder.currentNode();
    mNucleusEnv->setObjectName("nucleus2");

    // impact parameter
    mb = collision->Getb();

    InitNucleonAndQuark(builder);

    mScene = builder.finalizedSceneNode();
    mScene->setParent(this);

    mInnerCamera = new QGLCamera(this);

    mIps = new YSImpactParameterSetter(mParent, collision);
    mIps->move(10, 500);
    mIps->show();

}

//______________________________________________________________________________
YS3DView::~YS3DView()
{
    delete mFBO;
    delete mQanimation;
    delete mNanimation;
    delete mIps;
}

//______________________________________________________________________________
void YS3DView::initializeGL(QGLPainter *)
{
   // create the framebuffer needed to draw the nested view
    mFBO = new QOpenGLFramebufferObject(512, 512, QOpenGLFramebufferObject::Depth);
    mFBOSurface.setFramebufferObject(mFBO);

    glEnable(GL_BLEND);
}

//______________________________________________________________________________
void YS3DView::keyPressEvent(QKeyEvent * event)
{
    // stop the animation
    if (event->key() == Qt::Key_Space && !event->isAutoRepeat()) {
        if (!mQanimation) {
            mQanimation = new QPropertyAnimation(this, "QRot", this);
            mQanimation->setStartValue(0.0f);
            mQanimation->setEndValue(360.0f);
            mQanimation->setDuration(4500);
            mQanimation->setLoopCount(-1);
        }
        if (mQanimation->state() == QAbstractAnimation::Running)
            mQanimation->stop();
        else
            mQanimation->start();
    } else if (event->key() == Qt::Key_Return && !event->isAutoRepeat()) {
        if (mCollision) {
            if(!mNanimation) {
                mNanimation = new QPropertyAnimation(this, "NTrans", this);
                mNanimation->setDuration(4500);
                mNanimation->setStartValue(0.0f);
                mNanimation->setEndValue(mCollDist * 2.);
            }
             if (mNanimation->state() == QAbstractAnimation::Running)
                mNanimation->stop();
            else
                mNanimation->start();
        }
    }
}

//______________________________________________________________________________
void YS3DView::DrawNucleon(QGLPainter *painter, const QVector3D &posn)
{
    // Draw a transparent nucleon
    painter->modelViewMatrix().push();
    painter->setFaceColor(QGL::AllFaces, QColor(0, 160, 202, 125));
    painter->setStandardEffect(QGL::LitDecalTexture2D);
    glBindTexture(GL_TEXTURE_2D, mFBO->texture());
    glEnable(GL_TEXTURE_2D);

    painter->modelViewMatrix().translate(posn);

    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);
    mNucleonNode->draw(painter);
    glCullFace(GL_BACK);
    mNucleonNode->draw(painter);
    glDisable(GL_CULL_FACE);

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    painter->modelViewMatrix().pop();
}

//______________________________________________________________________________
void YS3DView::DrawNucleonAndQuarks(QGLPainter *painter, const QVector3D &posn)
{
   // draw a nucleon with quarks inside
    DrawQuark(painter, posn, Qt::red);
    DrawQuark(painter, posn, Qt::blue);
    DrawQuark(painter, posn, Qt::green);
    DrawNucleon(painter, posn);
}

//______________________________________________________________________________
void YS3DView::DrawNucleus(QGLPainter *painter, const QVector3D &posn, YSNucleus *nucleus)
{
    // draw nucleus

    QVector3D * nucleons =  nucleus->GetNucleons();

    for (int index = 0; index < nucleus->A(); index++) {
        QVector3D pos = nucleons[index] + posn;
        DrawNucleonAndQuarks(painter, pos);
    }

    painter->modelViewMatrix().push();
    painter->setFaceColor(QGL::AllFaces, QColor(0, 160, 202, 125));
    painter->setStandardEffect(QGL::LitDecalTexture2D);
    glBindTexture(GL_TEXTURE_2D, mFBO->texture());
    glEnable(GL_TEXTURE_2D);

    painter->modelViewMatrix().translate(posn);

    if (nucleus->A() != 1) {
        glCullFace(GL_FRONT);
        glEnable(GL_CULL_FACE);
        mNucleusEnv->draw(painter);
        glCullFace(GL_BACK);
        mNucleusEnv->draw(painter);
        glDisable(GL_CULL_FACE);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    painter->modelViewMatrix().pop();
}

//______________________________________________________________________________
void YS3DView::DrawQuark(QGLPainter *painter, const QVector3D &posn, const QColor color)
{
    // Draw a quark inside a nucleon
    painter->modelViewMatrix().push();

    painter->setFaceColor(QGL::AllFaces, QColor(color));
    painter->setStandardEffect(QGL::LitDecalTexture2D);
    glBindTexture(GL_TEXTURE_2D, mFBO->texture());
    glEnable(GL_TEXTURE_2D);

    qreal r     = (qreal)qrand() / (qreal)RAND_MAX * YSNucleus::kgProtonRadius;
    qreal phi   = (qreal)qrand() / (qreal)RAND_MAX * qDegreesToRadians(360.);
    qreal theta = (qreal)qrand() / (qreal)RAND_MAX * qDegreesToRadians(180.);
    qreal rx = r * qCos(phi) * qSin(theta) + posn.x();
    qreal ry = r * qSin(phi) * qSin(theta) + posn.y();
    qreal rz = r * qCos(theta) + posn.z();

    QVector3D posq(rx, ry, rz);

    painter->modelViewMatrix().translate(posq);

    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);
    mQuarkNode->draw(painter);
    glCullFace(GL_BACK);
    mQuarkNode->draw(painter);
    glDisable(GL_CULL_FACE);

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    painter->modelViewMatrix().pop();

}

//______________________________________________________________________________
void YS3DView::InitNucleonAndQuark(QGLBuilder &builder)
{
    // define nucleon and quark

    // the nucleon
    builder.newSection(QGL::Faceted);
    builder << QGLSphere(YSNucleus::kgProtonRadius * 2);
    mNucleonNode = builder.currentNode();
    mNucleonNode->setObjectName("nucleon");

    // the quark
    builder.newSection();
    builder << QGLSphere(YSNucleus::kgProtonRadius / 20.); // the quark is in fact 1000 times smaller than the nucleon
    mQuarkNode = builder.currentNode();
    mQuarkNode->setObjectName("quark");
}

//______________________________________________________________________________
//void YS3DView::mousePressEvent(QMouseEvent *event)
//{
//    // select impact parameter by dragging one nucleus
//    qDebug() << "YS3DView::mousePressEvent" << event->x() << event->y();
//}

//______________________________________________________________________________
void YS3DView::paintGL(QGLPainter *painter)
{
    // draws the nucleus made of nucleons made of quarks

    painter->modelViewMatrix().push();
    painter->projectionMatrix().push();
    painter->pushSurface(&mFBOSurface);

    painter->setCamera(mInnerCamera);
    painter->setFaceColor(QGL::AllFaces, QColor(170, 202, 0));
    painter->setStandardEffect(QGL::LitMaterial);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    painter->popSurface();
    painter->projectionMatrix().pop();
    painter->modelViewMatrix().pop();

    // drawing sequence of the quarks, nucleons, nucleus draw from back to front
    qreal unzoom;
    if (mCollision)
        unzoom = -100.;
    else
        unzoom = -50;

    // unzoom
    QMatrix4x4 mat = painter->worldMatrix();
     QVector4D row = mat.row(2);
     qreal row23 = row[2,3];
     if ( row23 == 0 ) {
         row.setW(unzoom);
         mat.setRow(2, row);
         painter->modelViewMatrix() = mat;
     }

    //scale x, y, z
    QVector3D scaleV(1, 1, 1);
    painter->modelViewMatrix().scale(scaleV);

    qreal x1displacement = 0.0, x2displacement = 0.0;
    qreal y1displacement = -mb / 2., y2displacement = mb / 2.;
    if (mCollision) {
        x1displacement = mCollDist;
        x2displacement = -mCollDist;
    }
    qreal zoomScale = mat(2,3);
    if (zoomScale > 1.0) { // if zoom too large show only one nucleon
        QVector3D nucleonpos(0., 0., 0.);
        DrawNucleonAndQuarks(painter, nucleonpos);
    } else {
        QVector3D nucleus1pos(x1displacement - mNpos, y1displacement, 0.);
        if (mCollision && zoomScale > -100)
            nucleus1pos.setX(0);
        DrawNucleus(painter, nucleus1pos, mNucleus1);
        if (mCollision && zoomScale <= -100) {
            QVector3D nucleus2pos(x2displacement + mNpos, y2displacement, 0.);
                DrawNucleus(painter, nucleus2pos, mNucleus2);
        }
    }
}
