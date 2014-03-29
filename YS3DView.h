//
//  YS3DView.h
//  GL view of a nucleus
//
//  Created by Yves Schutz on 15/12/13.
//  Copyright (c) 2013 Yves Schutz. All rights reserved.
//

#ifndef YS3DVIEW_H
#define YS3DVIEW_H

#include <QGLView>
#include <QGLFramebufferObjectSurface>

class QGLBuilder;
class QGLCamera;
class QGLFramebufferObject;
class QPropertyAnimation;
class QVector3D;

class YSCollision;
class YSImpactParameterSetter;
class YSMenu;
class YSNucleus;

class YS3DView : public QGLView
{
    Q_OBJECT
    Q_PROPERTY(qreal QRot READ QRot WRITE SetQRot)
    Q_PROPERTY(qreal NTrans READ NTrans WRITE SetNTrans)

public:
    explicit YS3DView(YSMenu *parent, YSNucleus *nucleus);
    explicit YS3DView(YSMenu *parent, YSCollision *collision);

    virtual  ~YS3DView();

    qreal QRot() const { return mQpos; }
    void  SetQRot(qreal pos) { mQpos = pos; update(); }
    qreal NTrans() const { return mNpos; }
    void  Setb(qreal b) { mb = b; }
    void  SetNTrans(qreal pos) { mNpos = pos; update(); }


protected:
    void initializeGL(QGLPainter * painter);
    void keyPressEvent(QKeyEvent * event);
    void paintGL(QGLPainter *painter);
//    void mousePressEvent(QMouseEvent * event);

signals:

public slots:

private:
    void DrawNucleon(QGLPainter *painter, const QVector3D &posn);
    void DrawNucleonAndQuarks(QGLPainter *painter, const QVector3D &posn);
    void DrawNucleus(QGLPainter * painter, const QVector3D &posn, YSNucleus *nucleus);
    void DrawQuark(QGLPainter *painter, const QVector3D &posn, const QColor color);
    void InitNucleonAndQuark(QGLBuilder &builder);

    qreal                       mb;                                       // impact parameter
    bool                        mCollision;                               // nucleus or collision
    qreal                       mCollDist;                                // distance between the 2 nuclei before collision
    QGLCamera                   *mInnerCamera;                            // camera for the nested scene
    QOpenGLFramebufferObject    *mFBO;
    QGLFramebufferObjectSurface mFBOSurface;
    YSImpactParameterSetter     *mIps;  // impact parameter widget
    QPropertyAnimation          *mNanimation;                             // nucleons motion
    qreal                       mNpos;                                    // quark position in he animation
    QGLSceneNode                *mNucleonNode, *mNucleusEnv, *mScene;     // nested scene: quark in nucleon in scene
    YSNucleus                   *mNucleus1;                               // one of the nuclei to be drawn
    YSNucleus                   *mNucleus2;                               // one of the nuclei to be drawn
    YSMenu                      *mParent;                                 // parent menu
    QPropertyAnimation          *mQanimation;                             // quarks motion
    qreal                       mQpos;                                    // quark position in he animation
    QGLSceneNode                *mQuarkNode;                              // the quark node in the scene
};

#endif // YS3DVIEW_H
