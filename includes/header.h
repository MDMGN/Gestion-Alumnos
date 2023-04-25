#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
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
    char nif[11];
}ALUMNO;

typedef struct{
    int dia;
    int mes;
    int anio;
}FECHA;

typedef struct{
    int nCurso;
    char description[20];
    FECHA fInicio;
    FECHA fFin;
    int iniciado;
    int finalizado;
    int plazasMax;
}CURSO;

//Cabezeras de funciones

/* Funciones auxiliares */
void gotoXY(int x,int y);
int menu(char *menu[30],int limit);

/* Funciones para el submenu de alumno */
void menuAlumnos();
void mostrarMenu(char*menu[30],int limit);
void altaAlumnos();
void consultaAlumno();
void introducirDatosAlumnos(ALUMNO *alumno);
int getLastExpe(FILE *file);
void mostrarAlumno(ALUMNO alumno);
void modificarAlumno();
int comprobarExp(int,int);
void editarAlumno(ALUMNO *alumno);

/* Funciones para el submenu de cursos */
void menuCursos();