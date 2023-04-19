#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>

//Constantes
#define RUTA_A "data/alumnos.dat"
#define RUTA_AS "data/asignaturas.dat"

//Estructuras
typedef struct{
    int nExped;
    char nombre[20];
    char domicilio[20];
    char codPost[5];
    char municipio[15];
    char nif[15];
}ALUMNO;

//Cabezeras de funciones
void gotoXY(int x,int y);
int menu(char *menu[30],int limit);
void menuAlumnos();
void mostrarMenu(char*menu[30],int limit);
void altaAlumnos();
void introducirDatosAlumnos(FILE *pf,ALUMNO alumno);
int getLastExpe(FILE *file);
void modificarAlumno();
int comprobarExp(int,int);