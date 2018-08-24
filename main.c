#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <fcntl.h>

#define HIJO 0
int main(int argc, char *argv[]){
    int prueba = 1, i = 0, j = 0;
    int usoCPU;
    char caracter;
    char linea[10];
    FILE *file;

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


        sleep(20);
        
        if( (file = fopen(logs_file, "r")) == NULL){
            perror(logs_file);
            exit(-1);
        }
        j = 0;
        fseek(file, -5, SEEK_END);
        fread(&caracter, sizeof(char), 1, file);
        do{
            if(caracter != '\n' && caracter !='.'){
                linea[j] = caracter;
                j++;
            }
            fread(&caracter, sizeof(char), 1, file); 
        }while(caracter != '\n' && caracter != '.' && caracter != EOF);
        linea[j] = '\0';

        printf("CPU %s\n", linea);
        //sleep(10);
    }

    fclose(file);
    return 0;
}