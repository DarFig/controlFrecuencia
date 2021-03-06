#ifndef UTILS_H
#define UTILS_H

//las cabeceras las pongo en un solo fichero para no liarme
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <fcntl.h>

#include "../include/define_limits.h"



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
static int check_usage0 = 0;//evita bajar de frecuencia por un 0 irregular 



static int is_not_end_line(char caracter){
    return (caracter != '\n' && caracter != '.' && caracter != EOF);
}
static int is_not_omitted_caracter(char caracter){
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
      
        set_frequency(DOS_GHZ);
        int pidd = fork();
        if (pidd < 0) exit(1);
        if(pidd == HIJO){ 
            execl("./tools/cores_down.sh", "",NULL); exit(0);
        }
        sleep(5);
        actualConfig = CORES_OCHO;
      
    }else{
        int pidd = fork();
        if (pidd < 0) exit(1);
        if(pidd == HIJO){ 
            execl("./tools/cores_up.sh", "",NULL); exit(0);
        }
        sleep(5);
        actualConfig = CORES_ALL;
        set_frequency(UNO_CINCO_GHZ);
    }

}
static void run_decisions_uno(int cpu_usage){
    if(cpu_usage > UP_ONE){
        set_frequency(UNO_CINCO_GHZ);
    } 
}
static void run_decisions_uno_cinco(int cpu_usage){
    if(cpu_usage < DOWN_ONE_FIVE){       
        switch_cores();
    }else if(cpu_usage > UP_ONE_FIVE){
        set_frequency(DOS_GHZ);
    } 
}
static void run_decisions_dos(int cpu_usage){
    if(cpu_usage < DOWN_DOS){
        set_frequency(UNO_CINCO_GHZ);
    }else if(cpu_usage > UP_DOS){
        set_governor(ONDEMAND);
    }
}
static void run_decisions_cores(int cpu_usage){
    if(cpu_usage > UP_CORES){
        switch_cores();
        
    }        
}
static void run_decisions_ondemand(int cpu_usage){
    if(cpu_usage < DOWN_ONDEMAND){
        set_governor(USERSPACE);
        set_frequency(DOS_GHZ);
    }
}
static void run_decisions_performance(int cpu_usage){
    if(cpu_usage < DOWN_PERFORMANCE)
        set_governor(ONDEMAND);
}

void run_decisions_model(int cpu_usage){
    if(actualConfig == CORES_OCHO){
        run_decisions_cores(cpu_usage);
    }else if(cpu_usage > SLEEP_LIMIT || check_usage0 == 1){
        check_usage0 = 0;
        if(actualGovernor == USERSPACE){
            switch (actualFrequency)
            {   
                case UN_GHZ:
                    run_decisions_uno(cpu_usage);
                    break;
                case UNO_CINCO_GHZ:
                    run_decisions_uno_cinco(cpu_usage);
                    break;
                case DOS_GHZ:
                    run_decisions_dos(cpu_usage);
                    break;    
                default:
                    break;
            }      
        }else if(actualGovernor == ONDEMAND){
            run_decisions_ondemand(cpu_usage);     
        }else if(actualGovernor == PERFORMANCE){
            run_decisions_performance(cpu_usage);      
        }
        
    }else if(cpu_usage <= SLEEP_LIMIT){
        check_usage0 = 1;
        sleep(20);
    }

}


#endif