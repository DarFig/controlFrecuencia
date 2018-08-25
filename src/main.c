#include "../include/utils.h"


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
        if(pid == HIJO){ execl("./tools/obtenerUso.sh", "",NULL); exit(0);}
        
        //main process
        


        sleep(15);
        
        
        usoCPU = read_last_line_from_log(file);
        printf("CPU %d\n", usoCPU);
        if(usoCPU < 5)
            set_governor(POWERSAVE);
        else if(usoCPU < 90){
            set_governor(USERSPACE);
            if(usoCPU < 20)
                set_frequency(UNO_CINCO_GHZ);
            else
                set_frequency(DOS_GHZ);
        }else
            set_governor(ONDEMAND);


        if (i < 2)
            i++;
        else
            prueba = 0;
        //sleep(10);
    }

    fclose(file);
    return 0;
}