//
//  YSCrossSectionpp.h
// calculates the pp cross section from systematics data in mb energy (√s) in GeV
//
//  Created by Yves Schutz on 06/03/14.
//  Copyright (c) 2014 Yves Schutz. All rights reserved.
//

#ifndef YSCROSSSECTIONPP_H
#define YSCROSSSECTIONPP_H

#include "YSF1.h"

class QStringList;

class YSCrossSectionpp : public YSF1
{

public:
    enum YSCSType {
        kElastic, kInelastic, kTotal
    };

    explicit YSCrossSectionpp(QObject *parent = 0);
    virtual ~YSCrossSectionpp();

    void            Draw(QCustomPlot *cp);
    qreal           Eval(qreal) const;
    void            Print() const;
    void            SetType(YSCSType);

private:
    YSCSType        mType;  // type of cross section anong elastic, inelastic and total
};

#endif // YSCROSSSECTIONPP_H
