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
#define RUTA_M "data/matricula.dat"
#define RUTA_LISTA_AL "informes/alumnos.txt"
#define RUTA_LISTA_RE "informes/resumenes.txt"

//Colores
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

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

typedef struct{
    int nMatricula;
    int nCurso;
    int nExp;
    float nota;
}MATRICULA;

typedef struct{
    int nMatricula;
    int nCurso;
    int nExp;
    float nota;
}NOTA;


//Cabezeras de funciones

/* Funciones auxiliares */
void gotoXY(int,int);
int menu(char **,int);
int comprobar(int,int);
int totalRegistro(FILE *,long);
void insertarFecha(char date[],FECHA* fecha);
void debugearInt(int);
/* Funciones para el submenu de alumno */
void menuAlumno();
void mostrarMenu(char**,int);
void altaAlumno();
void consultaAlumno();
void introducirDatosAlumno(ALUMNO *);
void mostrarAlumno(ALUMNO);
void modificarAlumno();
void editarAlumno(ALUMNO *);
void pedirAlumno(int*,char*);

/* Funciones para el submenu de cursos */
void menuCurso();
void altaCurso();
void introducirDatosCurso(CURSO*);
void modificarCurso();
void editarCurso(CURSO*);
void consultaCurso();
void mostrarCurso(CURSO curso);
void pedirCurso(int*,char*);

/*Funciones para el submenu de matricula*/

void matriculaciones();
void gestionarMatricula(FILE *,FILE*,FILE*);
int comprobarPlazas(int,int,FILE *);
void gestionarAlumno(FILE *,FILE *,int,int,int);
void escribirMatricula(MATRICULA*,int,int,int);
int comprobarMatricula(int,int ,FILE *);
void mostrarMatriculas();

//Funciones para el submenu de Gestions de Cursos
void gestionCursos();
void comenzarCurso();
void finalizarCurso();
void boletinAlumno();
int informeAlumnosPorCurso(int,FILE*,FILE*);
void gestionarNotas(int,FILE*,FILE*);
int informeResumen(FILE*,FILE*);
void pedirNota(float* nota);