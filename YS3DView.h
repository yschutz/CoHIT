//
//  YS3dView.h
//  GL view of a nucleus
//
//  Created by Yves Schutz on 15/12/13.
//  Copyright (c) 2013 Yves Schutz. All rights reserved.
//

#ifndef YS3dView_H
#define YS3dView_H

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

class YS3dView : public QGLView
{
    Q_OBJECT
    Q_PROPERTY(qreal QRot READ QRot WRITE SetQRot)
    Q_PROPERTY(qreal NTransIn READ NTransIn WRITE SetNTransIn)
    Q_PROPERTY(qreal NTransOut READ NTransOut WRITE SetNTransOut)

public:
    explicit YS3dView(YSMenu *parent, YSNucleus *nucleus);
    explicit YS3dView(YSMenu *parent, YSCollision *collision);

    virtual  ~YS3dView();

    qreal QRot() const { return mQpos; }
    void  SetQRot(qreal pos) { mQpos = pos; update(); }
    qreal NTransIn() const { return mNPosIn; }
    qreal NTransOut() const { return mNPosOut; }
    void  Setb(qreal b) { mb = b; }
    void  SetNTransIn(qreal pos) { mNPosIn = pos; update(); }
    void  SetNTransOut(qreal pos) { mNPosOut = pos; update(); }
    void  ReDraw(qreal gamma1, qreal gamma2, qreal beta1, qreal beta2);


protected:
    void initializeGL(QGLPainter * painter);
    void keyPressEvent(QKeyEvent * event);
    void paintGL(QGLPainter *painter);
//    void mousePressEvent(QMouseEvent * event);

signals:

public slots:

private:
    void DrawNucleon(QGLPainter *painter, const QVector3D &posn, bool w);
    void DrawNucleonAndQuarks(QGLPainter *painter, const QVector3D &posn, bool w);
    void DrawNucleus(QGLPainter * painter, const QVector3D &posn, YSNucleus *nucleus);
    void DrawParticipants(QGLPainter * painter, const QVector3D &posn, YSNucleus *nucleus);
    void DrawQuark(QGLPainter *painter, const QVector3D &posn, const QColor color);
    void InitNucleonAndQuark(QGLBuilder &builder);

    QPropertyAnimation          *mAnimInColl;                             // nucleons motion toward collision
    QPropertyAnimation          *mAnimOutColl;                            // nucleons motion out of collision
    qreal                       mb;                                       // impact parameter
    bool                        mCollision;                               // nucleus or collision
    qreal                       mCollDist;                                // distance between the 2 nuclei before collision
    QGLCamera                   *mInnerCamera;                            // camera for the nested scene
    QOpenGLFramebufferObject    *mFBO;
    QGLFramebufferObjectSurface mFBOSurface;
    YSImpactParameterSetter     *mIps;  // impact parameter widget
    qreal                       mNPosIn;                                    // quark position in he animation
    qreal                       mNPosOut;                                    // quark position in he animation
    QGLSceneNode                *mNucleonNode, *mNucleusEnv, *mScene;     // nested scene: quark in nucleon in scene
    YSNucleus                   *mNucleus1;                               // one of the nuclei to be drawn
    YSNucleus                   *mNucleus2;                               // one of the nuclei to be drawn
    YSMenu                      *mParent;                                 // parent menu
    QPropertyAnimation          *mQanimation;                             // quarks motion
    qreal                       mQpos;                                    // quark position in he animation
    QGLSceneNode                *mQuarkNode;                              // the quark node in the scene
    QVector3D                   mScaleV1;                                 // scale matrix of the view of nuc1
    QVector3D                   mScaleV2;                                 // scale matrix of the view of nuc2
};

#endif // YS3dView_H
