#include "split.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* 
* Calcula la cantidad de substring, separados por el separador pasado por parametro, que se encuentran en el string pasado por parametro.
* Pre: -
* Pos: Devuelve la cantidad de substrings que hay en el string pasado por parametro
*/
size_t calcular_cantidad_substrings(const char* string, char separador){
    size_t cantidad = 1;
    for (int i = 0; string[i] != '\0'; i++){
        if (string[i] == separador){
            cantidad++;
        }
    }
    return cantidad;
}

/* 
* Calcula el tamaño de un substring, empezando a contar desde su inicio pasado por parametro hasta que se encuentre con un caracter
* igual al pasado por parametro, el cual significa que ya termino un substring y comienza otro.
* Pre: -
* Pos: Devuelve el tamaño del substring
*/
int calcular_tamanio_substring(const char* string, int inicio_substring, char separador){
    int tamanio = 1;
    int i = inicio_substring;
    while (string[i] != separador && string[i] != '\0'){
        tamanio++;
        i++;
    }
    return tamanio;
}

/* 
* Se copia en memoria reservada en el heap el substring del string pasado por parametro que comienza desde el inicio pasado por parametro
* hasta el tamaño calculado anteriormente pasado por parametro
* Pre: -
* Pos: Devuelve el substring con los caracteres correspondientes copiados del string pasado por parametro, si algo salio mal devuelve NULL
*/
char* copiar_substring(const char* string, int tamanio_substring, int inicio_substring){
    int i = inicio_substring;
    int j = 0;
    char* substring = malloc(sizeof(char)*(size_t)tamanio_substring);
    if (!substring){
        return NULL;
    }
    while( ( j < tamanio_substring - 1 ) ){
        substring[j] = string[i];
        j++;
        i++;
    }
    substring[j] = '\0';
    return substring;
}

/*
* Pre: -  
* Pos: Libera los substring y el vector de substrings
*/
void liberar_vector(char** vector){
    if(vector){
        for (int i = 0; vector[i] != 0; i++){
            free(vector[i]);
        }
        free(vector);
    }
}

char** split(const char* string, char separador){
    if( string == NULL){
        return NULL ;
    }
    
    size_t cantidad_substrings = calcular_cantidad_substrings(string, separador);
    int i;
    int inicio_substring = 0;
    int tamanio_substring = 0;

    char** vector_split = calloc((cantidad_substrings+1), sizeof(char*));
    if (!vector_split){
        return NULL;
    }
    
    for (i = 0; i < cantidad_substrings; i++){

        inicio_substring = (inicio_substring+tamanio_substring);

        tamanio_substring = calcular_tamanio_substring(string, inicio_substring, separador);

        char* substring = copiar_substring(string, tamanio_substring, inicio_substring);
        if (!substring){
            liberar_vector(vector_split);
            return NULL;
        }

        vector_split[i] = substring;
    }
    vector_split[i] = NULL;
    return vector_split;
}

void mostrar_resultado(char** descripcion){
    if(descripcion){
        int i = 0;

        printf("\n[");
        while (descripcion[i]){
            if(descripcion[i+1] == NULL){
                if(strcmp(descripcion[i],"") == 0){
                    printf("''");
                }else{
                    printf("'%s'", descripcion[i]);
                }
            } else{
                if(strcmp(descripcion[i],"") == 0){
                    printf("'', ");
                }else{
                    printf("'%s', ", descripcion[i]);
                }
            }
            i++;
        }
        printf("]\n");
    }
    liberar_vector(descripcion);
}

void mostrar_split(const char* string, char separador){
    printf("\nSimulador de la aplicacion de Split en el lenguaje Python\n");
    printf(">>> '%s'.split('%c')", string, separador);
}

int main(){

    char** descripcion;

    printf("Ejemplos de uso de la primitiva Split: \n");

    descripcion = split("123:456:789:0", ':');
    mostrar_split("123:456:789:0", ':');
    mostrar_resultado(descripcion);
    
    descripcion = split("Hola como estas?", ' ');
    mostrar_split("Hola como estas?", ' ');
    mostrar_resultado(descripcion);
    
    descripcion = split("Hola mundo", '?');
    mostrar_split("Hola mundo", '?');
    mostrar_resultado(descripcion);
    
    descripcion = split(",1,2,3,", ',');
    mostrar_split(",1,2,3,", ',');
    mostrar_resultado(descripcion);
    
    descripcion = split("", ',');
    mostrar_split("", ',');
    mostrar_resultado(descripcion);
    
    descripcion = split(NULL, ';');
    mostrar_resultado(descripcion);

    return 0;
}