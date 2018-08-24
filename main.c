#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <fcntl.h>

#define HIJO 0
int main(int argc, char *argv[]){
    int prueba = 1, i = 0;
    int usoCPU, file;

    const char logs_file[] = "log.txt";
    while(prueba){
        
        int pid = fork();
        if (pid < 0) exit(1);
        if(pid == HIJO) execl("./obtenerUso.sh", "",NULL);
        
        //main process
        if (i < 2)
            i++;
        else
            prueba = 0;


        sleep(10);
        //decidir
        if( (file = open(logs_file, O_RDONLY)) == -1) exit(-1);
        
        printf("CPU %d \n", usoCPU);
        sleep(10);
    }


    return 0;
}