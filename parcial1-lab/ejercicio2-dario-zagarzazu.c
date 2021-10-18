#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAMIONES 200
#define PATENTE 7
#define MAX_DESTINOS 999
#define MAX_CHOFER 150

typedef struct{
    short num_destino;
    float distancia;
}ST_DESTINO;

typedef struct{
    char patente[PATENTE];
    short num_destino;
    char num_chofer;
}ST_VIAJE;

typedef struct{
    char patente[PATENTE];
}ST_CAMION;

typedef struct{
    char num_chofer;
    float distancia;
}ST_CHOFER;

FILE * abrir(const char * filename, const char * mode);
void cerrar(FILE * file);
int leerViaje(ST_VIAJE *reg, FILE * file);
int leerDestino(ST_DESTINO *reg, FILE * file);
void verificarCamion(ST_CAMION camiones[], const char* patente);
void informarViajesADestino(int arr[]);
void cargarDestinos(ST_DESTINO arr[], FILE * file);
float buscarDistancia(ST_DESTINO arr[], int destino);

int main(){
    FILE * bDestino = abrir(".\\destinos.dat", "rb");
    FILE * bViajes = abrir(".\\viajes.dat", "rb");

    ST_DESTINO destinos[MAX_DESTINOS] = {0};
    cargarDestinos(destinos, bDestino);
    cerrar(bDestino);
    ST_VIAJE viaje;
    ST_CAMION camiones[CAMIONES] = {0};
    ST_CHOFER chofer[MAX_CHOFER] = {0};
    int viajes_a_destino[MAX_DESTINOS] = {0};

    leerViaje(&viaje,bViajes);
    while (!feof(bViajes))
    {
        viajes_a_destino[viaje.num_destino-1] += 1;
        if(viaje.num_destino == 116){
            verificarCamion(camiones, viaje.patente);
        }
        chofer[0].num_chofer = viaje.num_chofer;
        chofer[0].distancia += buscarDistancia(destinos, viaje.num_destino);
        leerViaje(&viaje,bViajes);
    }
    
    informarViajesADestino(viajes_a_destino);

    cerrar(bViajes);
    return 0;
}
FILE * abrir(const char * filename, const char * mode){
    FILE * file = fopen(filename, mode);
    if(file == NULL){
        fputs("Error al abrir archivo: ",stderr);
        printf("%s\n", filename);
        system("pause");
        exit(EXIT_FAILURE);
    }
    return file;
}
void cerrar(FILE * file){
    fclose(file);
    file = NULL;
}
int leerDestino(ST_DESTINO *reg, FILE * file){
    return fread(reg, sizeof(reg), 1, file);
}
int leerViaje(ST_VIAJE *reg, FILE * file){
    return fread(reg, sizeof(reg), 1, file);
}
void verificarCamion(ST_CAMION camiones[], const char* patente){
    for (int i = 0; i < CAMIONES; i++)
    {
        if(strcmp(camiones[i].patente ,patente) != 0){
            strcpy(camiones[i].patente, patente);
            return;
        }
    }
    
}
void informarViajesADestino(int arr[]){
    for (int i = 0; i < MAX_DESTINOS; i++)
    {
        if(arr[i] != 0){
            printf("Viajes a destino %d: %d", i+1, arr[i]);
        }
    }
    
}

float buscarDistancia(ST_DESTINO arr[], int destino){
    for (int i = 0; i < MAX_DESTINOS; i++)
    {
        if(arr[i].num_destino == destino){
            return arr[i].distancia;
        }
    }
    return -1;
}
void cargarDestinos(ST_DESTINO arr[], FILE * file){
    ST_DESTINO aux;
    leerDestino(&aux, file);
    int i = 0;
    while (!feof(file))
    {
        arr[i].num_destino = aux.num_destino;
        arr[i].distancia = aux.distancia;
        i++;
        leerDestino(&aux, file);
    }
}
