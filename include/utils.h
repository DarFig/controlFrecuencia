#ifndef UTILS_H
#define UTILS_H

//las cabeceras las pongo en un solo fichero para no liarme
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <fcntl.h>




#define SALTO_ATRAS -3 
#define HIJO 0

int check_switch = 0; 

//configs cres
enum {CORES_OCHO, CORES_ALL};

//some governors in linux
enum {POWERSAVE = 0, USERSPACE = 1, ONDEMAND = 2, PERFORMANCE = 3};

//some cpu frequencies
enum {UN_GHZ = 1, UNO_CINCO_GHZ = 2, DOS_GHZ = 3, OTHER = 4};

static int actualGovernor = ONDEMAND;
static int actualFrequency = OTHER;
static int actualConfig = CORES_ALL;



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
        if(check_switch){
            set_frequency(DOS_GHZ);
            int pidd = fork();
            if (pidd < 0) exit(1);
            if(pidd == HIJO){ 
                execl("./tools/cores_down.sh", "",NULL); exit(0);
            }
            sleep(5);
            actualConfig = CORES_OCHO;
            check_switch = 0;
        }else{
            sleep(20);
            check_switch = 1;
        }

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
    if(cpu_usage > 36){
        set_frequency(UNO_CINCO_GHZ);
    } 
}
static void run_decisions_uno_cinco(int cpu_usage){
    if(cpu_usage < 10){       
        switch_cores();
    }else if(cpu_usage > 80){
        set_frequency(DOS_GHZ);
    }
    
    if(cpu_usage > 10 && check_switch == 1)
        check_switch = 0;
    
}
static void run_decisions_dos(int cpu_usage){
    if(cpu_usage < 40){
        set_frequency(UNO_CINCO_GHZ);
    }else if(cpu_usage > 90){
        set_governor(ONDEMAND);
    }
}
static void run_decisions_cores(int cpu_usage){
    if(cpu_usage > 80){
        switch_cores();
        
    }        
}
static void run_decisions_ondemand(int cpu_usage){
    if(cpu_usage < 75){
        set_governor(USERSPACE);
        set_frequency(DOS_GHZ);
    }//else if(cpu_usage > 89)
      //  set_governor(PERFORMANCE);
}
static void run_decisions_performance(int cpu_usage){
    if(cpu_usage < 85)
        set_governor(ONDEMAND);
}

void run_decisions_model(int cpu_usage){
    if(actualConfig == CORES_OCHO){
        run_decisions_cores(cpu_usage);
    }else if(actualGovernor == USERSPACE){
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
   

}


#endif