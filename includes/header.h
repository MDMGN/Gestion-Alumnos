#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>

//Constantes
#define RUTA_A "data/alumnos.dat"
#define RUTA_AS "data/asignaturas.dat"
//Estructuras de datos
typedef struct{
    int nExped;
    char nombre[20];
    char domicilio[20];
    char codPost[5];
    char municipio[15];
    char nif[15];
}ALUMNO;

//Cabezeras de funciones
void mostrarMenu();
int menu();
void mostrarFicheroAlumno();
