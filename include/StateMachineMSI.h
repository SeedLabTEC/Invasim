#ifndef _INCLUDE_STATEMACHINEMSI_H_
#define _INCLUDE_STATEMACHINEMSI_H_

#include <stdio.h>

enum States {
    modified,
    invalid,
    shared,
    owned
};

enum Condition {
    readMissCPU,
    readHitCPU,
    writeMissCPU,
    writeHitCPU,
    readMissBUS,
    writeMissBUS,
    invalidateBUS,
};

class StateMachineMSI
{
private:
    States actualState;
    Condition actionResult;



public:
    StateMachineMSI();
    enum States getState(Condition _actionResult, States _actualState);
    enum States getActualState();
};



#endif