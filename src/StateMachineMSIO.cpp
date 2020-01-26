/**
* @file StateMachineMSIO.cpp
* @brief State machine to the protocol MSIO
* @author Jairo Ortega Calderon
* @date 20/09/19
**/

#include "../include/StateMachineMSIO.h"

StateMachineMSIO::StateMachineMSIO()
{
    this->actualState = invalid;
}

enum States StateMachineMSIO::getState(Condition _actionResult, States _actualState)
{
    switch (_actionResult)
    {
    //readMissCPU
    case 0:
        switch (_actualState)
        {
        case modified:
            actualState = shared;
            dprintf("Do write Back. \n");
            dprintf("Write read_miss on bus. \n");
            break;
        case invalid:
            actualState = shared;
            dprintf("Write read_miss on bus. \n");
            break;
        case shared:
            dprintf("Write read_miss on bus. \n");
            break;
        default:
            actualState = modified;
            dprintf("Write read_miss on bus. \n");
            break;
        }
        break;
    //writeMissCPU
    case 1:
        switch (_actualState)
        {
        case modified:
            dprintf("Do write Back. \n");
            dprintf("Write write_miss on bus. \n");
            break;
        case invalid:
            dprintf("Write write_miss on bus. \n");
            actualState = modified;
            break;
        case shared:
            actualState = modified;
            dprintf("Write write_miss on bus. \n");
            break;
        default:
            break;
        }
        break;
    //writeHitCPU
    case 2:
        switch (_actualState)
        {
        case shared:
            actualState = modified;
            dprintf("Write invalidate on bus. \n");
            break;
        case owned:
            actualState = modified;
            dprintf("Write invalidate on bus. \n");
            break;
        case invalid:
            actualState = modified;
            dprintf("Write invalidate on bus. \n");
            break;
        default:
            break;
        }
        break;
    //readMissBUS
    case 3:
        switch (_actualState)
        {
        case modified:
            actualState = owned;
            break;
        default:
            break;
        }
        break;
    //writeMissBUS
    case 4:
        switch (_actualState)
        {
        case modified:
            actualState = invalid;
            dprintf("Do write Back. \n");
            break;
        case owned:
            actualState = invalid;
            dprintf("Do write Back. \n");
            break;
        default:
            actualState = invalid;
            break;
        }
        break;
    //invalidateBUS
    default:
        actualState = invalid;
        break;
    }
    return actualState;
}