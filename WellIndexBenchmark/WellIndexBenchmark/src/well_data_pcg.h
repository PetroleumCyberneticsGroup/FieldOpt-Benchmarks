#ifndef WELL_DATA_PCG_H
#define WELL_DATA_PCG_H

#include <QString>
#include <QStringList>

class WellDataPCG
{
public:
    WellDataPCG();

    QStringList well_dirs_paths;
    QStringList well_dirs_names;
    QStringList well_file_names;
};

#endif // WELL_DATA_PCG_H
