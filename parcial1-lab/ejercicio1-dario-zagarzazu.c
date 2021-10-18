#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MATERIAS 20

typedef struct{
    char codigo_materia[5];
    int cant_alumnos;
}ST_MATERIA;

typedef struct{
    char codigo_materia[5];
    char legajo[6];
    char nota;
}ST_ALUMNO;

typedef struct
{
    ST_MATERIA materia;
    int aprobados;
    int reprobados;
}ST_PORCENTAJE;


FILE * abrir(const char * filename, const char * mode);
void cerrar(FILE * file);

int leerBin(ST_ALUMNO * reg, FILE * file);
int leerMateria(ST_MATERIA * reg, FILE * file);
void cargarMaterias(FILE * file,ST_PORCENTAJE porcentaje[]);
int cantAlumnosMateria(const char * codigo, ST_PORCENTAJE arr[]);
void actualizarAprobadosMateria(ST_PORCENTAJE arr[], const char * codigo);
void actualizarReprobadosMateria(ST_PORCENTAJE arr[], const char * codigo);
void informarNotas(int notas[]);
void informarMaterias(ST_PORCENTAJE arr[]);

int main()
{
    FILE * bMaterias = abrir(".\\materias.dat", "rb");
    FILE * bAlumnos = abrir(".\\alumnos.dat", "rb");

    int notas[10] = {0};
    ST_PORCENTAJE porcentaje[MAX_MATERIAS] = {0};
    cargarMaterias(bMaterias, porcentaje);
    cerrar(bMaterias);

    ST_ALUMNO alumno;
    leerBin(&alumno, bAlumnos);
    while (!feof(bAlumnos))
    {
        notas[alumno.nota-1] += 1;
        if(alumno.nota >= 6){
            actualizarAprobadosMateria(porcentaje, alumno.codigo_materia);
        }else{
            actualizarReprobadosMateria(porcentaje, alumno.codigo_materia);
        }
        int cant_alumnos = cantAlumnosMateria(alumno.codigo_materia, porcentaje);
        if(cant_alumnos == -1){
            printf("Error al buscar alumnos.\n");
            system("pause");
            return 0;
        }

        leerBin(&alumno, bAlumnos);
    }
    
    cerrar(bAlumnos);
    informarNotas(notas);
    informarMaterias(porcentaje);

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

int leerBin(ST_ALUMNO * reg, FILE * file){
    return fread(reg, sizeof(reg), 1, file);
}
int leerMateria(ST_MATERIA * reg, FILE * file){
    return fread(reg, sizeof(reg), 1, file);
}
void cargarMaterias(FILE * file,ST_PORCENTAJE porcentaje[]){
    ST_MATERIA aux;
    leerMateria(&aux, file);
    int i = 0;
    while(!feof(file))
    {
        if(leerMateria == NULL) return;
        strcpy(porcentaje[i].materia.codigo_materia, aux.codigo_materia);
        porcentaje[i].materia.cant_alumnos = aux.cant_alumnos;
        leerMateria(&aux, file);
        i++;
    }
}

int cantAlumnosMateria(const char * codigo, ST_PORCENTAJE arr[]){
    for (int i = 0; i < MAX_MATERIAS; i++)
    {
        if(strcmp(arr[i].materia.codigo_materia,codigo) == 0){
            return arr[i].materia.cant_alumnos;
        }
    }
    return -1;
}

void actualizarAprobadosMateria(ST_PORCENTAJE arr[], const char * codigo){
    for (int i = 0; i < MAX_MATERIAS; i++){
        if(strcmp(arr[i].materia.codigo_materia, codigo) == 0){
            arr[i].aprobados++;
        }
    }
}
void actualizarReprobadosMateria(ST_PORCENTAJE arr[], const char * codigo){
    for (int i = 0; i < MAX_MATERIAS; i++){
        if(strcmp(arr[i].materia.codigo_materia, codigo) == 0){
            arr[i].reprobados++;
        }
    }
}
void informarNotas(int notas[]){
    for (int i = 0; i < 10; i++) {
        printf("Alumnos con nota %d: %d\n", i+1, notas[i]);
    }
}
void informarMaterias(ST_PORCENTAJE arr[]){
    for (int i = 0; i < MAX_MATERIAS; i++){
        printf("Materia: %s - Aprobados %d%% - Reprobados %d%%\n", arr[i].materia.codigo_materia, arr[i].aprobados, arr[i].reprobados);
    }
}