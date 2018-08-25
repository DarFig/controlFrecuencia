#ifndef DOSIGNALS_H
#define DOSIGNALS_H

#include <signal.h>


int continuar = 1;


void do_SIGINT(int sig){
    //salida controlada
    continuar = 0;    
}
/*void do_SIGKILL(int sig){
    continuar = 0;    
}*/


#endif