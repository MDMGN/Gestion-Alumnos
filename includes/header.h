#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <windows.h>

//Constantes
#define RUTA_A "data/alumnos.dat"
#define RUTA_AS "data/asignaturas.dat"
#define RUTA_C "data/cursos.dat"

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
void gotoXY(int,int);
int menu(char **,int);
int totalRegistro(FILE *,long);
void insertarFecha(char date[],FECHA* fecha);
/* Funciones para el submenu de alumno */
void menuAlumno();
void mostrarMenu(char*,int);
void altaAlumno();
void consultaAlumno();
void introducirDatosAlumno(ALUMNO *);
void mostrarAlumno(ALUMNO);
void modificarAlumno();
int comprobarExp(int,int);
void editarAlumno(ALUMNO *);

/* Funciones para el submenu de cursos */
void menuCurso();
void altaCurso();
void introducirDatosCurso(CURSO*);
void modificarCurso();
void consultaCurso();
void mostrarCurso(CURSO curso);