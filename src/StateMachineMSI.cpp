
#include "../include/StateMachineMSI.h"

StateMachineMSI::StateMachineMSI()
{
    this->actualState = invalid;
}


enum States StateMachineMSI::getActualState(){
    return this->actualState;
}

enum States StateMachineMSI::getState(Condition _actionResult, States _actualState){
    switch (_actionResult){
        //readMissCPU
        case 0:
            switch (_actualState){
                case modified:
                    actualState = shared;
                    printf("Hacer write Back \n");
                    printf("Escribir en el bus read miss \n");
                    break;
                case invalid:
                    actualState = shared;
                    printf("Escribir en el bus read miss \n");
                    break;
                case shared:
                    printf("Escribir en el bus read miss \n");
                    break;        
                default:
                    break;
                }
            break;
        //readHitCPU
        case 1:
            //Si hay un read hit no pasa nada, pues se mantendría el estado y nunca puede ser Invalid
            printf("Leer localmente \n");
            break;
        //writeMissCPU
        case 2:
            switch (_actualState){
                case modified:
                    printf("Hacer write Back \n");
                    printf("Escribir en el bus write miss \n");
                    break;
                case invalid:
                    printf("Escribir en el bus write miss \n");
                    actualState = modified;
                    break;
                case shared:
                    actualState = modified;
                    printf("Escribir en el bus write miss \n");
                    break;            
                default:
                    break;
            }
            break;
        //writeHitCPU
        case 3:
            switch (_actualState){
                case shared:
                    actualState = modified;
                    printf("Escribir en el bus invalidate \n");
                    break;                
                default:
                    //Solo puede ser modified
                    printf("Escribir datos en el cache \n");
                    break;
                }
            break;
        //readMissBUS
        case 4:
            switch (_actualState){
                case modified:
                    actualState = shared;
                    printf("Hacer write Back \n");
                    break;                
                default:
                    //Solo puede ser shared. No se hace nada.
                    break;
            }
            break;
        //writeMissBUS
        case 5:
            switch (_actualState){
                case modified:
                    actualState = invalid;
                    break;                
                default:
                    //Solo puede ser shared. No se hace nada.
                    actualState = invalid;
                    printf("Hacer write Back \n");
                    break;
            }
            break;
        //invalidateBUS
        default:
            //Solo puede ser shared.
            actualState = invalid;
            break;
    }
    return actualState;
}