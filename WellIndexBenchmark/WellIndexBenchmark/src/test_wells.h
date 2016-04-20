#ifndef TESTWELLS_H
#define TESTWELLS_H

#include "well_rms.h"
#include "well_pcg.h"

class TestWells
{
public:
    TestWells();

    WellPCG well_pcg;
    WellRMS well_rms;
};

#endif // TESTWELLS_H
