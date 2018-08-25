#ifndef UTILS_H
#define UTILS_H

//las cabeceras las pongo en un solo fichero para no liarme
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <fcntl.h>

#define SALTO_ATRAS -5

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




#endif