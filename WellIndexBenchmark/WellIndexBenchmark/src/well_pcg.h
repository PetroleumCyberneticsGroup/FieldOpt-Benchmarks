#ifndef WELL_PCG_H
#define WELL_PCG_H

#include <QString>

class WellPCG
{
public:
    WellPCG(){}
    QString name() const { return name_;}
    QStringList files();
};

#endif // WELL_PCG_H
