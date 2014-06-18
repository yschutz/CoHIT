//
//  YSH1.cpp
//  A basic histogram
//
//  Created by Yves Schutz on 10/05/14.
//  Copyright (c) 2014 Yves Schutz. All rights reserved.

#ifndef YSH1_H
#define YSH1_H

#include <QObject>
#include <QVector>

#include "YSDrawableObject.h"

class QCustomPlot;



class YSH1 : public YSDrawableObject
{

public:
    explicit YSH1(QString name, int bins, qreal xmin, qreal xmax);
             YSH1(const YSH1 &);
    virtual ~YSH1() {;}

    void            Copy(QObject &obj) const;
    void            Fill(qreal x, qreal weight = 1);
    qreal           GetYMax();
    bool            IsH1() { return true; }

private:

};

#endif // YSH1_H
