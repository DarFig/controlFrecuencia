#include "../include/utils.h"
#include "../include/doSignals.h"

int main(int argc, char *argv[]){
    
    //signals time 
    if(signal(SIGINT, do_SIGINT) == SIG_ERR) {
        perror("signal");
        exit(-1);
    }
    
    int usoCPU;
    FILE *file;

    const char logs_file[] = "./files/log.txt";
    if( (file = fopen(logs_file, "r")) == NULL){
            perror(logs_file);
            exit(-1);
    }

    while(continuar){
        
        int pid = fork();
        if (pid < 0) exit(1);
        if(pid == HIJO){ execl("./tools/obtenerUso.sh", "",NULL); exit(0);}
        
        
        sleep(15);
        
        
        usoCPU = read_last_line_from_log(file);
        run_decisions_model(usoCPU);      
        
    }
    
    fclose(file);
    if(actualConfig == CORES_OCHO )
        switch_cores();
    set_governor(ONDEMAND);//default on servers

    return 0;
}