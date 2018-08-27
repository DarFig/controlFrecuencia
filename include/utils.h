#ifndef UTILS_H
#define UTILS_H

//las cabeceras las pongo en un solo fichero para no liarme
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <fcntl.h>

#define L_DOWN 10
#define L_MEDIUM 50
#define L_UP 90


#define SALTO_ATRAS -3 
#define HIJO 0

//configs cres
enum {CORES_OCHO, CORES_ALL};

//some governors in linux
enum {POWERSAVE = 0, USERSPACE = 1, ONDEMAND = 2, PERFORMANCE = 3};

//some cpu frequencies
enum {UN_GHZ = 1, UNO_CINCO_GHZ = 2, DOS_GHZ = 3, OTHER = 4};

static int actualGovernor = ONDEMAND;
static int actualFrequency = OTHER;
static int actualConfig = CORES_ALL;



int is_not_end_line(char caracter){
    return (caracter != '\n' && caracter != '.' && caracter != EOF);
}
int is_not_omitted_caracter(char caracter){
    return (caracter != '\n' && caracter !='.');
}

int read_last_line_from_log(FILE* file){
    char linea[10];
    char caracter;
    int j = 0;

    fseek(file, SALTO_ATRAS, SEEK_END);
    fread(&caracter, sizeof(char), 1, file);
    do{
        if(is_not_omitted_caracter(caracter)){
            linea[j] = caracter;
            j++;
        }
        fread(&caracter, sizeof(char), 1, file); 

    }while(is_not_end_line(caracter));
    linea[j] = '\0';

    return atoi(linea);
}

void set_governor(int _governorFlag){
    if(actualGovernor != _governorFlag){
        if(_governorFlag == POWERSAVE){
            int pidd = fork();
            if (pidd < 0) exit(1);
            if(pidd == HIJO){ 
                execl("./tools/powersave.sh", "",NULL); exit(0);}
            
            sleep(2); 
        }else
        if(_governorFlag == USERSPACE){
            int pidd = fork();
            if (pidd < 0) exit(1);
            if(pidd == HIJO){ 
                execl("./tools/userspace.sh", "",NULL); exit(0);}
            
            sleep(2);
        }else
        if(_governorFlag == ONDEMAND){
            int pidd = fork();
            if (pidd < 0) exit(1);
            if(pidd == HIJO){ 
                execl("./tools/ondemand.sh", "",NULL); exit(0);}
            
            sleep(2);
        }else
        if(_governorFlag == PERFORMANCE){
            int pidd = fork();
            if (pidd < 0) exit(1);
            if(pidd == HIJO){ 
                execl("./tools/performance.sh", "",NULL); exit(0);} 
            sleep(2);     
        }
        actualGovernor = _governorFlag;
    }
}

void set_frequency(int _frequencyFlag){
    if(actualFrequency != _frequencyFlag){
        if(_frequencyFlag == UN_GHZ){
            int pidd = fork();
            if (pidd < 0) exit(1);
            if(pidd == HIJO){ 
                execl("./tools/unghz.sh", "",NULL); exit(0);
            }
            sleep(1);
        }else
        if(_frequencyFlag == UNO_CINCO_GHZ){
            int pidd = fork();
            if (pidd < 0) exit(1);
            if(pidd == HIJO){ 
                execl("./tools/unoconcincoghz.sh", "",NULL); exit(0);
            }
            sleep(1);
        }else
        if(_frequencyFlag == DOS_GHZ){
            int pidd = fork();
            if (pidd < 0) exit(1);
            if(pidd == HIJO){ 
                execl("./tools/dosghz.sh", "",NULL); exit(0);
            }
            sleep(1);
        }
        actualFrequency = _frequencyFlag;
    }
}

void switch_cores(){
    if(actualConfig != CORES_OCHO){
        int pidd = fork();
        if (pidd < 0) exit(1);
        if(pidd == HIJO){ 
            execl("./tools/shutdown_cores.sh", "",NULL); exit(0);
        }
        sleep(5);
        actualConfig = CORES_OCHO;
    }else{
        int pidd = fork();
        if (pidd < 0) exit(1);
        if(pidd == HIJO){ 
            execl("./tools/shutdown_cores.sh", "",NULL); exit(0);
        }
        sleep(5);
        actualConfig = CORES_ALL;
    }

}

void run_decisions_model(int cpu_usage){   
    if(actualGovernor == USERSPACE){
        switch (actualFrequency)
        {
            case UNO_CINCO_GHZ:
                
                break;
            case DOS:
                
                break;
        
            default:
                break;
        }
        
    }else if(actualGovernor == ONDEMAND){

        
    }else if(actualGovernor == PERFORMANCE){

        
    }
   

}


#endif