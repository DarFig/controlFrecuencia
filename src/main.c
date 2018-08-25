#include "../include/utils.h"

#define HIJO 0
int main(int argc, char *argv[]){
    int prueba = 1, i = 0; 
    int usoCPU;

    FILE *file;

    const char logs_file[] = "./files/log.txt";
    if( (file = fopen(logs_file, "r")) == NULL){
            perror(logs_file);
            exit(-1);
    }

    while(prueba){
        
        int pid = fork();
        if (pid < 0) exit(1);
        if(pid == HIJO) execl("./tools/obtenerUso.sh", "",NULL);
        
        //main process
        if (i < 2)
            i++;
        else
            prueba = 0;


        sleep(20);
        
        
        usoCPU = read_last_line_from_log(file);
        printf("CPU %d\n", usoCPU);
        
        //sleep(10);
    }

    fclose(file);
    return 0;
}