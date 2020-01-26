#ifndef _INCLUDE_STATEMACHINEMSIO_H_
#define _INCLUDE_STATEMACHINEMSIO_H_

#include "Utils.h"

/**
 * @brief Struct for the states of the cache line
 */
enum States
{
    modified,
    invalid,
    shared,
    owned
};
/**
 * @brief Type of action
 */
enum Condition
{
    readMissCPU,
    writeMissCPU,
    writeHitCPU,
    readMissBUS,
    writeMissBUS,
    invalidateBUS,
};

/**
* @file StateMachineMSIO.h
* @brief State machine to the protocol MSIO
* @author Jairo Ortega Calderon
* @date 20/09/19
**/
class StateMachineMSIO
{
    private:
        States actualState;
        Condition actionResult;

    public:
        /**
         * @brief Construct a new State Machine MSIO
         */
        StateMachineMSIO();
        /**
         * @brief Get the next state from the actual
         * @param _actionResult type of action, like readMissCPU
         * @param _actualState Actual state of the line
         * @return enum States Next state
         */
        enum States getState(Condition _actionResult, States _actualState);
};

#endif