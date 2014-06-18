//
//  YSWoodSaxon.h
//  The Wood Saxon function
//
//  Created by Yves Schutz on 03/01/14.
//  Copyright (c) 2014 Yves Schutz. All rights reserved.
//

#ifndef YSWOODSAXON_H
#define YSWOODSAXON_H

#include <QObject>
#include <QStringList>
#include <QVector>

#include "YSF1.h"

class YSWoodSaxon : public YSF1
{
    Q_OBJECT

public:
    explicit YSWoodSaxon();
    virtual ~YSWoodSaxon() {;}

    enum YSWSType {
        kWS, kRWS
    };

    qreal Eval(qreal) const;
    void  Print() const;
    void  SetType(YSWSType type) { mType = type; }

private:
    YSWSType        mType;                            // type of function WS (default) or rWS
};

#endif // YSWOODSAXON_H
